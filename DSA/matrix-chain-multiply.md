# Matrix Chain Multiplication (MCM) – Complete DSA Interview Preparation

Important Dynamic Programming Topic Medium–Hard

Matrix Chain Multiplication is one of the most important problems in Dynamic Programming (DP). It is frequently used to test your understanding of:

- Recursion and recursion trees.
- Memoization (Top-Down DP).
- Tabulation (Bottom-Up DP).
- Partition DP.
- Optimal substructure and overlapping subproblems.
- Finding the optimal order of operations.

We'll cover the fundamental problem, all important approaches, and commonly expected interview variations.

## 1. Understand Matrix Chain Multiplication

### Problem statement

You are given an array `arr[]` of size `N`, representing the dimensions of a sequence of matrices.

You have to find the minimum number of scalar multiplications required to multiply all the matrices.

The important point is that you cannot change the order of matrices, but you can change the order in which you perform the multiplications by placing parentheses differently.

### Example

Suppose:

cpp

```cpp
arr[] = {10, 20, 30, 40};
```

This represents three matrices:

- A1 = 10 × 20
- A2 = 20 × 30
- A3 = 30 × 40

We need to calculate:

$$
A_1 \times A_2 \times A_3
$$

There are two possible ways.

Option 1: (A1 × A2) × A3

First multiplication:

$$
10 \times 20 \times 30 = 6000
$$

The resulting matrix has dimensions 10 × 30.

Second multiplication:

$$
10 \times 30 \times 40 = 12000
$$

Total:

$$
6000 + 12000 = 18000
$$

Option 2: A1 × (A2 × A3)

First multiplication:

$$
20 \times 30 \times 40 = 24000
$$

The resulting matrix has dimensions 20 × 40.

Second multiplication:

$$
10 \times 20 \times 40 = 8000
$$

Total:

$$
24000 + 8000 = 32000
$$

Optimal Answer$$
\boxed{18000}
$$

Therefore, the minimum number of scalar multiplications is 18000.

Matrix Chain Multiplication | (DP-48) - Tutorial

[takeuforward.org](<https://takeuforward.org/dynamic-programming/matrix-chain-multiplication-dp-48?utm_source=chatgpt.com>)

## 2. Important Concept: How to Identify Matrices

If the dimensions array is:

cpp

```cpp
arr[] = {10, 20, 30, 40, 50};
```

Then the matrices are:

| Matrix | Dimensions |
| --- | --- |
| A1 | 10 × 20 |
| A2 | 20 × 30 |
| A3 | 30 × 40 |
| A4 | 40 × 50 |

Remember:

If there are N elements in the dimensions array, there are N-1 matrices.

This is extremely important when writing the recursive function.

## 3. Question 1 – Matrix Chain Multiplication (Basic Problem)

Easy to Medium Must Prepare

Problem statement:

Given an array `arr[]` representing the dimensions of N-1 matrices, find the minimum number of scalar multiplications needed to multiply the complete chain of matrices.

### Input

cpp

```cpp
arr[] = {10, 20, 30, 40};
```

### Output

cpp

```cpp
18000
```

### Approach 1: Recursion (Brute Force)

Intuition:

We try every possible position where we can split the matrix chain.

For example:

text

```text
A1 A2 A3 A4
```

We can divide it into:

text

```text
A1 | A2 A3 A4
A1 A2 | A3 A4
A1 A2 A3 | A4
```

For every partition:

1. Calculate the minimum cost of the left partition.
2. Calculate the minimum cost of the right partition.
3. Calculate the cost of multiplying the two resulting matrices.
4. Take the minimum among all partitions.

### Recurrence relation

Let:

$$
f(i,j)
$$

represent the minimum multiplication cost of matrices from index i to j.

Then:

$$
f(i,j)=\min_{i\leq k<j}
\begin{cases}
f(i,k)+f(k+1,j)\\
+arr[i-1]\times arr[k]\times arr[j]
\end{cases}
$$

Base case:

$$
f(i,j)=0 \quad \text{if } i=j
$$

### C++ Code – Recursive Solution

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

// Returns minimum multiplication cost
// for matrices from i to j.
int solve(int i, int j, vector<int>& arr) {

    // Only one matrix remains.
    // No multiplication is required.
    if (i == j) {
        return 0;
    }

    int mini = INT_MAX;

    // Try every possible partition.
    for (int k = i; k < j; k++) {

        // Cost of multiplying left and right parts
        int steps =
            solve(i, k, arr) +
            solve(k + 1, j, arr) +
            arr[i - 1] * arr[k] * arr[j];

        // Store minimum cost.
        mini = min(mini, steps);
    }

    return mini;
}

int matrixMultiplication(vector<int>& arr) {

    int n = arr.size();

    // There are n-1 matrices.
    // Matrix indices are 1 to n-1.
    return solve(1, n - 1, arr);
}

int main() {

    vector<int> arr = {10, 20, 30, 40};

    cout << matrixMultiplication(arr);

    return 0;
}
```

Output:

text

```text
18000
```

Complexity:

- Time Complexity: Exponential (approximately $O(2^N)$ as a loose upper bound).
- Auxiliary Space: $O(N)$ recursion stack.

The recursive solution calculates many subproblems repeatedly. We can optimize it using DP.

### Approach 2: Memoization (Top-Down DP)

Very ImportantProblem with recursion:

Suppose we calculate:

cpp

```cpp
solve(1, 3)
```

During its execution, the same subproblems may be calculated multiple times.

For example:

text

```text
solve(1, 3)
    solve(1, 1)
    solve(2, 3)
        solve(2, 2)
        solve(3, 3)
```

Different partitions can lead to repeated calculations.

Solution: Store the answer of each subproblem in a DP array.

We use:

cpp

```cpp
dp[i][j]
```

to store the minimum multiplication cost between matrices i and j.

### C++ Code – Memoization

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

long long solve(int i, int j,
                vector<int>& arr,
                vector<vector<long long>>& dp) {

    // Base case: One matrix requires no multiplication.
    if (i == j) {
        return 0;
    }

    // If already calculated, return stored answer.
    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    long long mini = LLONG_MAX;

    // Try all possible partition positions.
    for (int k = i; k < j; k++) {

        long long steps =
            solve(i, k, arr, dp) +
            solve(k + 1, j, arr, dp) +
            1LL * arr[i - 1] * arr[k] * arr[j];

        mini = min(mini, steps);
    }

    // Store and return the result.
    return dp[i][j] = mini;
}

long long matrixMultiplication(vector<int>& arr) {

    int n = arr.size();

    vector<vector<long long>> dp(
        n, vector<long long>(n, -1)
    );

    return solve(1, n - 1, arr, dp);
}

int main() {

    vector<int> arr = {10, 20, 30, 40};

    cout << matrixMultiplication(arr);

    return 0;
}
```

Output:

text

```text
18000
```

Complexity:

- Time Complexity: $O(N^3)$
- Space Complexity: $O(N^2)$ for DP + $O(N)$ recursion stack.

### Approach 3: Tabulation (Bottom-Up DP)

Most Important for InterviewsIntuition:

Instead of solving the problem recursively, we calculate smaller subproblems first and gradually solve larger subproblems.

We initialize:

cpp

```cpp
dp[i][j] = 0;
```

For every single matrix, no multiplication is needed.

Then we calculate answers for chains of length 2, 3, 4, and so on.

### C++ Code – Tabulation

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

long long matrixMultiplication(vector<int>& arr) {

    int n = arr.size();

    // dp[i][j] = minimum cost of multiplying
    // matrices from i to j.
    vector<vector<long long>> dp(
        n, vector<long long>(n, 0)
    );

    // len represents the number of matrices
    // in the current chain.
    for (int len = 2; len <= n - 1; len++) {

        // Starting matrix index.
        for (int i = 1; i + len - 1 <= n - 1; i++) {

            // Ending matrix index.
            int j = i + len - 1;

            dp[i][j] = LLONG_MAX;

            // Try every possible partition.
            for (int k = i; k < j; k++) {

                long long steps =
                    dp[i][k] +
                    dp[k + 1][j] +
                    1LL * arr[i - 1] * arr[k] * arr[j];

                // Update minimum multiplication cost.
                dp[i][j] = min(dp[i][j], steps);
            }
        }
    }

    return dp[1][n - 1];
}

int main() {

    vector<int> arr = {10, 20, 30, 40};

    cout << matrixMultiplication(arr);

    return 0;
}
```

Output:

text

```text
18000
```

Complexity:

- Time Complexity: $O(N^3)$
- Space Complexity: $O(N^2)$

### Understanding the Tabulation Loop

This is the most important part:

cpp

```cpp
for (int len = 2; len <= n - 1; len++)
```

Why start with 2?

Because a single matrix has zero multiplication cost.

For example, with:

cpp

```cpp
arr = {10, 20, 30, 40};
```

The DP table is:

DP table (matrix-chain indices)

| i / j | 1 | 2 | 3 |
| --- | --- | --- | --- |
| 1 | 0 | 6000 | 18000 |
| 2 | — | 0 | 24000 |
| 3 | — | — | 0 |

dp\[1\]\[3\] = 18000 is our final answer.

Remember this MCM pattern:

cpp

```cpp
for (int i = n - 1; i >= 1; i--) {

    for (int j = i + 1; j < n; j++) {

        int mini = INT_MAX;

        for (int k = i; k < j; k++) {

            // Left cost + Right cost + Current cost

        }
    }
}
```

This is another valid bottom-up ordering because smaller intervals are solved before larger intervals.

## 4. Question 2 – Print the Optimal Parenthesization

Medium–HardProblem statement:

Given the dimensions of a matrix chain, find not only the minimum multiplication cost but also the optimal order of multiplication.

For example:

cpp

```cpp
arr[] = {10, 20, 30, 40};
```

Expected output:

text

```text
Minimum Cost: 18000
Optimal Order: ((A1 x A2) x A3)
```

### Approach

We use two DP tables:

- `dp[i][j]`: Minimum multiplication cost.
- `split[i][j]`: The position where the optimal partition occurs.

After filling the DP table, we use recursion to reconstruct the optimal parenthesization.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

vector<vector<long long>> dp;
vector<vector<int>> splitPoint;

// Calculate minimum multiplication cost.
long long solve(vector<int>& arr, int i, int j) {

    if (i == j) {
        return 0;
    }

    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    long long mini = LLONG_MAX;

    for (int k = i; k < j; k++) {

        long long cost =
            solve(arr, i, k) +
            solve(arr, k + 1, j) +
            1LL * arr[i - 1] * arr[k] * arr[j];

        if (cost < mini) {

            mini = cost;

            // Remember the best splitting position.
            splitPoint[i][j] = k;
        }
    }

    return dp[i][j] = mini;
}

// Reconstruct optimal parenthesization.
string buildOrder(int i, int j) {

    // Single matrix: no parentheses needed.
    if (i == j) {
        return "A" + to_string(i);
    }

    int k = splitPoint[i][j];

    string left = buildOrder(i, k);
    string right = buildOrder(k + 1, j);

    return "(" + left + " x " + right + ")";
}

int main() {

    vector<int> arr = {10, 20, 30, 40};

    int n = arr.size();

    dp.assign(n, vector<long long>(n, -1));
    splitPoint.assign(n, vector<int>(n, -1));

    long long ans = solve(arr, 1, n - 1);

    cout << "Minimum Cost: " << ans << endl;

    cout << "Optimal Order: "
         << buildOrder(1, n - 1) << endl;

    return 0;
}
```

Output:

text

```text
Minimum Cost: 18000
Optimal Order: ((A1 x A2) x A3)
```

Complexity:

- Time Complexity: $O(N^3)$ for DP, plus $O(N)$ for reconstructing the order.
- Space Complexity: $O(N^2)$ for DP and split tables.

## 5. Question 3 – Count the Number of Ways to Multiply a Matrix Chain

Medium–HardProblem statement:

Given N-1 matrices, find the total number of different ways to fully parenthesize their multiplication while preserving their original order.

For example:

cpp

```cpp
arr[] = {10, 20, 30, 40};
```

There are three matrices:

text

```text
A1, A2, A3
```

Possible parenthesizations:

text

```text
(A1 x A2) x A3

A1 x (A2 x A3)
```

Output:

text

```text
2
```

### Approach

This is similar to MCM, but instead of minimizing the cost, we count all possible partitions.

For every possible split:

$$
ways(i,j)=\sum_{k=i}^{j-1}ways(i,k)\times ways(k+1,j)
$$

Base case:

$$
ways(i,i)=1
$$

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

long long countWays(int i, int j,
                    vector<vector<long long>>& dp) {

    // A single matrix has exactly one arrangement.
    if (i == j) {
        return 1;
    }

    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    long long ways = 0;

    // Try every possible partition.
    for (int k = i; k < j; k++) {

        long long left = countWays(i, k, dp);
        long long right = countWays(k + 1, j, dp);

        // Combine left and right parenthesizations.
        ways += left * right;
    }

    return dp[i][j] = ways;
}

int main() {

    vector<int> arr = {10, 20, 30, 40};

    int n = arr.size();

    vector<vector<long long>> dp(
        n, vector<long long>(n, -1)
    );

    cout << countWays(1, n - 1, dp);

    return 0;
}
```

Output:

text

```text
2
```

The number of ways for a chain of m matrices is the Catalan number $C_{m-1}$.

## 6. Question 4 – Minimum Cost to Cut a Stick

Medium–Hard Frequently Asked

Problem statement:

You are given a stick of length `n` and an array `cuts[]` containing positions where the stick must be cut.

Every time you make a cut, the cost is equal to the length of the stick segment being cut.

Find the minimum total cost required to perform all cuts.

### Example

cpp

```cpp
n = 7;
cuts = {1, 3, 4, 5};
```

Output:

text

```text
16
```

### Approach / Intuition

This is very similar to Matrix Chain Multiplication.

The difference is that instead of dividing a matrix chain, we divide a stick into smaller segments.

First:

- Add `0` and `n` to the cuts array.
- Sort the cuts.
- Consider each interval between two boundaries.
- Try every cut inside the interval.
- Calculate the cost and take the minimum.

Recurrence:

$$
dp[i][j]=\min_{k=i}^{j}
\left(dp[i][k-1]+dp[k+1][j]+cuts[j+1]-cuts[i-1]\right)
$$

### C++ Code – Memoization

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int solve(int i, int j, vector<int>& cuts,
          vector<vector<int>>& dp) {

    // No cuts left in this interval.
    if (i > j) {
        return 0;
    }

    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    int mini = INT_MAX;

    // Try making each cut first.
    for (int k = i; k <= j; k++) {

        // Current segment length is cuts[j+1] - cuts[i-1].
        int cost = cuts[j + 1] - cuts[i - 1]
                 + solve(i, k - 1, cuts, dp)
                 + solve(k + 1, j, cuts, dp);

        mini = min(mini, cost);
    }

    return dp[i][j] = mini;
}

int minCost(int n, vector<int>& c) {

    c.push_back(0);
    c.push_back(n);

    sort(c.begin(), c.end());

    int m = c.size();

    vector<vector<int>> dp(
        m, vector<int>(m, -1)
    );

    return solve(1, m - 2, c, dp);
}

int main() {

    int n = 7;
    vector<int> cuts = {1, 3, 4, 5};

    cout << minCost(n, cuts);

    return 0;
}
```

Output:

text

```text
16
```

Complexity:

- Time: $O(C^3)$
- Space: $O(C^2)$, where C is the number of cuts (excluding the boundaries).

Interview takeaway: Whenever you see a problem where you must choose which position to cut first and recursively solve the left and right intervals, think about MCM / Partition DP.

## 7. Question 5 – Burst Balloons

Hard Very Important

Problem statement:

You are given an array of balloons. Each balloon has a number written on it.

When you burst balloon `i`, you receive coins equal to:

$$
nums[left]\times nums[i]\times nums[right]
$$

Here, `left` and `right` are the nearest balloons that have not yet been burst.

After bursting a balloon, it disappears.

Find the maximum number of coins you can collect by bursting all balloons in an optimal order.

### Example

cpp

```cpp
nums = {3, 1, 5, 8};
```

Output:

text

```text
167
```

### Approach / Intuition

This is a classic MCM variation.

Important trick: Instead of deciding which balloon to burst first, decide which balloon to burst last in a particular interval.

Why?

Because when we choose the last balloon to burst in an interval, its left and right neighbors are fixed.

First, add 1 at both ends:

cpp

```cpp
nums = {1, 3, 1, 5, 8, 1};
```

Then try every balloon `k` as the last balloon in interval `[i, j]`.

Recurrence:

$$
dp[i][j]=\max_{k=i}^{j}
\begin{cases}
dp[i][k-1]+dp[k+1][j]\\
+nums[i-1]\times nums[k]\times nums[j+1]
\end{cases}
$$

### C++ Code – Memoization

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int solve(int i, int j, vector<int>& nums,
          vector<vector<int>>& dp) {

    // No balloons remain in this interval.
    if (i > j) {
        return 0;
    }

    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    int maxi = 0;

    // Assume k is the LAST balloon to be burst.
    for (int k = i; k <= j; k++) {

        // Coins received when bursting balloon k last.
        int coins =
            nums[i - 1] * nums[k] * nums[j + 1];

        // Maximum coins from left and right intervals.
        int total =
            solve(i, k - 1, nums, dp) +
            solve(k + 1, j, nums, dp) +
            coins;

        maxi = max(maxi, total);
    }

    return dp[i][j] = maxi;
}

int maxCoins(vector<int>& nums) {

    int n = nums.size();

    // Add boundary balloons.
    nums.insert(nums.begin(), 1);
    nums.push_back(1);

    vector<vector<int>> dp(
        n + 2, vector<int>(n + 2, -1)
    );

    return solve(1, n, nums, dp);
}

int main() {

    vector<int> nums = {3, 1, 5, 8};

    cout << maxCoins(nums);

    return 0;
}
```

Output:

text

```text
167
```

Complexity:

- Time: $O(N^3)$
- Space: $O(N^2)$ + recursion stack.

Important interview trick: In many partition DP problems, deciding the first operation makes the subproblem boundaries difficult to determine. Try deciding the last operation instead.

## 8. Question 6 – Minimum Score Triangulation of Polygon

Medium–HardProblem statement:

You are given an array `values[]`, representing the values of vertices of a convex polygon.

You must divide the polygon into triangles by drawing non-intersecting diagonals.

The score of a triangle with vertices `i`, `j`, and `k` is:

$$
values[i]\times values[j]\times values[k]
$$

Find the minimum total score of the triangulation.

### Example

cpp

```cpp
values = {1, 2, 3};
```

Output:

text

```text
6
```

Because there is only one triangle:

$$
1\times2\times3=6
$$

### Approach

This is also an interval partition DP problem.

For each interval `[i, j]`, select a vertex `k` between them to form a triangle.

The recurrence is:

$$
dp[i][j]=\min_{i<k<j}
\begin{cases}
dp[i][k]+dp[k][j]\\
+values[i]\times values[k]\times values[j]
\end{cases}
$$

### C++ Code – Tabulation

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int minScoreTriangulation(vector<int>& values) {

    int n = values.size();

    vector<vector<int>> dp(
        n, vector<int>(n, 0)
    );

    // Solve smaller intervals first.
    for (int len = 3; len <= n; len++) {

        for (int i = 0; i + len <= n; i++) {

            int j = i + len - 1;

            dp[i][j] = INT_MAX;

            // Select the third vertex of the triangle.
            for (int k = i + 1; k < j; k++) {

                int score =
                    dp[i][k] +
                    dp[k][j] +
                    values[i] * values[k] * values[j];

                dp[i][j] = min(dp[i][j], score);
            }
        }
    }

    return dp[0][n - 1];
}

int main() {

    vector<int> values = {1, 2, 3};

    cout << minScoreTriangulation(values);

    return 0;
}
```

Complexity:

- Time: $O(N^3)$
- Space: $O(N^2)$

## 9. Question 7 – Boolean Parenthesization

Hard Important DP Problem

Problem statement:

You are given a boolean expression containing:

- `T` – True
- `F` – False
- `&` – AND
- `|` – OR
- `^` – XOR

You have to find the number of ways to parenthesize the expression such that its final result evaluates to True.

### Example

cpp

```cpp
expression = "T|F&T";
```

Output:

text

```text
2
```

Possible valid parenthesizations:

text

```text
(T | F) & T = True

T | (F & T) = True
```

Both evaluate to True.

### Approach

Unlike standard MCM, here we need to maintain two DP values:

- `trueWays[i][j]`: Number of ways to obtain True.
- `falseWays[i][j]`: Number of ways to obtain False.

For each operator, try all possible partitions and combine the left and right results according to the operator.

### C++ Code – Memoization

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

long long dp[205][205][2];

long long solve(int i, int j, int isTrue,
                string& s) {

    // Invalid expression interval.
    if (i > j) {
        return 0;
    }

    // Only one boolean operand.
    if (i == j) {

        if (isTrue) {
            return s[i] == 'T';
        }

        return s[i] == 'F';
    }

    if (dp[i][j][isTrue] != -1) {
        return dp[i][j][isTrue];
    }

    long long ways = 0;

    // Operators are placed at odd indices.
    for (int k = i + 1; k < j; k += 2) {

        char op = s[k];

        long long LT = solve(i, k - 1, 1, s);
        long long LF = solve(i, k - 1, 0, s);

        long long RT = solve(k + 1, j, 1, s);
        long long RF = solve(k + 1, j, 0, s);

        // Combine the results according to operator.
        if (op == '&') {

            if (isTrue) {
                ways = (ways + LT * RT) % MOD;
            }
            else {
                ways = (ways + LT * RF
                              + LF * RT
                              + LF * RF) % MOD;
            }
        }

        else if (op == '|') {

            if (isTrue) {
                ways = (ways + LT * RT
                              + LT * RF
                              + LF * RT) % MOD;
            }
            else {
                ways = (ways + LF * RF) % MOD;
            }
        }

        else if (op == '^') {

            if (isTrue) {
                ways = (ways + LT * RF
                              + LF * RT) % MOD;
            }
            else {
                ways = (ways + LT * RT
                              + LF * RF) % MOD;
            }
        }
    }

    return dp[i][j][isTrue] = ways;
}

int main() {

    string s = "T|F&T";

    memset(dp, -1, sizeof(dp));

    cout << solve(0, s.size() - 1, 1, s);

    return 0;
}
```

Output:

text

```text
2
```

Complexity:

- Time: $O(N^3)$
- Space: $O(N^2)$ for the DP states, plus recursion stack.

## 10. Question 8 – Palindrome Partitioning II (Minimum Cuts)

Medium–HardProblem statement:

Given a string `s`, divide it into substrings such that every substring is a palindrome.

Find the minimum number of cuts required.

### Example

cpp

```cpp
s = "aab";
```

Output:

text

```text
1
```

Explanation:

text

```text
"aa" | "b"
```

Both substrings are palindromes, and only one cut is required.

### Approach

Try every possible partition of the string.

For every starting index `i`, try every ending index `j`.

If the substring `s[i...j]` is a palindrome, recursively solve the remaining suffix.

### C++ Code – Memoization

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

bool isPalindrome(string& s, int i, int j) {

    while (i < j) {

        if (s[i] != s[j]) {
            return false;
        }

        i++;
        j--;
    }

    return true;
}

int solve(int i, string& s, vector<int>& dp) {

    // Entire string has been partitioned.
    if (i == s.size()) {
        return 0;
    }

    if (dp[i] != -1) {
        return dp[i];
    }

    int mini = INT_MAX;

    for (int j = i; j < s.size(); j++) {

        // Partition only when current substring
        // is a palindrome.
        if (isPalindrome(s, i, j)) {

            int cost = 1 + solve(j + 1, s, dp);

            mini = min(mini, cost);
        }
    }

    return dp[i] = mini;
}

int minCut(string s) {

    int n = s.size();

    vector<int> dp(n, -1);

    // The final partition does not need a cut.
    return solve(0, s, dp) - 1;
}

int main() {

    string s = "aab";

    cout << minCut(s);

    return 0;
}
```

Output:

text

```text
1
```

Complexity:

- Time: $O(N^3)$ with the palindrome-checking implementation above.
- Space: $O(N)$ for the DP and recursion stack.

## 11. More Important MCM-Based Interview Questions

Apart from the questions above, prepare these variations too. They test the same partition DP thinking, although their recurrence relations may differ.

| No. | Coding question | Difficulty | Main concept |
| --- | --- | --- | --- |
| 9 | Minimum Cost to Merge Stones | Hard | Interval DP |
| 10 | Strange Printer | Hard | Interval DP |
| 11 | Remove Boxes | Hard | 3D DP |
| 12 | Scramble String | Hard | Partition DP |
| 13 | Optimal Binary Search Tree | Hard | Interval DP |
| 14 | Egg Dropping Puzzle | Hard | Minimax DP |
| 15 | Minimum Cost Tree From Leaf Values | Medium | Interval DP |
| 16 | Minimum Insertion Steps to Make a String Palindrome | Medium | String DP |
| 17 | Minimum Cost to Make Two Strings Identical | Medium | String DP |
| 18 | Maximum Value of Expression by Parenthesization | Medium–Hard | Partition DP |

### Particularly important problems to practice

Burst Balloons

LeetCode 312 · Hard

[Practice problem](<https://leetcode.com/problems/burst-balloons/?utm_source=chatgpt.com>)

Minimum Cost to Cut a Stick

LeetCode 1547 · Hard

[Practice problem](<https://leetcode.com/problems/minimum-cost-to-cut-a-stick/?utm_source=chatgpt.com>)

Minimum Score Triangulation of Polygon

LeetCode 1039 · Medium

[Practice problem](<https://leetcode.com/problems/minimum-score-triangulation-of-polygon/?utm_source=chatgpt.com>)

Scramble String

LeetCode 87 · Hard

[Practice problem](<https://leetcode.com/problems/scramble-string/?utm_source=chatgpt.com>)

## 12. Most Important MCM Pattern to Remember

Whenever you encounter
