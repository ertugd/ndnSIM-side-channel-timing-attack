library(ggplot2)
library(scales)
library(doBy)
#################################################################
#App_delay_Tracer_RTT Ratios Analyse Script, Ertugrul Dogruluk- 2018
#Algorithmi Research Centree, Braga-Portugal, University of Minho
##################################################################
data = read.table("/home/ertugrul/Desktop/ndnSIM/scenario/results/p4_app-delays-trace.txt", header=T)

data$Node = factor(data$Node)
data$Type = factor(data$Type)
data$DelayS <- data$DelayS 
data$Time = data$Time
data$AppId = data$AppId

data = subset(data, Type %in% c("FullDelay"))
#data = subset(data, AppId %in% c("0"))
data = subset(data, Node %in% c("leaf-6", "leaf-13", "leaf-5", "leaf-4", "leaf-3", "leaf-2", "leaf-1"
                                , "leaf-7", "leaf-8", "leaf-9", "leaf-10", "leaf-11"
                                , "leaf-12", "leaf-14", "leaf-15", "leaf-16"))
data.combined = summaryBy(. ~ Time + Node + Type, data=data, FUN=mean)

#data.leaves = subset(data.combined, Node %in% c("leaf-16"))

# graph rates on the root nodes in Packets
g.root <- ggplot(data.combined) +
  geom_point(aes (x=Time, y=DelayS.mean, color=Node ), size=0.2) +
  #geom_point(aes(x=Node, y=DelayS.mean, color=Type))+
  
  ylab("RTT Values(nS)") +
  xlab("Simulation Time (sec.)")+
  theme_bw(base_size = 10)+
  scale_colour_manual(values=c("leaf-6"="blue1","leaf-13"="firebrick1","leaf-5"="chartreuse3", "leaf-4"="burlywood1",
                                "leaf-3"="burlywood4", "leaf-2"="darkmagenta", "leaf-1"="burlywood4"
                               , "leaf-7"="darkmagenta", "leaf-8"="deeppink", "leaf-9"="gray0", "leaf-10"="darkolivegreen4", 
                               "leaf-11"="goldenrod3" , "leaf-12"="darkseagreen", "leaf-14"="darkorchid1", "leaf-15"="gold4", "leaf-16"="cadetblue1"))+
  #annotate("text", x = 32, y = 0.0011, label = "--->Cached Content RTT", size = 3.2, colour = "red")+
  #scale_y_continuous(labels = scales::percent)+
  facet_wrap(~ Node)
  
  #coord_flip()

ggsave("/home/ertugrul/Desktop/ndnSIM/scenario/graphs/PDFs/p4/p4_app_delay_tracer.pdf", width=10, height=10)
print(g.root)
x = dev.off()

