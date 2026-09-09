#include "pagerank.h"
#include <cmath>

PageRankResult pageRank(const CSRGraph &g, double d, double tol, int maxIter)
{
    PageRankResult r;

    // Initialize the rank vector to uniform distribution : 1/V for each vertex
    r.rank.assign(g.V, 1.0 / g.V);

    // PageRank values for the next iteration.
    vector<double> next(g.V);

    for (int it = 1; it <= maxIter; it++)
    {
        fill(next.begin(), next.end(), (1.0 - d) / g.V);
        
        // A dangling vertex is a vertex with no outgoing edges.
        double dangling = 0;

        for (int u = 0; u < g.V; u++)
        {
            // The number of outgoing edges from vertex u.
            int out = g.offset[u + 1] - g.offset[u];

            if (out == 0)  // If vertex u is dangling, accumulate its rank to be distributed later.
                dangling += r.rank[u];
            else  // Distribute the rank of vertex u to its outgoing neighbors.
                for (int p = g.offset[u]; p < g.offset[u + 1]; p++)
                    next[g.to[p]] += d * r.rank[u] / out;
        }

        // If at least one dangling vertex exists, we distribute its PageRank.
        if (dangling != 0)
            for (double &x : next)
                x += d * dangling / g.V;

        // Calculate the total change in PageRank values to check for convergence.
        double change = 0;

        for (int i = 0; i < g.V; i++)
            change += fabs(next[i] - r.rank[i]);

        r.rank.swap(next);
        r.iterations = it;

        if (change <= tol)
        {
            r.converged = true;
            break;
        }
    }

    return r;
}
