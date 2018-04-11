library(ggplot2)
library(dplyr)
library(tidyr)
library(reshape2)
library(ggrepel)
set.seed(42)
library(grid)
#################################################################
#Cache Hit Ratios Analyse Script, Ertugrul Dogruluk- 2018
#Algorithmi Research Centree, Braga-Portugal, University of Minho
##################################################################
data = read.table("/home/ertugrul/Desktop/ndnSIM/scenario/results/p4_Cs_tracer.txt", header=T)
setwd(dirname(rstudioapi::getActiveDocumentContext()$path))
dataCast <- dcast(data, Time + Node ~ Type) %>%
mutate(CacheHitRatio= CacheHits/(CacheHits+CacheMisses))

  
#dataCast2  <- dataCast %>%  filter(CacheHitRatio > xxx)

dataCast = subset(dataCast, Node %in% c("leaf-6", "leaf-13"))
# graph rates on all nodes in Kilobits
ggplot (dataCast , aes(x=Time, y = CacheHitRatio, color= Node)) +
  geom_line(size=0.35) +
  ylab("CacheHitRatio")+
  xlab("Simulation Time(sec.)")+
 scale_y_continuous(labels = scales::percent)+
  facet_wrap(~ Node) +
  theme(legend.position="none")  
  

  
  #facet_wrap(~ CacheHitRatio)


#coord_flip()+

ggsave("/home/ertugrul/Desktop/ndnSIM/scenario/graphs/PDFs/p4/p4_cache_hit_ratio.pdf", width=3.5, height=3)

print(g.all)

retval <- dev.off()

