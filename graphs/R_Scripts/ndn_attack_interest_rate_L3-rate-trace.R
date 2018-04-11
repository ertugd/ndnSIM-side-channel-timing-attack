library(ggplot2)
library(scales)
library(doBy)
#################################################################
#L3 Rate Tracer_Interest Analyse Script, Ertugrul Dogruluk- 2018
#Algorithmi Research Centree, Braga-Portugal, University of Minho
##################################################################
data = read.table("/home/ertugrul/Desktop/ndnSIM/scenario/results/p4_L3-rate-trace.txt", header=T)
data$Node = factor(data$Node)
data$FaceId <- factor(data$FaceId)
data$Kilobits <- data$Kilobytes * 8
data$Type = factor(data$Type)
data$Packets  = data$Packets
#data$PacketRaw  = data$PacketRaw

# exlude irrelevant types
data = subset(data, Type %in% c("InInterests", "OutData", "OutInterests", "InData", "OutSatisfiedInterests","InTimedOutInterests","OutSatisfiedInterests",
                                "OutTimedOutInterests","TimedOutInterests", "SatisfiedInterests", "InSatisfiedInterests"))
data = subset(data, Node %in% c("leaf-6", "leaf-13", "leaf-5", "leaf-4", "leaf-3", "leaf-2", "leaf-1"
                                        , "leaf-7", "leaf-8", "leaf-9", "leaf-10", "leaf-11"
                                        , "leaf-12", "leaf-14", "leaf-15", "leaf-16"))

# combine stats from all faces
data.combined = summaryBy(. ~ Time + Node + Type, data=data, FUN=sum)

data.root = subset (data.combined, Node == "gw-root")
data.leaves = subset(data.combined, Node %in% c("bb-6"))

# graph rates on all nodes in Kilobits
g.all <- ggplot(data.combined) +
  geom_line(aes (x=Time, y=Packets.sum, color=Node), size=0.3) +
  ylab("Rate [Kbits/s]") +
  facet_wrap(~ Type)+
theme_bw(base_size = 5)+
scale_colour_manual(values=c("leaf-6"="blue1","leaf-13"="firebrick1","leaf-5"="chartreuse3", "leaf-4"="burlywood1",
                                "leaf-3"="burlywood4", "leaf-2"="darkmagenta", "leaf-1"="burlywood4"
                               , "leaf-7"="darkmagenta", "leaf-8"="deeppink", "leaf-9"="gray0", "leaf-10"="darkolivegreen4", 
                               "leaf-11"="goldenrod3" , "leaf-12"="darkseagreen", "leaf-14"="darkorchid1", "leaf-15"="gold4", "leaf-16"="cadetblue1"))
 # scale_y_continuous(labels = scales::percent)

  
print(g.all)

# graph rates on the root nodes in Packets
g.root <- ggplot(data.leaves) +
  geom_point(aes (x=Time, y=Kilobits.sum, color=Node), size=2) +
  geom_line(aes (x=Time, y=Kilobits.sum, color=Type), size=0.5) +
  ylab("Rate [Kbits/s]")


print(g.all)

ggsave("/home/ertugrul/Desktop/ndnSIM/scenario/graphs/PDFs/p4/p4_L3_rate_tracer.pdf", width=8, height=5)
retval <- dev.off()

