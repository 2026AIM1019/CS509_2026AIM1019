#include "csr.h"
using namespace std;

CSRGraph convertToCSR(const Graph &graph)
{
    CSRGraph csr;

    csr.V = graph.V;
    csr.E = graph.E;
    csr.source = graph.source;


    csr.row_ptr.resize(csr.V + 1);

    csr.row_ptr[0] = 0;


    for (int i = 0; i < csr.V; i++)
    {
        csr.row_ptr[i + 1] = csr.row_ptr[i] + graph.adj[i].size();
    }

    int totalEdges = csr.row_ptr[csr.V];

    csr.col_idx.resize(totalEdges);
    csr.weights.resize(totalEdges);

    int index = 0;


    for (int i = 0; i < csr.V; i++)
    {
        for (int j = 0; j < (int)graph.adj[i].size(); j++)
        {
            csr.col_idx[index] = graph.adj[i][j];
            csr.weights[index] = graph.weights[i][j];

            index++;
        }
    }

    return csr;
}