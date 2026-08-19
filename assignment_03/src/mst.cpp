#include "graph.h"
#include <algorithm>

void sortMSTEdges(vector<Edge> &e)
{
    sort(e.begin(), e.end(), [](Edge a, Edge b)
         {if(a.u!=b.u)
            return a.u<b.u;
        return a.v<b.v; });
}
