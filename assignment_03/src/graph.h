#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

using namespace std;

struct Edge
{
    int u, v, weight;
};

struct Graph
{
    int V, E;
    vector<vector<Edge>> adj;
};

struct CSRGraph
{
    int V;
    vector<int> offset, to, weight;
};

struct MSTResult
{
    vector<Edge> edges;
    long long totalWeight = 0;
};

bool readGraph(const string &, Graph &);

CSRGraph convertToCSR(const Graph &);

vector<Edge> getEdges(const Graph &);

MSTResult kruskal(const Graph &);

MSTResult prim(const CSRGraph &);

void sortMSTEdges(vector<Edge> &);

#endif
