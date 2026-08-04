#ifndef MATMUL_H
#define MATMUL_H
using namespace std;

#include <vector>


vector<vector<int>> gemmSimple(
    const vector<vector<int>>& A,
    const vector<vector<int>>& B);


vector<vector<int>> gemmBlocked(
    const vector<vector<int>>& A,
    const vector<vector<int>>& B);

#endif // MATMUL_H
