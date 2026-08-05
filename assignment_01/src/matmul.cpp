#include "matmul.h"
using namespace std;


vector<vector<int>> gemmSimple(
    const vector<vector<int>>& A,
    const vector<vector<int>>& B) {

    int M = A.size();                 
    int K = B.size();                
    int N = B[0].size();         

    vector<vector<int>> C(M, vector<int>(N, 0));

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < K; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}


vector<vector<int>> gemmBlocked(
    const vector<vector<int>>& A,
    const vector<vector<int>>& B) {

    const int BLOCK = 32;             

    int M = A.size();                
    int K = B.size();               
    int N = B[0].size();        

   
    vector<vector<int>> C(M, vector<int>(N, 0));

  
    for (int i0 = 0; i0 < M; i0 += BLOCK) {
        for (int j0 = 0; j0 < N; j0 += BLOCK) {
            for (int k0 = 0; k0 < K; k0 += BLOCK) {
                
                int iEnd = min(i0 + BLOCK, M);
                int jEnd = min(j0 + BLOCK, N);
                int kEnd = min(k0 + BLOCK, K);

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
