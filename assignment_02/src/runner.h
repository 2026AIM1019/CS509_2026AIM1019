#ifndef RUNNER_H
#define RUNNER_H

#include <functional>
#include <string>

#include "graph.h"

using namespace std;

void runAlgorithm(
    const string &algorithmName,
    function<double(const CSRGraph &, int, const string &)> executor);


void runBellmanFord();
void runFloydWarshall();

#endif
