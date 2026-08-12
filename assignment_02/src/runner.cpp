#include "runner.h"

#include <iostream>
#include <iomanip>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <limits>

#include "graph.h"
#include "graph_io.h"
#include "csr.h"
#include "timer.h"
#include "output.h"
#include "compare.h"
#include "bellman_ford.h"
#include "floyd_warshall.h"

using namespace std;
namespace fs = std::filesystem;

namespace
{
    const long long INF = numeric_limits<long long>::max() / 4;

    vector<fs::path> getTestFiles(const string &folder)
    {
        vector<fs::path> files;

        if (!fs::exists(folder))
            throw runtime_error("Tests directory not found: " + folder);

        for (const auto &entry : fs::directory_iterator(folder))
        {
            if (entry.is_regular_file() &&
                entry.path().extension() == ".txt")
            {
                files.push_back(entry.path());
            }
        }

        sort(files.begin(), files.end());
        return files;
    }

    void createGeneratedDirectory(const string &folder)
    {
        if (!fs::exists(folder))
            fs::create_directories(folder);
    }

    void printHeader(const string &algorithm)
    {
        cout << "=========================================\n";
        cout << "   " << algorithm << " Automatic Test Runner\n";
        cout << "=========================================\n\n";

        cout << left
             << setw(20) << "Test File"
             << setw(10) << "Status"
             << "Execution Time\n";

        cout << "----------------------------------------------------------\n";
    }

    void printSummary(int passed, int failed)
    {
        cout << "\n=========================================\n";
        cout << "Total Tests : " << passed + failed << '\n';
        cout << "Passed      : " << passed << '\n';
        cout << "Failed      : " << failed << '\n';
        cout << "=========================================\n";
    }

    CSRGraph matrixToCSR(const MatrixGraph &matrixGraph)
    {
        Graph graph;
        graph.V = matrixGraph.V;
        graph.source = matrixGraph.source;
        graph.adj.resize(graph.V);
        graph.weights.resize(graph.V);

        int edgeCount = 0;

        for (int u = 0; u < graph.V; ++u)
        {
            for (int v = 0; v < graph.V; ++v)
            {
                if (u == v)
                    continue;

                if (matrixGraph.matrix[u][v] < INF)
                {
                    graph.adj[u].push_back(v);
                    graph.weights[u].push_back(
                        static_cast<int>(matrixGraph.matrix[u][v]));
                    ++edgeCount;
                }
            }
        }

        graph.E = edgeCount;
        return convertToCSR(graph);
    }

    bool crossCheckBellmanFord(
        const MatrixGraph &matrixGraph,
        const FloydWarshallResult &floydResult)
    {
        if (matrixGraph.V != 10 && matrixGraph.V != 100)
            return true;

        if (floydResult.negativeCycle)
            return true;

        CSRGraph csr = matrixToCSR(matrixGraph);

        for (int source = 0; source < matrixGraph.V; ++source)
        {
            BellmanFordResult bf = BellmanFord(csr, source);

            if (bf.negativeCycle)
                return false;

            for (int v = 0; v < matrixGraph.V; ++v)
            {
                long long expected = floydResult.distance[source][v];
                long long actual = bf.distance[v];

                bool bothInf =
                    expected >= INF && actual >= INF;

                if (!bothInf && expected != actual)
                    return false;
            }
        }

        return true;
    }
}

void runAlgorithm(
    const string &algorithmName,
    function<double(const CSRGraph &, int, const string &)> executor)
{
    string testFolder = "tests/" + algorithmName;
    string outputFolder = "outputs/" + algorithmName;
    string generatedFolder = "generated/" + algorithmName;

    createGeneratedDirectory(generatedFolder);

    vector<fs::path> testFiles = getTestFiles(testFolder);

    if (testFiles.empty())
    {
        cout << "No test files found.\n";
        return;
    }

    int passed = 0;
    int failed = 0;

    string title = algorithmName;

    transform(title.begin(),
              title.end(),
              title.begin(),
              ::toupper);

    printHeader(title);

    for (const auto &testFile : testFiles)
    {
        Graph graph = readGraph(testFile.string());
        CSRGraph csr = convertToCSR(graph);

        string filename = testFile.filename().string();
        string generatedFile = generatedFolder + "/" + filename;
        string expectedFile = outputFolder + "/" + filename;

        double executionTime =
            executor(csr, graph.source, generatedFile);

        bool ok =
            compareFiles(expectedFile, generatedFile);

        cout << left
             << setw(20) << filename;

        if (ok)
        {
            ++passed;
            cout << setw(10) << "PASS";
        }
        else
        {
            ++failed;
            cout << setw(10) << "FAIL";
        }

        cout << fixed << setprecision(3)
             << executionTime << " ms\n";
    }

    printSummary(passed, failed);
}

void runBellmanFord()
{
    runAlgorithm(
        "bellman_ford",
        [](const CSRGraph &csr,
           int source,
           const string &generatedFile) -> double
        {
            Timer timer;
            timer.start();

            BellmanFordResult result =
                BellmanFord(csr, source);

            timer.stop();

            writeBellmanFordOutput(
                generatedFile,
                result,
                source);

            return timer.elapsedMilliseconds();
        });
}

void runFloydWarshall()
{
    const string testFolder = "tests/floyd_warshall";
    const string outputFolder = "outputs/floyd_warshall";
    const string generatedFolder = "generated/floyd_warshall";

    createGeneratedDirectory(generatedFolder);

    vector<fs::path> testFiles = getTestFiles(testFolder);

    if (testFiles.empty())
    {
        cout << "No Floyd-Warshall test files found.\n";
        return;
    }

    int passed = 0;
    int failed = 0;
    int crossChecks = 0;
    int crossCheckFailures = 0;

    printHeader("FLOYD-WARSHALL");

    for (const auto &testFile : testFiles)
    {
        MatrixGraph graph =
            readMatrixGraph(testFile.string());

        string filename = testFile.filename().string();
        string generatedFile =
            generatedFolder + "/" + filename;
        string expectedFile =
            outputFolder + "/" + filename;

        Timer timer;
        timer.start();

        FloydWarshallResult result =
            FloydWarshall(graph);

        timer.stop();

        writeFloydWarshallOutput(
            generatedFile,
            result);

        bool ok =
            compareFiles(
                expectedFile,
                generatedFile);

        bool crossCheck = true;

        if (graph.V == 10 || graph.V == 100)
        {
            ++crossChecks;

            crossCheck =
                crossCheckBellmanFord(
                    graph,
                    result);

            if (!crossCheck)
                ++crossCheckFailures;
        }

        if (!crossCheck)
            ok = false;

        cout << left
             << setw(20) << filename;

        cout << setw(10)
             << (ok ? "PASS" : "FAIL");

        cout << fixed << setprecision(3)
             << timer.elapsedMilliseconds()
             << " ms";

        if (graph.V == 10 || graph.V == 100)
        {
            cout << " | BF cross-check: "
                 << (crossCheck ? "PASS" : "FAIL");
        }

        cout << '\n';

        if (ok)
            ++passed;
        else
            ++failed;
    }

    printSummary(passed, failed);

    if (crossChecks > 0)
    {
        cout << "Bellman-Ford cross-checks: "
             << crossChecks
             << ", failed: "
             << crossCheckFailures
             << "\n";
    }
}
