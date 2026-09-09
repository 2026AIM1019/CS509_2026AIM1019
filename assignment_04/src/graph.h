#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

using namespace std;

struct Graph {
    int V=0,E=0;
    vector<vector<int>> adj;
};

struct CSRGraph {
    int V=0;
    vector<int> offset,to;
};

bool readUndirectedGraph(const string&, Graph&);

bool readDirectedPageRankGraph(const string&, Graph&, double&, double&, int&);

CSRGraph convertToCSR(const Graph&);

#endif
