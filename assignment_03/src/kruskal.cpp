#include "graph.h"
#include <algorithm>
class DSU
{
    vector<int> p, r;

public:
    DSU(int n) : p(n), r(n, 0)
    {
        for (int i = 0; i < n; i++)
            p[i] = i;
    }

    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }

    bool unite(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        if (r[a] < r[b])
            swap(a, b);
        p[b] = a;
        if (r[a] == r[b])
            r[a]++;
        return true;
    }
};

MSTResult kruskal(const Graph &g)
{
    auto e = getEdges(g);
    sort(e.begin(), e.end(), [](Edge a, Edge b)
         { return a.weight < b.weight; });

    DSU d(g.V);
    MSTResult r;

    for (auto x : e)
        if (d.unite(x.u, x.v))
        {
            r.edges.push_back(x);
            r.totalWeight += x.weight;

            if ((int)r.edges.size() == g.V - 1)
                break;
        }
    return r;
}
