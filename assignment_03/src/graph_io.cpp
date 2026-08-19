#include "graph.h"

#include <fstream>
#include <iostream>

bool readGraph(const string &name, Graph &g)
{
    ifstream f(name);
    if (!f)
    {
        cout << "Error: Cannot open input file: " << name << "\n";
        return false;
    }

    f >> g.V >> g.E;

    g.adj.resize(g.V);

    for (int i = 0; i < g.V; i++)
    {
        int u, d;
        f >> u >> d;
        for (int j = 0; j < d; j++)
        {
            int v, w;
            f >> v >> w;
            g.adj[u].push_back({u, v, w});
        }
    }
    return true;
}

CSRGraph convertToCSR(const Graph &g)
{
    CSRGraph c;
    c.V = g.V;
    c.offset.resize(g.V + 1, 0);

    for (int i = 0; i < g.V; i++)
        c.offset[i + 1] = c.offset[i] + g.adj[i].size();

    c.to.resize(c.offset[g.V]);
    c.weight.resize(c.offset[g.V]);

    for (int i = 0; i < g.V; i++)
    {
        int p = c.offset[i];
        for (auto e : g.adj[i])
        {
            c.to[p] = e.v;
            c.weight[p] = e.weight;
            p++;
        }
    }
    return c;
}

vector<Edge> getEdges(const Graph &g)
{
    vector<Edge> e;
    for (int u = 0; u < g.V; u++)
        for (auto x : g.adj[u])
            if (u < x.v)
                e.push_back(x);
    return e;
}
