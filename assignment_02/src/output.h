#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>
#include "graph.h"

using namespace std;

void writeBellmanFordOutput(const string &filename,
                            const BellmanFordResult &result,
                            int source);

void writeFloydWarshallOutput(const string &filename,
                              const FloydWarshallResult &result);

#endif
