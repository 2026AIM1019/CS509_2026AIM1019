#ifndef PAGERANK_H
#define PAGERANK_H

#include "graph.h"

struct PageRankResult
{
    vector<double> rank;
    int iterations = 0;  // Stores how many iterations were performed.
    bool converged = false;  // whether convergence actually happened
};

PageRankResult pageRank(const CSRGraph &, double, double, int);

#endif
