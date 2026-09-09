#include "color.h"
#include <algorithm>
#include <unordered_set>

vector<int> greedyWelshPowell(const CSRGraph &g)
{
    vector<int> deg(g.V);

    // Stores the order in which vertices will be colored.
    vector<int>order(g.V);

    // Stores the color assigned to each vertex. -1 means uncolored.
    vector<int>color(g.V, -1);
    
    for (int i = 0; i < g.V; i++)
    {
        deg[i] = g.offset[i + 1] - g.offset[i];
        order[i] = i;
    }

    // Initially order = [0,1,2,3,4,5].

    // Sort vertices in decreasing order of degree. If two vertices have the same degree, sort them by their vertex number.
    sort(order.begin(), order.end(), [&](int a, int b)
         {if(deg[a]!=deg[b])
            return deg[a]>deg[b];
        return a<b; });

    
    for (int u : order)
    {
        // Colors already used by the current vertex's colored neighbors.
        unordered_set<int> used;

        for (int p = g.offset[u]; p < g.offset[u + 1]; p++)
        {
            int v = g.to[p];
            if (color[v] >= 0)
                used.insert(color[v]);
        }

        int c = 0;
        // If color c is already used, try the next color.
        while (used.count(c))
            ++c;
        
        // Give vertex u the smallest color that doesn't conflict with its already-colored neighbors.
        color[u] = c;
    }

    return color;
}


bool validColoring(const CSRGraph &g, const vector<int> &c)
{
    if ((int)c.size() != g.V)
        return false;

    for (int u = 0; u < g.V; u++)
    {
        if (c[u] < 0)
            return false;
        
        // Go to every neighbour of u and check if it has the same color as u. If yes, return false.
        for (int p = g.offset[u]; p < g.offset[u + 1]; p++)
            if (c[u] == c[g.to[p]])
                return false;
    }

    return true;
}
