#include "matmul.h"

// ----------------------------------------------------------------------------
// Simple GEMM: direct nested-loop implementation.
//   C[i][j] = sum over k of A[i][k] * B[k][j]
// ----------------------------------------------------------------------------
std::vector<std::vector<int>> gemmSimple(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B) {

    int M = A.size();                 // rows of A
    int K = B.size();                 // cols of A == rows of B
    int N = B[0].size();              // cols of B

    // Result is M x N, initialized to zeros.
    std::vector<std::vector<int>> C(M, std::vector<int>(N, 0));

    // Simple triple-loop matrix multiplication.
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < K; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

// ----------------------------------------------------------------------------
// Blocking GEMM: tiled implementation for better cache reuse.
//   The matrices are divided into BLOCK x BLOCK tiles. Iterating over
//   tiles keeps a block of A and a block of B resident in cache while
//   accumulating into a block of C, reducing cache misses.
// ----------------------------------------------------------------------------
std::vector<std::vector<int>> gemmBlocked(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B) {

    const int BLOCK = 32;             // tile size

    int M = A.size();                 // rows of A
    int K = B.size();                 // cols of A == rows of B
    int N = B[0].size();              // cols of B

    // Result is M x N, initialized to zeros.
    std::vector<std::vector<int>> C(M, std::vector<int>(N, 0));

    // Tiled matrix multiplication.
    for (int i0 = 0; i0 < M; i0 += BLOCK) {
        for (int j0 = 0; j0 < N; j0 += BLOCK) {
            for (int k0 = 0; k0 < K; k0 += BLOCK) {
                // Process the current block (i0..i0+BLOCK) x (j0..j0+BLOCK)
                // using A block (i0.., k0..) and B block (k0.., j0..).
                int iEnd = std::min(i0 + BLOCK, M);
                int jEnd = std::min(j0 + BLOCK, N);
                int kEnd = std::min(k0 + BLOCK, K);

                for (int i = i0; i < iEnd; ++i) {
                    for (int j = j0; j < jEnd; ++j) {
                        int sum = 0;
                        for (int k = k0; k < kEnd; ++k) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] += sum;
                    }
                }
            }
        }
    }

    return C;
}
