#include "graph.h"
#include <queue>
#include <functional>

MSTResult prim(const CSRGraph &g)
{
    MSTResult r;
    vector<bool> used(g.V, false);

    using Item = pair<int, pair<int, int>>;
    priority_queue<Item, vector<Item>, greater<Item>> q;
    
    q.push({0, {0, -1}});
    while (!q.empty())
    {
        auto x = q.top();
        q.pop();
        int w = x.first, u = x.second.first, p = x.second.second;
        if (used[u])
            continue;
        used[u] = true;
        if (p != -1)
        {
            r.edges.push_back({p, u, w});
            r.totalWeight += w;
        }
        for (int i = g.offset[u]; i < g.offset[u + 1]; i++)
            if (!used[g.to[i]])
                q.push({g.weight[i], {g.to[i], u}});
    }
    return r;
}
