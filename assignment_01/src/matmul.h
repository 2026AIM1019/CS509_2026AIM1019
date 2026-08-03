#ifndef MATMUL_H
#define MATMUL_H

#include <vector>

// Simple GEMM: direct triple-loop (nested) implementation.
//   A is M x K, B is K x N -> result is M x N.
std::vector<std::vector<int>> gemmSimple(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B);

// Blocking GEMM: uses tiling so data is reused more efficiently in cache.
//   A is M x K, B is K x N -> result is M x N.
//   Must produce the same result matrix as gemmSimple for the same input.
std::vector<std::vector<int>> gemmBlocked(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B);

#endif // MATMUL_H
