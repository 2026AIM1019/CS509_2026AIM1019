#ifndef GRAPH_IO_H
#define GRAPH_IO_H

#include <string>
#include "graph.h"

using namespace std;

Graph readGraph(const string &filename);

MatrixGraph readMatrixGraph(const string &filename);

#endif
