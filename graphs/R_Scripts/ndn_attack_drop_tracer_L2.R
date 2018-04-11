library(ggplot2)
library(scales)
library(doBy)
#################################################################
#L2 Drop Trace Script, Ertugrul Dogruluk- 2018
#Algorithmi Research Centree, Braga-Portugal, University of Minho
##################################################################
data = read.table("/home/ertugrul/Desktop/ndnSIM/scenario/results/p4_drop-trace.txt", header=T)
data$Node = factor(data$Node)
data$Kilobits <- data$Kilobytes 
data$Type = factor(data$Type)

## data.rtr = data[grep("Rtr", data$Node),]

# graph rates on all nodes in Kilobits
g.all <- ggplot(data, aes(x=Time, y=Kilobits, color=Type)) +
  geom_line(size=0.3) +
  ylab("Packet drop rate [Kbits/s]") +
  facet_wrap(~ Node) +
  theme_bw(base_size = 5)
 # scale_y_continuous(labels = scales::percent)


ggsave("/home/ertugrul/Desktop/ndnSIM/scenario/graphs/PDFs/p4/p4_L2_drop_tracer.pdf", width=5, height=2.5)
print(g.all)
x = dev.off()