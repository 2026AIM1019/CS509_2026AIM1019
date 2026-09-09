#ifndef COLOR_H
#define COLOR_H
#include "graph.h"

vector<int> greedyWelshPowell(const CSRGraph&);

// Checks if the coloring is valid. Returns true if valid, false otherwise.
bool validColoring(const CSRGraph&, const vector<int>&);

#endif
