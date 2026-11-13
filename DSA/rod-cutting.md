# Rod Cutting Problem – Complete DSA Interview Preparation in C++

Very Important DP Topic Easy to Hard

The Rod Cutting Problem is one of the most important problems in Dynamic Programming. It is closely related to the Unbounded Knapsack Pattern.

It is frequently asked in:

- Technical interviews and placement exams.
- Dynamic Programming coding rounds.
- GeeksforGeeks and other coding platforms.
- Questions involving optimization, recursion, and knapsack.

We'll cover the basic problem, all major approaches, code with comments, dry runs, complexity analysis, and important variations.

## 1. Understanding the Rod Cutting Problem

### Problem statement

You are given a rod of length `N` and an array `price[]`, where:

- `price[i]` represents the price of a rod piece of length `i+1`.
- You can cut the rod into smaller pieces.
- You can make as many cuts as you want.
- Your task is to find the maximum obtainable price by cutting the rod optimally.

Important: You can use the same piece length multiple times.

### Example 1

text

```text
Input:
N = 8

price[] = {1, 5, 8, 9, 10, 17, 17, 20}

Output:
22
```

Explanation:

The rod has length 8.

One optimal way is:

text

```text
Length 2 + Length 6
```

Their prices are:

text

```text
price[2] = 5
price[6] = 17

Total = 5 + 17 = 22
```

Another optimal way is:

text

```text
Length 2 + Length 2 + Length 2 + Length 2

Total = 5 + 5 + 5 + 5 = 20
```

Therefore, the maximum obtainable price is:

Answer: 22### Visual understanding

PPT - Unit 4: Dynamic Programming PowerPoint Presentation, free download - ID:1869400

[slideserve.com](<https://www.slideserve.com/zuri/unit-4-dynamic-programming?utm_source=chatgpt.com>)

### Important observation

This problem is an Unbounded Knapsack problem because we can choose the same rod length multiple times.

For example, if we choose a piece of length 2, we can choose another piece of length 2 again.

## 2. Recursive Approach (Brute Force)

### Problem statement

Find the maximum obtainable price by trying every possible way to cut the rod.

### Intuition

For every rod length, we have two choices:

1. Take the current piece length and reduce the remaining rod length.
2. Skip the current piece length and move to the next smaller piece.

This is similar to the Unbounded Knapsack problem.

We define:

`solve(index, N)`

Where:

- `index` represents the current available piece length.
- `N` represents the remaining rod length.

### Recurrence relation

For each piece length:

Take:

$$
price[index]+solve(index,N-(index+1))
$$

We stay at the same index because we can take the same length again.

Not Take:

$$
solve(index-1,N)
$$

We move to the previous piece length.

Therefore:

$$
dp[index][N]=\max(Take,NotTake)
$$

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

// Recursive function to find maximum obtainable price
int solve(int index, int N, vector<int>& price) {

    // Base case:
    // Only length 1 pieces are available.
    if (index == 0) {

        // We must use N pieces of length 1.
        return N * price[0];
    }

    // Option 1: Do not take current piece length
    int notTake = solve(index - 1, N, price);

    // Option 2: Take current piece length
    int take = INT_MIN;

    // Current piece length is index + 1
    int rodLength = index + 1;

    // Check whether the piece fits in remaining rod
    if (rodLength <= N) {

        // Stay at same index because
        // we can take this piece again.
        take = price[index] +
               solve(index, N - rodLength, price);
    }

    // Return maximum profit
    return max(take, notTake);
}

int cutRod(vector<int>& price, int N) {

    return solve(N - 1, N, price);
}

int main() {

    vector<int> price = {
        1, 5, 8, 9, 10, 17, 17, 20
    };

    int N = 8;

    cout << cutRod(price, N);

    return 0;
}
```

Output:

text

```text
22
```

### Complexity analysis

- Time Complexity: Exponential, upper bounded by $O(2^N)$.
- Auxiliary Space: $O(N)$ recursion stack.

Problem: The same subproblems are calculated repeatedly. We can optimize this using memoization.

## 3. Memoization (Top-Down Dynamic Programming)

Important Interview Approach### Problem statement

Solve the Rod Cutting Problem using recursion and memoization to avoid recalculating the same subproblems.

### Intuition

We create a 2D DP array:

cpp

```cpp
dp[index][N]
```

Meaning:

`dp[index][N]` stores the maximum obtainable price using piece lengths from `1` to `index+1` to fill a rod of length `N`.

Before calculating an answer, check whether it has already been calculated.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int solve(int index, int N,
          vector<int>& price,
          vector<vector<int>>& dp) {

    // Base case: Only length 1 is available
    if (index == 0) {
        return N * price[0];
    }

    // Return already calculated answer
    if (dp[index][N] != -1) {
        return dp[index][N];
    }

    // Option 1: Skip current piece length
    int notTake = solve(index - 1, N, price, dp);

    // Option 2: Take current piece length
    int take = INT_MIN;

    int rodLength = index + 1;

    if (rodLength <= N) {

        // Same index because this is unbounded knapsack
        take = price[index] +
               solve(index, N - rodLength, price, dp);
    }

    // Store the maximum answer
    return dp[index][N] = max(take, notTake);
}

int cutRod(vector<int>& price, int N) {

    vector<vector<int>> dp(
        N, vector<int>(N + 1, -1)
    );

    return solve(N - 1, N, price, dp);
}

int main() {

    vector<int> price = {
        1, 5, 8, 9, 10, 17, 17, 20
    };

    int N = 8;

    cout << cutRod(price, N);

    return 0;
}
```

Output:

text

```text
22
```

### Complexity analysis

- Time Complexity: $O(N^2)$
- Space Complexity: $O(N^2)$ for DP + $O(N)$ recursion stack.

## 4. Tabulation (Bottom-Up Dynamic Programming)

Most Important Approach### Problem statement

Solve the Rod Cutting Problem using an iterative DP approach without recursion.

### Intuition

We use a 2D DP array:

$$
dp[i][j]
$$

Meaning:

- `i` = number of available piece lengths.
- `j` = remaining rod length.
- `dp[i][j]` = maximum profit obtainable.

We consider two choices:

1. Not Take

$$
dp[i-1][j]
$$

Skip the current piece length.

2. Take

$$
price[i-1]+dp[i][j-i]
$$

Take the current piece and stay at the same row because we can use it again.

Therefore:

$$
dp[i][j]=\max(dp[i-1][j],price[i-1]+dp[i][j-i])
$$

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int cutRod(vector<int>& price, int N) {

    // dp[i][j] represents maximum profit
    // using first i piece lengths for rod length j.
    vector<vector<int>> dp(
        N + 1, vector<int>(N + 1, 0)
    );

    // i represents available piece lengths
    for (int i = 1; i <= N; i++) {

        // j represents current rod length
        for (int j = 0; j <= N; j++) {

            // Option 1: Do not take current piece
            int notTake = dp[i - 1][j];

            // Option 2: Take current piece
            int take = INT_MIN;

            // Current piece length is i
            if (i <= j) {

                // Stay in same row because
                // we can take the same piece again.
                take = price[i - 1] + dp[i][j - i];
            }

            // Store maximum profit
            dp[i][j] = max(take, notTake);
        }
    }

    // Maximum profit for complete rod length N
    return dp[N][N];
}

int main() {

    vector<int> price = {
        1, 5, 8, 9, 10, 17, 17, 20
    };

    int N = 8;

    cout << cutRod(price, N);

    return 0;
}
```

Output:

text

```text
22
```

### Dry Run

Consider:

text

```text
N = 4

price[] = {2, 5, 7, 8}
```

The DP table will be:

| Piece length / Rod length | 0 | 1 | 2 | 3 | 4 |
| --- | --- | --- | --- | --- | --- |
| 0 pieces | 0 | 0 | 0 | 0 | 0 |
| 1 | 0 | 2 | 4 | 6 | 8 |
| 2 | 0 | 2 | 5 | 7 | 10 |
| 3 | 0 | 2 | 5 | 7 | 10 |
| 4 | 0 | 2 | 5 | 7 | 10 |

Therefore:

$$
dp[4][4]=10
$$

One optimal solution is:

text

```text
Length 2 + Length 2

Price = 5 + 5 = 10
```

### Complexity analysis

- Time Complexity: $O(N^2)$
- Space Complexity: $O(N^2)$

## 5. Space Optimization (1D DP)

Very Important for Interviews### Problem statement

Solve the Rod Cutting Problem using only a one-dimensional DP array instead of a 2D DP table.

### Intuition

In the previous approach, we used:

cpp

```cpp
dp[i][j]
```

But each row only depends on:

- The previous row.
- The current row at a smaller capacity.

Therefore, we can reduce the 2D DP into a 1D array.

We define:

cpp

```cpp
dp[j]
```

Meaning:

Maximum profit obtainable for rod length `j`.

### Recurrence

$$
dp[j]=\max(dp[j],price[i-1]+dp[j-i])
$$

### Important concept

We iterate `j` from left to right:

cpp

```cpp
for (int j = i; j <= N; j++)
```

Why?

Because we want to reuse the same piece length multiple times.

This is the same concept as Unbounded Knapsack.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int cutRod(vector<int>& price, int N) {

    // dp[j] stores maximum profit for rod length j
    vector<int> dp(N + 1, 0);

    // Try every available piece length
    for (int i = 1; i <= N; i++) {

        // Iterate forward to allow unlimited reuse
        for (int j = i; j <= N; j++) {

            // Take current piece length i
            int take = price[i - 1] + dp[j - i];

            // Either take or skip the current piece
            dp[j] = max(dp[j], take);
        }
    }

    return dp[N];
}

int main() {

    vector<int> price = {
        1, 5, 8, 9, 10, 17, 17, 20
    };

    int N = 8;

    cout << cutRod(price, N);

    return 0;
}
```

Output:

text

```text
22
```

### Complexity analysis

| Complexity | Value |
| --- | --- |
| Time | $O(N^2)$ |
| Space | $O(N)$ |

Recommended for interviewsIf the interviewer asks you to optimize the space complexity, this is the approach to present.

## 6. Print the Actual Rod Cutting Combination

Important Interview Variation### Problem statement

You are given the rod length and the prices of different rod lengths.

Find:

1. The maximum obtainable profit.
2. The actual combination of rod lengths that produces that profit.

### Example

text

```text
Input:

N = 8

price[] = {1, 5, 8, 9, 10, 17, 17, 20}

Output:

Maximum Profit = 22

Cuts = 2 6
```

### Intuition

We use the 1D DP approach, but maintain another array:

cpp

```cpp
parent[j]
```

It stores the length of the last piece selected to achieve the maximum profit for rod length `j`.

After calculating DP, we reconstruct the answer by repeatedly subtracting the selected piece length.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

void cutRod(vector<int>& price, int N) {

    // dp[i] = maximum profit for rod length i
    vector<int> dp(N + 1, 0);

    // Stores the selected piece length
    vector<int> parent(N + 1, 0);

    // Try every possible piece length
    for (int len = 1; len <= N; len++) {

        // Try all possible rod lengths
        for (int j = len; j <= N; j++) {

            // Profit obtained by taking current piece
            int take = price[len - 1] + dp[j - len];

            if (take > dp[j]) {

                // Update maximum profit
                dp[j] = take;

                // Remember which piece was selected
                parent[j] = len;
            }
        }
    }

    cout << "Maximum Profit: " << dp[N] << endl;

    cout << "Selected Pieces: ";

    // Reconstruct the selected rod pieces
    int remaining = N;

    while (remaining > 0) {

        int selectedLength = parent[remaining];

        // Safety check
        if (selectedLength == 0) {
            break;
        }

        cout << selectedLength << " ";

        // Remove selected piece from remaining rod
        remaining -= selectedLength;
    }

    cout << endl;
}

int main() {

    vector<int> price = {
        1, 5, 8, 9, 10, 17, 17, 20
    };

    int N = 8;

    cutRod(price, N);

    return 0;
}
```

Output:

text

```text
Maximum Profit: 22
Selected Pieces: 2 6
```

Note: There can be multiple optimal combinations. The printed combination depends on the order in which equal-profit choices are processed.

Complexity:

- Time: $O(N^2)$
- Space: $O(N)$

## 7. Rod Cutting Using a Different Recursion Form (Pick / Not Pick)

This is another way interviewers may expect you to write the recursive solution.

### Problem statement

Find the maximum obtainable profit by either selecting the current rod length or skipping it.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int solve(int ind, int length,
          vector<int>& price) {

    // If only the first piece length is available
    if (ind == 0) {

        // Fill the entire rod using length 1 pieces
        return length * price[0];
    }

    // Do not select current piece
    int notPick = solve(ind - 1, length, price);

    int pick = INT_MIN;

    // Actual length represented by current index
    int rodLength = ind + 1;

    // Select current piece if it fits
    if (rodLength <= length) {

        // Stay at same index for unlimited selection
        pick = price[ind] +
               solve(ind, length - rodLength, price);
    }

    return max(pick, notPick);
}

int main() {

    vector<int> price = {2, 5, 7, 8};

    int N = 4;

    cout << solve(N - 1, N, price);

    return 0;
}
```

Output:

text

```text
10
```

## 8. Rod Cutting Using GeeksforGeeks Standard Function Signature

This is useful when solving the problem on coding platforms.

### Problem statement

Given an array `price[]` of size `n`, where `price[i]` represents the price of a rod of length `i+1`, find the maximum obtainable value by cutting up a rod of length `n`.

### C++ Code

cpp

```cpp

class Solution {
public:

    int cutRod(vector<int>& price) {

        int n = price.size();

        // dp[i] stores maximum profit for rod length i
        vector<int> dp(n + 1, 0);

        // Try all available piece lengths
        for (int len = 1; len <= n; len++) {

            // Try all possible rod lengths
            for (int j = len; j <= n; j++) {

                // Take current piece and use remaining rod
                int take = price[len - 1] + dp[j - len];

                // Maximize profit
                dp[j] = max(dp[j], take);
            }
        }

        return dp[n];
    }
};
```

Complexity:

- Time: $O(N^2)$
- Space: $O(N)$

## 9. Important Variations of Rod Cutting

These are additional questions that interviewers can ask by modifying the original problem.

### Question 1: Rod Cutting with Minimum Number of Cuts

MediumProblem statement:

You are given a rod of length `N` and an array of prices. Find the maximum profit, but among all solutions with maximum profit, choose the one requiring the minimum number of pieces.

For example:

text

```text
N = 4
price = {2, 5, 7, 8}
```

Possible optimal solutions:

- `2 + 2` → Profit 10, two pieces.
- `1 + 1 + 2` → Profit 9, three pieces.

Answer: Profit 10, with 2 pieces.

C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

pair<int, int> rodCutting(vector<int>& price, int N) {

    const int INF = 1e9;

    // dp[i] = maximum profit for length i
    vector<int> dp(N + 1, 0);

    // pieces[i] = minimum pieces among optimal solutions
    vector<int> pieces(N + 1, INF);

    pieces[0] = 0;

    for (int len = 1; len <= N; len++) {

        for (int j = len; j <= N; j++) {

            int newProfit = dp[j - len] + price[len - 1];

            int newPieces = pieces[j - len] + 1;

            // Better profit is always preferred
            if (newProfit > dp[j]) {

                dp[j] = newProfit;
                pieces[j] = newPieces;
            }

            // If profit is equal, minimize piece count
            else if (newProfit == dp[j]) {

                pieces[j] = min(
                    pieces[j], newPieces
                );
            }
        }
    }

    return {dp[N], pieces[N]};
}

int main() {

    vector<int> price = {2, 5, 7, 8};

    auto ans = rodCutting(price, 4);

    cout << "Maximum Profit: " << ans.first << endl;
    cout << "Minimum Pieces: " << ans.second << endl;

    return 0;
}
```

Output:

text

```text
Maximum Profit: 10
Minimum Pieces: 2
```

Complexity: $O(N^2)$ time and $O(N)$ space.

### Question 2: Rod Cutting with a Cutting Cost

Medium–HardProblem statement:

You are given a rod of length `N`, prices for every possible piece length, and a fixed cost `C` for every cut.

Every time you divide a rod into two pieces, you pay the cutting cost.

Find the maximum profit after subtracting all cutting costs.

Example:

text

```text
N = 4

price = {2, 5, 7, 8}

Cutting Cost = 1
```

Possible options:

- No cut: Profit = 8.
- Two pieces of length 2: Profit = 5 + 5 - 1 = 9.

Answer = 9.

C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int rodCutting(vector<int>& price, int N, int cutCost) {

    // dp[i] = maximum net profit for rod length i
    vector<int> dp(N + 1, 0);

    for (int len = 1; len <= N; len++) {

        for (int j = len; j <= N; j++) {

            // If j == len, no additional cut is required
            int cost = (j == len) ? 0 : cutCost;

            int take = price[len - 1] + dp[j - len] - cost;

            dp[j] = max(dp[j], take);
        }
    }

    return dp[N];
}

int main() {

    vector<int> price = {2, 5, 7, 8};

    cout << rodCutting(price, 4, 1);

    return 0;
}
```

Output:

text

```text
9
```

Complexity: $O(N^2)$ time and $O(N)$ space.

### Question 3: Rod Cutting with Limited Availability of Each Length

HardProblem statement:

You are given:

- A rod of length `N`.
- A price array.
- A quantity array indicating how many pieces of each length are available.

Find the maximum obtainable profit without exceeding the available quantity of any piece length.

This is a Bounded Knapsack variation rather than Unbounded Knapsack.

C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int rodCutting(
    vector<int>& price,
    vector<int>& quantity,
    int N
) {

    // dp[j] = maximum profit for rod length j
    vector<int> dp(N + 1, 0);

    int n = price.size();

    // Process each available piece length
    for (int i = 0; i < n; i++) {

        // Process quantity of current piece
        for (int q = 0; q < quantity[i]; q++) {

            // Reverse iteration ensures each copy
            // is used at most once.
            for (int j = N; j >= i + 1; j--) {

                dp[j] = max(
                    dp[j],
                    price[i] + dp[j - (i + 1)]
                );
            }
        }
    }

    return dp[N];
}

int main() {

    vector<int> price = {2, 5, 7};

    vector<int> quantity = {2, 1, 1};

    int N = 4;

    cout << rodCutting(price, quantity, N);

    return 0;
}
```

Output:

text

```text
9
```

Here, the available pieces are two length-1 pieces, one length-2 piece, and one length-3 piece.

The best combination is length 1 + length 3, with profit 2 + 7 = 9.

Complexity:

- Time: $O(N \times \sum quantity[i])$
- Space: $O(N)$

### Question 4: Find the Minimum Number of Pieces to Make Rod Length N

Easy–MediumProblem statement:

You are given a rod length `N` and a list of allowed piece lengths.

Find the minimum number of pieces required to obtain exactly length `N`.

If it is impossible, return `-1`.

Example:

text

```text
N = 7

Allowed lengths = {1, 3, 4}

Output = 2
```

Explanation:

text

```text
3 + 4 = 7
```

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int minPieces(vector<int>& lengths, int N) {

    const int INF = 1e9;

    // dp[i] = minimum pieces required for length i
    vector<int> dp(N + 1, INF);

    // Zero pieces required for length zero
    dp[0] = 0;

    // Try every target length
    for (int i = 1; i <= N; i++) {

        // Try every available piece length
        for (int len : lengths) {

            if (len <= i && dp[i - len] != INF) {

                dp[i] = min(
                    dp[i],
                    1 + dp[i - len]
                );
            }
        }
    }

    return dp[N] == INF ? -1 : dp[N];
}

int main() {

    vector<int> lengths = {1, 3, 4};

    cout << minPieces(lengths, 7);

    return 0;
}
```

Output:

text

```text
2
```

Complexity:

- Time: $O(N \times K)$, where K is the number of allowed lengths.
- Space: $O(N)$.

## 10. Important Related Unbounded Knapsack Questions

Rod Cutting belongs to the Unbounded Knapsack family. Once you understand it, practice these problems too.

| No. | Question | Difficulty | Pattern |
| --- | --- | --- | --- |
| 1 | Unbounded Knapsack | Medium | Unbounded DP |
| 2 | Coin Change – Minimum Coins | Medium | Unbounded DP |
| 3 | Coin Change – Number of Ways | Medium | Unbounded DP |
| 4 | Maximum Ribbon Cut | Medium | Unbounded DP |
| 5 | Perfect Squares | Medium | Unbounded DP |
| 6 | Integer Break | Medium | DP |
| 7 | Minimum Cost to Fill a Bag | Medium | Unbounded DP |
| 8 | Combination Sum IV | Medium | Counting DP |
| 9 | Minimum Number of Squares | Medium | Unbounded DP |
| 10 | Maximum Product Cutting | Medium | Partition DP |

## 11. Difference Between 0/1 Knapsack and Unbounded Knapsack

This is one of the most frequently asked interview concepts.

| Feature | 0/1 Knapsack | Unbounded Knapsack |
| --- | --- | --- |
| Reuse an item? | No | Yes |
| DP transition | Previous row | Current row |
| 1D loop direction | Reverse | Forward |
| Rod Cutting | No | Yes |
| Coin Change | Depends on variant | Usually yes |

Remember this important difference:

For 0/1 Knapsack:

cpp

```cpp
for (int j = W; j >= weight[i]; j--) {
    dp[j] = max(dp[j], value[i] + dp[j-weight[i]]);
}
```

For Unbounded Knapsack:

cpp

```cpp
for (int j = weight[i]; j <= W; j++) {
    dp[j] = max(dp[j], value[i] + dp[j-weight[i]]);
}
```

The direction of the loop determines whether the same item can be reused.

## 12. Important Interview Questions and Answers

Q1. Which DP pattern is used in Rod Cutting?

Unbounded Knapsack.

Q2. Why do we stay at the same index after selecting a piece?

Because the same piece length can be selected unlimited times.

Q3. What is the base case in recursive Rod Cutting?

When only length-1 pieces are available:

$$
answer=N\times price[0]
$$

Q4. What is the time complexity of optimized Rod Cutting?

$$
O(N^2)
$$

Q5. What is the space complexity of optimized Rod Cutting?

$$
O(N)
$$

Q6. Why do we iterate forward in the 1D DP approach?

To allow unlimited reuse of the current piece length.

Q7. What is the difference between Rod Cutting and 0/1 Knapsack?

In Rod Cutting, the same piece length can be selected multiple times, whereas in 0/1 Knapsack each item can be selected at most once.

## 13. Rod Cutting – Preparation Checklist

Your learning progress

## 0%

0 of 12 completed

[ ]Understand the Rod Cutting problem

[ ]Implement recursion

[ ]Implement memoization

[ ]Implement 2D tabulation

[ ]Implement 1D space optimization

[ ]Print actual rod pieces

[ ]Understand 0/1 vs Unbounded Knapsack

[ ]Solve Unbounded Knapsack

[ ]Solve Coin Change – Minimum Coins

[ ]Solve Coin Change – Number of Ways

[ ]Solve Maximum Ribbon Cut

[ ]Solve Minimum Cost to Fill a Bag

## 14. Final Revision – What You Must Remember

| Approach | Time | Space |
| --- | --- | --- |
| Recursion | Exponential | $O(N)$ |
| Memoization | $O(N^2)$ | $O(N^2)$ + stack |
| Tabulation | $O(N^2)$ | $O(N^2)$ |
| Space Optimized | $O(N^2)$ | $O(N)$ |
| Print Rod Pieces | $O(N^2)$ | $O(N)$ |

The most important formula

$$
dp[j]=\max(dp[j],price[i-1]+dp[j-i])
$$

The most important concept: Forward iteration in 1D DP allows unlimited reuse of the current piece length.

My recommendation: Master Rod Cutting in all four approaches (recursion, memoization, tabulation, and space optimization). Then solve Unbounded Knapsack and Coin Change. These three problems will give you a strong foundation for the entire Unbounded Knapsack DP pattern.
