library(ggplot2)
library(scales)
library(doBy)
#################################################################
#Cache Hit/Miss Ratios Analyse Script, Ertugrul Dogruluk- 2018
#Algorithmi Research Centree, Braga-Portugal, University of Minho
##################################################################
data = read.table("/home/ertugrul/Desktop/ndnSIM/scenario/results/p4_Cs_tracer.txt", header=T)

data$Node = factor(data$Node)
data$Type = factor(data$Type)
data$Packets  = data$Packets
#data = subset(data, Node
              
              #%in% c("leaf-6", "leaf-13", "leaf-5", "leaf-4", "leaf-3", "leaf-2", "leaf-1"
              #                  , "leaf-7", "leaf-8", "leaf-9", "leaf-10", "leaf-11"
              #                  , "leaf-12", "leaf-14", "leaf-15", "leaf-16"))

data1 = subset(data, Type %in% c("CacheHits", "CacheMisses"))


# graph rates on all nodes in Kilobits
g.all <- ggplot(data, aes(x=Time, y = Packets, color=Type)) +
  geom_line(size=0.3) +
  ylab("Number of Packets") +
  facet_wrap(~ Node) +
  theme_light(base_size = 5)+
  #scale_y_continuous(labels = scales::percent)



ggsave("/home/ertugrul/Desktop/ndnSIM/scenario/graphs/PDFs/p4/p4_cache_tracer.pdf", width=5, height=2.5)

print(g.all)

retval <- dev.off()

