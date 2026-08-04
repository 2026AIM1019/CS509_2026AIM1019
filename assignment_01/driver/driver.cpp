#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace chrono;
namespace fs = filesystem;

#include "../src/matmul.h"

static string trim(const string& s) {
    size_t b = s.find_first_not_of(" \t\r\n");
    if (b == string::npos) return "";
    size_t e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e - b + 1);
}


static string runSolution(istream& in) {

    int p, q, r;
    in >> p >> q >> r;

    vector<vector<int>> A(p, vector<int>(q));
    for (int i = 0; i < p; ++i)
        for (int j = 0; j < q; ++j)
            in >> A[i][j];

    vector<vector<int>> B(q, vector<int>(r));
    for (int i = 0; i < q; ++i)
        for (int j = 0; j < r; ++j)
            in >> B[i][j];

    auto t0 = high_resolution_clock::now();
    vector<vector<int>> C_simple = gemmSimple(A, B);
    auto t1 = high_resolution_clock::now();
    double simpleMillis = duration<double, milli>(t1 - t0).count();


    auto t2 = high_resolution_clock::now();
    vector<vector<int>> C_blocked = gemmBlocked(A, B);
    auto t3 = high_resolution_clock::now();
    double blockedMillis = duration<double, milli>(t3 - t2).count();

   
    bool match = (C_simple == C_blocked);
    if (!match) {
        return string("MISMATCH: Simple and Blocked GEMM differ");
    }

   
    string matrixStr;
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < r; ++j) {
            if (j > 0) matrixStr += ' ';
            matrixStr += to_string(C_blocked[i][j]);
        }
        matrixStr += '\n';
    }

 
    cout << "Algorithm: GEMM Simple\n"
         << "Result matrix:\n"
         << matrixStr
         << "Execution time: " << fixed << setprecision(2) << simpleMillis << " ms\n"
         << "\n"
         << "Algorithm: GEMM Blocking\n"
         << "Result matrix:\n"
         << matrixStr
         << "Execution time: " << fixed << setprecision(2) << blockedMillis << " ms\n";

    return matrixStr;
}

int main() {
    const string inputDir  = "tests/inputs";    
    const string outputDir = "tests/outputs";  

  
    vector<string> testFiles;
    if (fs::exists(inputDir)) {
        for (const auto& entry : fs::directory_iterator(inputDir)) {
            if (entry.path().extension() == ".txt") {
                testFiles.push_back(entry.path().filename().string());
            }
        }
    }
    sort(testFiles.begin(), testFiles.end());

    if (testFiles.empty()) {
        cerr << "No test files found in '" << inputDir << "'.\n"
             << "Add input files like tests/inputs/test_01.txt and\n"
             << "expected outputs like tests/outputs/test_01.txt.\n";
        return 1;
    }

    cout << "Running " << testFiles.size() << " test(s)...\n\n";

    int passed = 0;
    int failed = 0;
    double totalMicros = 0.0;

    // --- 2. Run every test --------------------------------------------------
    for (size_t i = 0; i < testFiles.size(); ++i) {
        const string& name = testFiles[i];

        // Read the input file
        ifstream inFile(inputDir + "/" + name);
        if (!inFile) {
            cerr << "[!] Cannot open input file: " << name << "\n";
            ++failed;
            continue;
        }
        stringstream inBuf;
        inBuf << inFile.rdbuf();
        inFile.close();

        // Read the expected output file (same base name, in outputs/)
        ifstream outFile(outputDir + "/" + name);
        string expected;
        if (outFile) {
            stringstream outBuf;
            outBuf << outFile.rdbuf();
            expected = trim(outBuf.str());
            outFile.close();
        }

        // Run the solution and time it
        auto start = high_resolution_clock::now();
        string actual = trim(runSolution(inBuf));
        auto end = high_resolution_clock::now();
        double micros = duration<double, micro>(end - start).count();
        totalMicros += micros;

        bool ok = (actual == expected);
        if (ok) ++passed; else ++failed;

        cout << "[" << (i + 1) << "/" << testFiles.size() << "] "
             << setw(12) << left << name << " -> "
             << (ok ? "PASSED" : "FAILED")
             << " | Time: " << fixed << setprecision(2)
             << micros << " us)\n";
    }

    cout << "\n================ SUMMARY ================\n"
         << "Total Tests : " << testFiles.size() << "\n"
         << "Passed      : " << passed << "\n"
         << "Failed      : " << failed << "\n"
         << "Total Time  : " << fixed << setprecision(2)
         << totalMicros << " us\n"
         << "Result      : " << (failed == 0 ? "ALL TESTS PASSED"
                                             : "SOME TESTS FAILED")
         << "\n";

    return (failed == 0) ? 0 : 1;
}

