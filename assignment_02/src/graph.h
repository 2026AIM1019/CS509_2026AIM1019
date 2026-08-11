#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <limits>

using namespace std;

struct Graph
{
    int V = 0;
    int E = 0;
    int source = 0;

    vector<vector<int>> adj;
    vector<vector<int>> weights;
};

struct CSRGraph
{
    int V = 0;
    int E = 0;
    int source = 0;

    vector<int> row_ptr;
    vector<int> col_idx;
    vector<int> weights;
};

struct MatrixGraph
{
    int V = 0;
    int source = 0;

    vector<vector<long long>> matrix;
};


struct BellmanFordResult
{
    vector<long long> distance;
    vector<int> predecessor;
    bool negativeCycle = false;
};

struct FloydWarshallResult
{
    vector<vector<long long>> distance;
    bool negativeCycle = false;
};

#endif
