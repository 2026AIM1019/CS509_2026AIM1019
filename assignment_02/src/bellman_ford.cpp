#include "bellman_ford.h"

#include <limits>

using namespace std;

BellmanFordResult BellmanFord(const CSRGraph &csr, int source)
{
    BellmanFordResult result;

    const long long INF = numeric_limits<long long>::max() / 4;

    result.distance.assign(csr.V, INF);
    result.predecessor.assign(csr.V, -1);
    result.negativeCycle = false;

    if (source < 0 || source >= csr.V)
        return result;

    result.distance[source] = 0;

    for (int pass = 1; pass <= csr.V - 1; ++pass)
    {
        bool changed = false;

        for (int u = 0; u < csr.V; ++u)
        {
            if (result.distance[u] == INF)
                continue;

            for (int i = csr.row_ptr[u]; i < csr.row_ptr[u + 1]; ++i)
            {
                int v = csr.col_idx[i];
                long long w = csr.weights[i];

                if (result.distance[u] + w < result.distance[v])
                {
                    result.distance[v] = result.distance[u] + w;
                    result.predecessor[v] = u;
                    changed = true;
                }
            }
        }

        if (!changed)
            break;
    }

    for (int u = 0; u < csr.V; ++u)
    {
        if (result.distance[u] == INF)
            continue;

        for (int i = csr.row_ptr[u]; i < csr.row_ptr[u + 1]; ++i)
        {
            int v = csr.col_idx[i];
            long long w = csr.weights[i];

            if (result.distance[u] + w < result.distance[v])
            {
                result.negativeCycle = true;
                return result;
            }
        }
    }

    return result;
}
