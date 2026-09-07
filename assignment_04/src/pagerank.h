#ifndef PAGERANK_H
#define PAGERANK_H
#include "graph.h"
struct PageRankResult { vector<double> rank; int iterations=0; bool converged=false; };
PageRankResult pageRank(const CSRGraph&,double,double,int);
#endif
