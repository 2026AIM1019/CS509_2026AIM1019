# TODO - Matrix Multiplication (CS509 Assignment 01)

- [x] Create src/matmul.h
- [x] Create src/matmul.cpp
- [x] Rewrite driver/driver.cpp runSolution() to parse matrices and call matmul
- [x] Update Makefile SRC to use src/matmul.cpp
- [x] Rewrite tests/inputs/test_01.txt
- [x] Rewrite tests/outputs/test_01.txt
- [x] Rewrite tests/inputs/test_02.txt
- [x] Rewrite tests/outputs/test_02.txt
- [x] Remove old src/add.cpp / src/add.h
- [x] Build and run tests (make clean && make run) - ALL TESTS PASSED
- [x] Added more test cases of different matrix sizes:
      test_03 (1x1 x 1x1), test_04 (3x2 x 2x4), test_05 (1x3 x 3x1),
      test_06 (3x3 x 3x3), test_07 (4x1 x 1x4) - ALL TESTS PASSED
- [x] Implemented Simple GEMM (gemmSimple) and Blocking GEMM (gemmBlocked)
- [x] Driver verifies both GEMM implementations produce identical results
- [x] Driver outputs the result from gemmBlocked
- [x] All 7 tests PASS (Simple and Blocked GEMM match, output uses Blocked)
