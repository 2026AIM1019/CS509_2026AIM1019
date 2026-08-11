#include "floyd_warshall.h"

#include <limits>
#include <algorithm>

using namespace std;

FloydWarshallResult FloydWarshall(const MatrixGraph &graph)
{
    FloydWarshallResult result;

    const long long INF = numeric_limits<long long>::max() / 4;
    result.distance = graph.matrix;
    result.negativeCycle = false;

    for (int k = 0; k < graph.V; ++k)
    {
        for (int i = 0; i < graph.V; ++i)
        {
            if (result.distance[i][k] >= INF)
                continue;

            for (int j = 0; j < graph.V; ++j)
            {
                if (result.distance[k][j] >= INF)
                    continue;

                long long throughK =
                    result.distance[i][k] + result.distance[k][j];

                if (throughK < result.distance[i][j])
                    result.distance[i][j] = throughK;
            }
        }
    }

    for (int i = 0; i < graph.V; ++i)
    {
        if (result.distance[i][i] < 0)
        {
            result.negativeCycle = true;
            break;
        }
    }

    return result;
}
