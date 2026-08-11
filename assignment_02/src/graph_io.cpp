#include "graph_io.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

Graph readGraph(const string &filename)
{
    ifstream fin(filename);

    if (!fin.is_open())
        throw runtime_error("Error: Unable to open input file: " + filename);

    Graph graph;

    if (!(fin >> graph.V >> graph.E))
        throw runtime_error("Error: Invalid graph header in " + filename);

    if (graph.V < 0 || graph.E < 0)
        throw runtime_error("Error: V and E must be non-negative.");

    graph.adj.resize(graph.V);
    graph.weights.resize(graph.V);

    for (int i = 0; i < graph.V; i++)
    {
        int vertex;
        int degree;

        if (!(fin >> vertex >> degree))
            throw runtime_error("Error: Invalid adjacency-list line.");

        if (vertex < 0 || vertex >= graph.V || degree < 0)
            throw runtime_error("Error: Invalid vertex or degree.");

        graph.adj[vertex].resize(degree);
        graph.weights[vertex].resize(degree);

        for (int j = 0; j < degree; j++)
        {
            int neighbour;
            int weight;

            if (!(fin >> neighbour >> weight))
                throw runtime_error("Error: Invalid edge in " + filename);

            if (neighbour < 0 || neighbour >= graph.V)
                throw runtime_error("Error: Invalid neighbour vertex.");

            graph.adj[vertex][j] = neighbour;
            graph.weights[vertex][j] = weight;
        }
    }

    string sourceLabel;
    if (!(fin >> sourceLabel >> graph.source))
        throw runtime_error("Error: Missing SOURCE line.");

    transform(sourceLabel.begin(),
              sourceLabel.end(),
              sourceLabel.begin(),
              [](unsigned char c)
              {
                  return static_cast<char>(toupper(c));
              });

    if (sourceLabel != "SOURCE")
        throw runtime_error("Error: Expected 'SOURCE' in input file.");

    if (graph.source < 0 || graph.source >= graph.V)
        throw runtime_error("Error: SOURCE vertex is out of range.");

    return graph;
}

MatrixGraph readMatrixGraph(const string &filename)
{
    ifstream fin(filename);

    if (!fin.is_open())
        throw runtime_error("Error: Unable to open input file: " + filename);

    MatrixGraph graph;

    if (!(fin >> graph.V))
        throw runtime_error("Error: Invalid matrix graph header.");

    if (graph.V <= 0)
        throw runtime_error("Error: Number of vertices must be positive.");

    const long long INF = numeric_limits<long long>::max() / 4;

    graph.matrix.assign(graph.V, vector<long long>(graph.V, INF));

    for (int i = 0; i < graph.V; ++i)
    {
        for (int j = 0; j < graph.V; ++j)
        {
            string token;

            if (!(fin >> token))
                throw runtime_error("Error: Matrix row has fewer than V entries.");

            if (token == "INF")
            {
                graph.matrix[i][j] = INF;
            }
            else
            {
                try
                {
                    size_t pos = 0;
                    long long value = stoll(token, &pos);

                    if (pos != token.size())
                        throw invalid_argument("trailing characters");

                    graph.matrix[i][j] = value;
                }
                catch (...)
                {
                    throw runtime_error(
                        "Error: Invalid matrix value '" + token +
                        "' in " + filename);
                }
            }
        }
    }

    for (int i = 0; i < graph.V; ++i)
    {
        if (graph.matrix[i][i] != 0)
            throw runtime_error("Error: Matrix diagonal must contain 0.");
    }

    graph.source = 0;

    return graph;
}
