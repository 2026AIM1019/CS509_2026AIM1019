// ============================================================================
// LeetCode-style test driver
// ----------------------------------------------------------------------------
// How it works:
//   1. Scans tests/inputs/ for all *.txt files (test cases are auto-detected,
//      no "number of test cases" header required).
//   2. For each input file "test_N.txt", reads the matching expected output
//      from tests/outputs/test_N.txt.
//   3. Runs your solution function, measures the time taken (microseconds).
//   4. Compares the actual output with the expected output and prints
//      PASSED / FAILED for each test, followed by a summary.
//
// Where to put your solution:
//   Implement your function in ../src/ (e.g. add.cpp) and declare it in the
//   header. Then edit runSolution() below to parse the test-case input and
//   call your function. Everything else in this file can stay unchanged.
//
// Build & run (from the assignment_01/ folder):
//   g++ -O2 -std=c++17 driver/driver.cpp src/add.cpp -o driver/driver
//   ./driver/driver
// ============================================================================

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

// ----------------------------------------------------------------------------
// Utility: strip leading/trailing whitespace from a string.
// ----------------------------------------------------------------------------
static string trim(const string& s) {
    size_t b = s.find_first_not_of(" \t\r\n");
    if (b == string::npos) return "";
    size_t e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e - b + 1);
}

// ----------------------------------------------------------------------------
// runSolution(): the ONLY function you normally need to edit.
//
// `in` is a stream containing one test case's input (from tests/inputs/).
// Read the arguments from it, call your solution, and return the result
// formatted as a string. The returned string is compared against the
// expected output file (after trimming whitespace).
// ----------------------------------------------------------------------------
static string runSolution(istream& in) {
    // --- Parse matrix multiplication inputs ---
    // Input format:
    //   p q r
    //   A (p rows, q integers each)
    //   B (q rows, r integers each)
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

// --- Call both GEMM implementations from src/matmul.h ---
    vector<vector<int>> C_simple  = gemmSimple(A, B);
    vector<vector<int>> C_blocked = gemmBlocked(A, B);

    // --- Verify both implementations produce the same result ---
    bool match = (C_simple == C_blocked);
    if (!match) {
        return string("MISMATCH: Simple and Blocked GEMM differ");
    }

    // --- Format the result matrix as a string ---
    // One row per line, elements separated by spaces.
    string out;
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < r; ++j) {
if (j > 0) out += ' ';
            out += to_string(C_blocked[i][j]);
        }
        out += '\n';
    }
    return out;
}

// ----------------------------------------------------------------------------
// Driver: scan tests, run each case, print results.
// ----------------------------------------------------------------------------
int main() {
    const string inputDir  = "tests/inputs";    // folder with test inputs
    const string outputDir = "tests/outputs";   // folder with expected outputs

    // --- 1. Auto-discover every *.txt input file ---------------------------
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
            //  << "   (Input: " << trim(inBuf.str())
            //  << " | Expected: \n" << expected
            //  << " | Got: \n" << actual
             << " | Time: " << fixed << setprecision(2)
             << micros << " us)\n";
    }

    // --- 3. Summary ---------------------------------------------------------
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

