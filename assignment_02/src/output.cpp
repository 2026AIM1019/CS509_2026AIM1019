#include "output.h"

#include <fstream>
#include <stdexcept>
#include <limits>

using namespace std;

namespace
{
    const long long INF = numeric_limits<long long>::max() / 4;

    void writeDistance(ofstream &fout, long long value)
    {
        if (value >= INF)
            fout << "INF";
        else
            fout << value;
    }
}

void writeBellmanFordOutput(const string &filename,
                            const BellmanFordResult &result,
                            int source)
{
    ofstream fout(filename);

    if (!fout.is_open())
        throw runtime_error("Unable to create output file.");

    fout << "Algorithm: Bellman-Ford\n";
    fout << "Source: " << source << "\n";

    if (result.negativeCycle)
    {
        fout << "Negative cycle: true\n";
        return;
    }

    fout << "Vertex Distance\n";

    for (size_t i = 0; i < result.distance.size(); ++i)
    {
        fout << i << " ";
        writeDistance(fout, result.distance[i]);
        fout << "\n";
    }

    fout << "Negative cycle: none\n";
}

void writeFloydWarshallOutput(const string &filename,
                              const FloydWarshallResult &result)
{
    ofstream fout(filename);

    if (!fout.is_open())
        throw runtime_error("Unable to create output file.");

    fout << "Algorithm: Floyd-Warshall\n";

    if (result.negativeCycle)
    {
        fout << "Negative cycle: true\n";
        return;
    }

    fout << "Distance matrix:\n";

    for (const auto &row : result.distance)
    {
        for (size_t j = 0; j < row.size(); ++j)
        {
            writeDistance(fout, row[j]);

            if (j + 1 != row.size())
                fout << " ";
        }

        fout << "\n";
    }

    fout << "Negative cycle: none\n";
}
