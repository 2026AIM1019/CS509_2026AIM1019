#include "../src/graph.h"
#include "../src/color.h"
#include "../src/pagerank.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

static const std::string COLOR_TESTS[5] = {
    "tests/color/color_10.txt",
    "tests/color/color_100.txt",
    "tests/color/color_10000.txt",
    "tests/color/color_50000.txt",
    "tests/color/color_100000.txt"
};

static const std::string PAGERANK_TESTS[5] = {
    "tests/pagerank/pagerank_10.txt",
    "tests/pagerank/pagerank_100.txt",
    "tests/pagerank/pagerank_1000.txt",
    "tests/pagerank/pagerank_10000.txt",
    "tests/pagerank/pagerank_50000.txt"
};

static bool fileExists(const std::string& path) {
    std::ifstream f(path);
    return f.good();
}

static int chooseTest(const std::string& name) {
    std::cout << "\n" << name << " test cases:\n";
    for (int i = 0; i < 5; ++i)
        std::cout << (i + 1) << ". Test case " << (i + 1) << "\n";
    std::cout << "Enter test case (1-5): ";

    int choice;
    std::cin >> choice;
    if (!std::cin || choice < 1 || choice > 5)
        return -1;
    return choice;
}

static void runColoring(int testCase) {
    const std::string& path = COLOR_TESTS[testCase - 1];

    if (!fileExists(path)) {
        std::cerr << "Error: Test file not found: " << path << "\n";
        return;
    }

    Graph g;
    if (!readUndirectedGraph(path, g)) {
        std::cerr << "Error: Invalid Vertex Coloring input.\n";
        return;
    }

    // CSR conversion is preprocessing and is intentionally outside timing.
    CSRGraph csr = convertToCSR(g);

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> colors = greedyWelshPowell(csr);
    auto stop = std::chrono::high_resolution_clock::now();

    double ms =
        std::chrono::duration<double, std::milli>(stop - start).count();

    bool valid = validColoring(csr, colors);
    int colorsUsed = 0;
    for (int c : colors)
        colorsUsed = std::max(colorsUsed, c + 1);

    std::cout << "\nAlgorithm: Greedy Vertex Coloring\n";
    std::cout << "Test case: " << testCase << "\n";
    std::cout << "Input: " << path << "\n";
    std::cout << "Vertices: " << g.V << "\n";
    std::cout << "Edges: " << g.E << "\n";
    std::cout << "Vertex colors:\n";

    for (int i = 0; i < g.V; ++i)
        std::cout << i << " " << colors[i] << "\n";

    std::cout << "Colors used: " << colorsUsed << "\n";
    std::cout << "Valid: " << (valid ? "true" : "false") << "\n";
    std::cout << "Execution time: " << ms << " ms\n";
}

static void runPageRank(int testCase) {
    const std::string& path = PAGERANK_TESTS[testCase - 1];

    if (!fileExists(path)) {
        std::cerr << "Error: Test file not found: " << path << "\n";
        return;
    }

    Graph g;
    double damping, tolerance;
    int maxIterations;

    if (!readDirectedPageRankGraph(
            path, g, damping, tolerance, maxIterations)) {
        std::cerr << "Error: Invalid PageRank input.\n";
        return;
    }

    // CSR conversion is preprocessing and is intentionally outside timing.
    CSRGraph csr = convertToCSR(g);

    auto start = std::chrono::high_resolution_clock::now();
    PageRankResult result =
        pageRank(csr, damping, tolerance, maxIterations);
    auto stop = std::chrono::high_resolution_clock::now();

    double ms =
        std::chrono::duration<double, std::milli>(stop - start).count();

    double sum = 0.0;
    int topVertex = 0;

    for (int i = 0; i < g.V; ++i) {
        sum += result.rank[i];
        if (result.rank[i] > result.rank[topVertex])
            topVertex = i;
    }

    std::cout << "\nAlgorithm: PageRank\n";
    std::cout << "Test case: " << testCase << "\n";
    std::cout << "Input: " << path << "\n";
    std::cout << "Vertices: " << g.V << "\n";
    std::cout << "Edges: " << g.E << "\n";
    std::cout << "Damping: " << damping << "\n";
    std::cout << "Tolerance: " << tolerance << "\n";
    std::cout << "Max iterations: " << maxIterations << "\n";
    std::cout << "Vertex ranks:\n";

    for (int i = 0; i < g.V; ++i)
        std::cout << i << " " << result.rank[i] << "\n";

    std::cout << "Top vertex: " << topVertex << "\n";
    std::cout << "Sum of ranks: " << sum << "\n";
    std::cout << "Iterations: " << result.iterations << "\n";
    std::cout << "Converged: "
              << (result.converged ? "true" : "false") << "\n";
    std::cout << "Execution time: " << ms << " ms\n";
}

int main() {
    while (true) {
        std::cout << "\n===== Assignment 4 =====\n";
        std::cout << "1. Vertex Coloring\n";
        std::cout << "2. PageRank\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";

        int algorithm;
        std::cin >> algorithm;

        if (!std::cin) {
            std::cerr << "Error: Invalid input.\n";
            return 1;
        }

        if (algorithm == 0) {
            std::cout << "Exiting.\n";
            return 0;
        }

        if (algorithm != 1 && algorithm != 2) {
            std::cerr << "Error: Enter 1, 2, or 0.\n";
            continue;
        }

        int testCase =
            chooseTest(algorithm == 1 ? "Vertex Coloring" : "PageRank");

        if (testCase < 0) {
            std::cerr << "Error: Enter a test case number from 1 to 5.\n";
            continue;
        }

        if (algorithm == 1)
            runColoring(testCase);
        else
            runPageRank(testCase);
    }
}
