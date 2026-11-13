# 0/1 Knapsack Problem – Complete DSA Interview Preparation in C++

Very Important DP Topic Easy to Hard

The 0/1 Knapsack Problem is one of the most important Dynamic Programming problems. It is the foundation of many other DP problems, including:

- Subset Sum
- Equal Sum Partition
- Count Subsets with Given Sum
- Minimum Subset Sum Difference
- Target Sum
- Partition Equal Subset Sum
- Count Partitions with Given Difference

It is frequently asked in coding interviews, placement examinations, and technical rounds.

I'll cover the recursive approach, memoization, tabulation, space optimization, and important variations with complete C++ code and explanations.

## 1. Understanding the 0/1 Knapsack Problem

### Problem statement

You are given:

- An array `weight[]` containing the weights of `N` items.
- An array `value[]` containing the values of `N` items.
- An integer `W` representing the maximum capacity of a knapsack.

Your task is to select items such that:

1. The total weight does not exceed `W`.
2. The total value is maximized.
3. Each item can either be selected once or not selected at all.

Important: You cannot select the same item more than once.

### Example 1

text

```text
Input:

N = 3
W = 4

weight[] = {4, 5, 1}
value[]  = {1, 2, 3}

Output:
4
```

Explanation:

We have three items:

| Item | Weight | Value |
| --- | --- | --- |
| 1 | 4 | 1 |
| 2 | 5 | 2 |
| 3 | 1 | 3 |

Our knapsack capacity is 4.

Possible selections:

- Item 1: Weight = 4, Value = 1.
- Item 2: Weight = 5, Invalid.
- Item 3: Weight = 1, Value = 3.
- Item 1 + Item 3: Weight = 5, Invalid.

The maximum obtainable value is 3, not 4.

Correct Answer: 3### Example 2

text

```text
Input:

N = 4
W = 7

weight[] = {1, 3, 4, 5}
value[]  = {1, 4, 5, 7}

Output:
9
```

Explanation:

Select:

- Item 2: Weight = 3, Value = 4.
- Item 3: Weight = 4, Value = 5.

Total weight:

$$
3+4=7
$$

Total value:

$$
4+5=9
$$

Therefore, the maximum value is 9.

What Is Knapsack Dynamic at Stephen Padilla blog

[storage.googleapis.com](<https://storage.googleapis.com/dkttoohzwbtgve/what-is-knapsack-dynamic.html?utm_source=chatgpt.com>)

## 2. Understanding the Pick and Not Pick Concept

The most important concept in 0/1 Knapsack is that every item has exactly two choices.

Choice 1: Pick the item

If the item's weight is less than or equal to the remaining capacity:

$$
value[index]+solve(index-1,W-weight[index])
$$

We move to the previous index because an item cannot be selected again.

Choice 2: Do Not Pick the item

$$
solve(index-1,W)
$$

We skip the item and move to the previous index.

We take the maximum of these two choices.

### Recurrence Relation

$$
dp[i][W]=\max(Take,NotTake)
$$

Where:

$$
Take=value[i]+dp[i-1][W-weight[i]]
$$

$$
NotTake=dp[i-1][W]
$$

The take option is valid only when:

$$
weight[i]\leq W
$$

### Base Cases

If no items are available:

$$
dp[-1][W]=0
$$

If the capacity is zero:

$$
dp[i][0]=0
$$

## 3. Recursive Approach (Brute Force)

### Problem statement

Find the maximum value that can be obtained by selecting or rejecting each item recursively.

### Intuition

We define:

cpp

```cpp
solve(index, W)
```

Where:

- `index` represents the current item.
- `W` represents the remaining knapsack capacity.

For every item, we explore two possibilities:

1. Pick the item.
2. Do not pick the item.

Finally, return the maximum value.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

// Recursive function to calculate maximum profit
int solve(int index, int W,
          vector<int>& weight,
          vector<int>& value) {

    // Base case:
    // Only the first item is available
    if (index == 0) {

        // Check whether first item fits
        if (weight[0] <= W) {
            return value[0];
        }

        // Cannot select the first item
        return 0;
    }

    // Option 1: Do not select current item
    int notTake = solve(
        index - 1, W, weight, value
    );

    // Option 2: Select current item
    int take = INT_MIN;

    // Check whether current item fits
    if (weight[index] <= W) {

        take = value[index] +
               solve(
                   index - 1,
                   W - weight[index],
                   weight,
                   value
               );
    }

    // Return maximum of both choices
    return max(take, notTake);
}

int knapsack(vector<int>& weight,
             vector<int>& value,
             int N,
             int W) {

    return solve(N - 1, W, weight, value);
}

int main() {

    vector<int> weight = {1, 3, 4, 5};

    vector<int> value = {1, 4, 5, 7};

    int N = 4;
    int W = 7;

    cout << knapsack(weight, value, N, W);

    return 0;
}
```

Output:

text

```text
9
```

### Complexity analysis

- Time Complexity: $O(2^N)$
- Auxiliary Space: $O(N)$ recursion stack.

Limitation: The same subproblems are calculated repeatedly. We can optimize this using memoization.

## 4. Memoization (Top-Down DP)

Very Important Interview Approach### Problem statement

Solve the 0/1 Knapsack problem using recursion and memoization to avoid recalculating the same subproblems.

### Intuition

We create a 2D DP array:

cpp

```cpp
dp[index][W]
```

Meaning:

`dp[index][W]` stores the maximum value obtainable using items from index `0` to `index` with knapsack capacity `W`.

Before calculating the answer, we check whether the result is already available.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int solve(int index, int W,
          vector<int>& weight,
          vector<int>& value,
          vector<vector<int>>& dp) {

    // Base case: Only first item is available
    if (index == 0) {

        if (weight[0] <= W) {
            return value[0];
        }

        return 0;
    }

    // Return previously calculated answer
    if (dp[index][W] != -1) {
        return dp[index][W];
    }

    // Option 1: Do not take current item
    int notTake = solve(
        index - 1, W, weight, value, dp
    );

    // Option 2: Take current item
    int take = INT_MIN;

    if (weight[index] <= W) {

        take = value[index] +
               solve(
                   index - 1,
                   W - weight[index],
                   weight,
                   value,
                   dp
               );
    }

    // Store and return maximum profit
    return dp[index][W] = max(take, notTake);
}

int knapsack(vector<int>& weight,
             vector<int>& value,
             int N,
             int W) {

    vector<vector<int>> dp(
        N, vector<int>(W + 1, -1)
    );

    return solve(N - 1, W, weight, value, dp);
}

int main() {

    vector<int> weight = {1, 3, 4, 5};

    vector<int> value = {1, 4, 5, 7};

    int N = 4;
    int W = 7;

    cout << knapsack(weight, value, N, W);

    return 0;
}
```

Output:

text

```text
9
```

### Complexity analysis

- Time Complexity: $O(N \times W)$
- Space Complexity: $O(N \times W)$ for DP + $O(N)$ recursion stack.

## 5. Tabulation (Bottom-Up Dynamic Programming)

Most Important Approach### Problem statement

Solve the 0/1 Knapsack problem using an iterative DP approach without recursion.

### Intuition

We create a 2D DP array:

$$
dp[i][j]
$$

Meaning:

`dp[i][j]` = Maximum value obtainable using the first `i` items with knapsack capacity `j`.

We have two choices.

1. Not Take

$$
dp[i-1][j]
$$

We skip the current item.

2. Take

$$
value[i-1]+dp[i-1][j-weight[i-1]]
$$

We select the current item and reduce the remaining capacity.

Notice that we move to the previous row even after taking an item. This ensures that an item cannot be selected again.

### Recurrence relation

$$
dp[i][j]=
\begin{cases}
dp[i-1][j], & weight[i-1]>j\\
\max(dp[i-1][j],value[i-1]+dp[i-1][j-weight[i-1]]), & otherwise
\end{cases}
$$

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int knapsack(vector<int>& weight,
             vector<int>& value,
             int N,
             int W) {

    // dp[i][j] represents maximum value using
    // first i items with capacity j.
    vector<vector<int>> dp(
        N + 1, vector<int>(W + 1, 0)
    );

    // Process items one by one
    for (int i = 1; i <= N; i++) {

        // Try every possible capacity
        for (int j = 0; j <= W; j++) {

            // Option 1: Do not take current item
            int notTake = dp[i - 1][j];

            // Option 2: Take current item
            int take = INT_MIN;

            // Check whether item fits
            if (weight[i - 1] <= j) {

                take = value[i - 1] +
                       dp[i - 1][j - weight[i - 1]];
            }

            // Store maximum value
            dp[i][j] = max(take, notTake);
        }
    }

    // Maximum value using all items
    // and complete knapsack capacity
    return dp[N][W];
}

int main() {

    vector<int> weight = {1, 3, 4, 5};

    vector<int> value = {1, 4, 5, 7};

    int N = 4;
    int W = 7;

    cout << knapsack(weight, value, N, W);

    return 0;
}
```

Output:

text

```text
9
```

### Dry Run

Consider:

text

```text
N = 3
W = 4

weight[] = {1, 3, 4}
value[]  = {15, 20, 30}
```

The DP table will be:

| Items / Capacity | 0 | 1 | 2 | 3 | 4 |
| --- | --- | --- | --- | --- | --- |
| 0 items | 0 | 0 | 0 | 0 | 0 |
| Item 1 | 0 | 15 | 15 | 15 | 15 |
| Item 2 | 0 | 15 | 15 | 20 | 35 |
| Item 3 | 0 | 15 | 15 | 20 | 35 |

Final answer:

$$
dp[3][4]=35
$$

Explanation:

Select:

- Item 1: Weight 1, Value 15.
- Item 2: Weight 3, Value 20.

Total weight = 4.

Total value = 35.

### Complexity analysis

- Time Complexity: $O(N \times W)$
- Space Complexity: $O(N \times W)$

## 6. Space Optimization (Two 1D Arrays)

Important Interview Approach### Problem statement

Optimize the 2D DP solution by using only two 1D arrays.

### Intuition

In the tabulation approach, the current row depends only on the previous row.

Therefore, we can use:

cpp

```cpp
prev[j]
curr[j]
```

Where:

- `prev[j]` stores the answer for the previous item.
- `curr[j]` stores the answer for the current item.

After processing each item, we update the previous array.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int knapsack(vector<int>& weight,
             vector<int>& value,
             int N,
             int W) {

    // Previous row and current row
    vector<int> prev(W + 1, 0);

    vector<int> curr(W + 1, 0);

    // Process each item
    for (int i = 0; i < N; i++) {

        // Try every possible capacity
        for (int j = 0; j <= W; j++) {

            // Option 1: Skip current item
            int notTake = prev[j];

            // Option 2: Take current item
            int take = INT_MIN;

            if (weight[i] <= j) {

                take = value[i] +
                       prev[j - weight[i]];
            }

            curr[j] = max(take, notTake);
        }

        // Current row becomes previous row
        prev = curr;
    }

    return prev[W];
}

int main() {

    vector<int> weight = {1, 3, 4, 5};

    vector<int> value = {1, 4, 5, 7};

    int N = 4;
    int W = 7;

    cout << knapsack(weight, value, N, W);

    return 0;
}
```

Output:

text

```text
9
```

Complexity:

- Time: $O(N \times W)$
- Space: $O(W)$

## 7. Space Optimization (Single 1D Array)

Best Approach for Interviews### Problem statement

Solve the 0/1 Knapsack problem using only one 1D DP array.

### Intuition

We can eliminate the need for two arrays by updating the DP array in reverse order.

Define:

cpp

```cpp
dp[j]
```

Meaning:

Maximum value obtainable with capacity `j` using the items processed so far.

For every item, we update:

$$
dp[j]=\max(dp[j],value[i]+dp[j-weight[i]])
$$

### Most important concept: Reverse iteration

We iterate from:

cpp

```cpp
for (int j = W; j >= weight[i]; j--)
```

Why?

Because we want to ensure that the current item is not selected more than once.

By iterating backwards, `dp[j-weight[i]]` still contains the result from before processing the current item.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int knapsack(vector<int>& weight,
             vector<int>& value,
             int N,
             int W) {

    // dp[j] = maximum value for capacity j
    vector<int> dp(W + 1, 0);

    // Process every item
    for (int i = 0; i < N; i++) {

        // Traverse capacity in reverse order
        for (int j = W; j >= weight[i]; j--) {

            // Option 1: Do not take current item
            // dp[j] remains unchanged.

            // Option 2: Take current item
            int take = value[i] + dp[j - weight[i]];

            // Store maximum value
            dp[j] = max(dp[j], take);
        }
    }

    return dp[W];
}

int main() {

    vector<int> weight = {1, 3, 4, 5};

    vector<int> value = {1, 4, 5, 7};

    int N = 4;
    int W = 7;

    cout << knapsack(weight, value, N, W);

    return 0;
}
```

Output:

text

```text
9
```

### Complexity analysis

| Complexity | Value |
| --- | --- |
| Time | $O(N \times W)$ |
| Space | $O(W)$ |

Recommended solutionThis is the most space-efficient standard DP solution for 0/1 Knapsack.

## 8. Print the Selected Items

Important Interview Variation### Problem statement

You are given weights, values, and knapsack capacity.

Find:

1. Maximum obtainable value.
2. The actual items selected to achieve that value.

### Example

text

```text
Input:

N = 4
W = 7

weight[] = {1, 3, 4, 5}
value[]  = {1, 4, 5, 7}

Output:

Maximum Value = 9
Selected Items = 2 3
```

### Intuition

We use the 2D DP table and backtrack from:

cpp

```cpp
dp[N][W]
```

If:

cpp

```cpp
dp[i][W] != dp[i-1][W]
```

Then the current item was selected.

We subtract its weight from the remaining capacity and continue.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

void knapsack(vector<int>& weight,
              vector<int>& value,
              int N,
              int W) {

    vector<vector<int>> dp(
        N + 1, vector<int>(W + 1, 0)
    );

    // Build the DP table
    for (int i = 1; i <= N; i++) {

        for (int j = 0; j <= W; j++) {

            // Do not take current item
            int notTake = dp[i - 1][j];

            int take = INT_MIN;

            // Take current item if it fits
            if (weight[i - 1] <= j) {

                take = value[i - 1] +
                       dp[i - 1][j - weight[i - 1]];
            }

            dp[i][j] = max(take, notTake);
        }
    }

    cout << "Maximum Value: " << dp[N][W] << endl;

    cout << "Selected Items: ";

    // Backtrack to find selected items
    int capacity = W;

    for (int i = N; i >= 1; i--) {

        // If value differs from previous row,
        // the current item was selected.
        if (dp[i][capacity] != dp[i - 1][capacity]) {

            cout << i << " ";

            // Reduce remaining capacity
            capacity -= weight[i - 1];
        }
    }

    cout << endl;
}

int main() {

    vector<int> weight = {1, 3, 4, 5};

    vector<int> value = {1, 4, 5, 7};

    int N = 4;
    int W = 7;

    knapsack(weight, value, N, W);

    return 0;
}
```

Output:

text

```text
Maximum Value: 9
Selected Items: 3 2
```

Note: The selected items are printed in reverse order. Multiple optimal selections may exist.

## 9. 0/1 Knapsack Using GeeksforGeeks Standard Function Signature

This version is useful for coding platforms.

### Problem statement

Given the weights and values of `N` items and a knapsack capacity `W`, return the maximum value that can be obtained without exceeding the capacity.

### C++ Code

cpp

```cpp

class Solution {
public:

    int knapsack(int W, vector<int> &val,
                 vector<int> &wt) {

        int n = val.size();

        // One-dimensional DP array
        vector<int> dp(W + 1, 0);

        // Process each item
        for (int i = 0; i < n; i++) {

            // Reverse traversal prevents reuse
            for (int j = W; j >= wt[i]; j--) {

                dp[j] = max(
                    dp[j],
                    val[i] + dp[j - wt[i]]
                );
            }
        }

        return dp[W];
    }
};
```

Complexity:

- Time: $O(N \times W)$
- Space: $O(W)$

# 10. Important 0/1 Knapsack Variations (Most Asked Interview Questions)

This is the most important section after understanding the basic Knapsack problem.

Many interviewers don't directly ask 0/1 Knapsack. Instead, they modify the question and test whether you can identify the underlying DP pattern.

Let's cover the major variations.

## Question 1: Subset Sum Problem

Very Important Medium

### Problem statement

You are given an array of positive integers `arr[]` and an integer `target`.

Determine whether there exists a subset of the array whose sum is exactly equal to the target.

Each element can be selected at most once.

### Example

text

```text
Input:

arr[] = {2, 3, 7, 8, 10}
target = 11

Output:
true
```

Explanation:

We can select:

text

```text
3 + 8 = 11
```

Therefore, a subset with the required sum exists.

### Intuition

This is similar to 0/1 Knapsack.

For every element, we have two choices:

- Take the element.
- Do not take the element.

Our state is:

cpp

```cpp
dp[index][target]
```

It tells us whether we can make the required sum using the available elements.

### C++ Code – Recursion + Memoization

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

bool solve(int index, int target,
           vector<int>& arr,
           vector<vector<int>>& dp) {

    // Target zero can always be achieved
    // by selecting an empty subset.
    if (target == 0) {
        return true;
    }

    // No elements are left
    if (index == 0) {
        return arr[0] == target;
    }

    // Return already calculated result
    if (dp[index][target] != -1) {
        return dp[index][target];
    }

    // Option 1: Do not take current element
    bool notTake = solve(
        index - 1, target, arr, dp
    );

    // Option 2: Take current element
    bool take = false;

    if (arr[index] <= target) {

        take = solve(
            index - 1,
            target - arr[index],
            arr,
            dp
        );
    }

    // Store whether any valid subset exists
    return dp[index][target] = (take || notTake);
}

bool isSubsetSum(vector<int>& arr, int target) {

    int n = arr.size();

    vector<vector<int>> dp(
        n, vector<int>(target + 1, -1)
    );

    return solve(n - 1, target, arr, dp);
}

int main() {

    vector<int> arr = {2, 3, 7, 8, 10};

    int target = 11;

    cout << boolalpha << isSubsetSum(arr, target);

    return 0;
}
```

Output:

text

```text
true
```

### Complexity

- Time: $O(N \times Target)$
- Space: $O(N \times Target)$ + recursion stack.

### Space-Optimized C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

bool isSubsetSum(vector<int>& arr, int target) {

    int n = arr.size();

    // dp[s] tells whether sum s is possible
    vector<bool> dp(target + 1, false);

    // Sum zero is always possible
    dp[0] = true;

    // Process each array element
    for (int i = 0; i < n; i++) {

        // Reverse traversal ensures each element
        // is selected at most once.
        for (int j = target; j >= arr[i]; j--) {

            dp[j] = dp[j] || dp[j - arr[i]];
        }
    }

    return dp[target];
}

int main() {

    vector<int> arr = {2, 3, 7, 8, 10};

    cout << boolalpha << isSubsetSum(arr, 11);

    return 0;
}
```

Complexity:

- Time: $O(N \times Target)$
- Space: $O(Target)$

## Question 2: Equal Sum Partition

Very Important Medium

### Problem statement

You are given an array of positive integers.

Determine whether the array can be divided into two subsets such that the sum of both subsets is equal.

### Example

text

```text
Input:

arr[] = {1, 5, 11, 5}

Output:
true
```

Explanation:

We can divide the array into:

text

```text
Subset 1 = {1, 5, 5}

Subset 2 = {11}
```

Both subset sums are 11.

### Intuition

First calculate the total sum.

If the total sum is odd, equal partition is impossible.

Otherwise, we need to find whether a subset with sum:

$$
target=\frac{totalSum}{2}
$$

exists.

This becomes the Subset Sum problem.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

bool canPartition(vector<int>& arr) {

    int totalSum = 0;

    // Calculate total array sum
    for (int x : arr) {
        totalSum += x;
    }

    // Odd sum cannot be divided equally
    if (totalSum % 2 != 0) {
        return false;
    }

    int target = totalSum / 2;

    // Subset Sum DP
    vector<bool> dp(target + 1, false);

    dp[0] = true;

    for (int x : arr) {

        // Reverse iteration for 0/1 selection
        for (int j = target; j >= x; j--) {

            dp[j] = dp[j] || dp[j - x];
        }
    }

    return dp[target];
}

int main() {

    vector<int> arr = {1, 5, 11, 5};

    cout << boolalpha << canPartition(arr);

    return 0;
}
```

Output:

text

```text
true
```

Complexity:

- Time: $O(N \times Sum)$
- Space: $O(Sum)$

## Question 3: Count Subsets with Given Sum

Very Important Medium

### Problem statement

You are given an array of integers and a target sum.

Find the total number of subsets whose elements add up exactly to the target.

Unlike Subset Sum, here we need to count all possible subsets rather than just return true or false.

### Example

text

```text
Input:

arr[] = {1, 2, 3, 3}
target = 6

Output:
3
```

Explanation:

The possible subsets are:

text

```text
{1, 2, 3}
{1, 2, 3}  // Using the other 3
{3, 3}
```

There are 3 valid subsets, considering equal-valued elements at different indices as different elements.

### Intuition

Instead of storing a boolean value, store the number of ways.

Recurrence:

$$
dp[i][j]=dp[i-1][j]+dp[i-1][j-arr[i-1]]
$$

The second term is included only when the current element fits.

### C++ Code – 2D DP

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

long long countSubsets(vector<int>& arr, int target) {

    int n = arr.size();

    // dp[i][j] = number of subsets using first i
    // elements whose sum is exactly j.
    vector<vector<long long>> dp(
        n + 1, vector<long long>(target + 1, 0)
    );

    // There is exactly one way to make sum 0:
    // select the empty subset.
    dp[0][0] = 1;

    // Process elements
    for (int i = 1; i <= n; i++) {

        for (int j = 0; j <= target; j++) {

            // Do not select current element
            dp[i][j] = dp[i - 1][j];

            // Select current element if possible
            if (arr[i - 1] <= j) {

                dp[i][j] +=
                    dp[i - 1][j - arr[i - 1]];
            }
        }
    }

    return dp[n][target];
}

int main() {

    vector<int> arr = {1, 2, 3, 3};

    cout << countSubsets(arr, 6);

    return 0;
}
```

Output:

text

```text
3
```

### Important edge case: Zero values

If the array contains zeros, the number of subsets can increase because each zero can either be selected or not selected.

For example:

text

```text
arr = {0, 0, 1}
target = 1
```

Answer = 4.

The 2D DP implementation above handles zeros correctly.

### Complexity

- Time: $O(N \times Target)$
- Space: $O(N \times Target)$

## Question 4: Minimum Subset Sum Difference

Very Important Medium–Hard

### Problem statement

You are given an array of positive integers.

Divide it into two subsets such that the absolute difference between their sums is minimized.

Return the minimum possible difference.

### Example

text

```text
Input:

arr[] = {1, 6, 11, 5}

Output:
1
```

Explanation:

One possible partition is:

text

```text
Subset 1 = {1, 5, 6}
Sum = 12

Subset 2 = {11}
Sum = 11
```

Difference:

$$
|12-11|=1
$$

### Intuition

Let:

- `S` = total sum.
- `s1` = sum of the first subset.
- `s2` = sum of the second subset.

We know:

$$
s1+s2=S
$$

Therefore:

$$
s2=S-s1
$$

Difference:

$$
|s1-s2|=|S-2s1|
$$

We only need to check subset sums from `0` to `S/2`.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int minSubsetSumDifference(vector<int>& arr) {

    int n = arr.size();

    int totalSum = 0;

    for (int x : arr) {
        totalSum += x;
    }

    // Find all possible subset sums up to totalSum
    vector<bool> dp(totalSum + 1, false);

    dp[0] = true;

    for (int x : arr) {

        // Reverse iteration for 0/1 selection
        for (int j = totalSum; j >= x; j--) {

            dp[j] = dp[j] || dp[j - x];
        }
    }

    int mini = INT_MAX;

    // Only check sums up to half of total sum
    for (int s1 = 0; s1 <= totalSum / 2; s1++) {

        if (dp[s1]) {

            int s2 = totalSum - s1;

            mini = min(mini, abs(s1 - s2));
        }
    }

    return mini;
}

int main() {

    vector<int> arr = {1, 6, 11, 5};

    cout << minSubsetSumDifference(arr);

    return 0;
}
```

Output:

text

```text
1
```

Complexity:

- Time: $O(N \times Sum)$
- Space: $O(Sum)$

## Question 5: Count Partitions with Given Difference

Medium–Hard### Problem statement

You are given an array of positive integers and an integer `D`.

Divide the array into two subsets `S1` and `S2` such that:

$$
S1-S2=D
$$

Find the number of ways to make such a partition.

### Example

text

```text
Input:

arr[] = {5, 2, 6, 4}
D = 3

Output:
1
```

Explanation:

One valid partition is:

text

```text
S1 = {5, 6}
Sum = 11

S2 = {2, 4}
Sum = 6
```

Difference:

$$
11-6=5
$$

This is not 3, so it is not a valid partition. The example above would be incorrect.

A correct example is:

text

```text
arr[] = {1, 1, 2, 3}
D = 1

Output:
3
```

For example, valid partitions include:

text

```text
S1 = {1, 3}, S2 = {1, 2}
S1 = {1, 3}, S2 = {1, 2}  // Different indexed 1
S1 = {1, 1, 2}, S2 = {3}
```

### Intuition

Let:

$$
S1+S2=TotalSum
$$

And:

$$
S1-S2=D
$$

Adding both equations:

$$
2S1=TotalSum+D
$$

Therefore:

$$
S1=\frac{TotalSum+D}{2}
$$

The problem becomes counting subsets whose sum is equal to this target.

If `TotalSum + D` is odd or `D` exceeds the total sum, the answer is zero.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

long long countPartitions(vector<int>& arr, int D) {

    int totalSum = 0;

    for (int x : arr) {
        totalSum += x;
    }

    // Invalid difference
    if (D > totalSum) {
        return 0;
    }

    // Target must be an integer
    if ((totalSum + D) % 2 != 0) {
        return 0;
    }

    int target = (totalSum + D) / 2;

    // dp[s] = number of subsets with sum s
    vector<long long> dp(target + 1, 0);

    // One way to make sum zero: empty subset
    dp[0] = 1;

    for (int x : arr) {

        // Reverse traversal for 0/1 selection
        for (int j = target; j >= x; j--) {

            dp[j] += dp[j - x];
        }
    }

    return dp[target];
}

int main() {

    vector<int> arr = {1, 1, 2, 3};

    int D = 1;

    cout << countPartitions(arr, D);

    return 0;
}
```

Output:

text

```text
3
```

Complexity:

- Time: $O(N \times Target)$
- Space: $O(Target)$

## Question 6: Target Sum

Very Important – LeetCode Medium

### Problem statement

You are given an array of positive integers `nums[]` and a target integer `target`.

You must assign either `+` or `-` signs to every element such that their sum equals the target.

Return the number of different expressions that can be formed.

### Example

text

```text
Input:

nums = {1, 1, 1, 1, 1}
target = 3

Output:
5
```

Explanation:

There are five ways:

text

```text
+1 +1 +1 +1 -1 = 3
+1 +1 +1 -1 +1 = 3
+1 +1 -1 +1 +1 = 3
+1 -1 +1 +1 +1 = 3
-1 +1 +1 +1 +1 = 3
```

### Intuition

Let:

- `S1` = sum of positive elements.
- `S2` = sum of negative elements without their signs.

Then:

$$
S1-S2=Target
$$

And:

$$
S1+S2=TotalSum
$$

Therefore:

$$
S1=\frac{TotalSum+Target}{2}
$$

We convert this into Count Subsets with Given Sum.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int findTargetSumWays(vector<int>& nums, int target) {

    int totalSum = 0;

    for (int x : nums) {
        totalSum += x;
    }

    // Target cannot exceed total sum in absolute value
    if (abs(target) > totalSum) {
        return 0;
    }

    // Check whether a valid integer subset target exists
    if ((totalSum + target) % 2 != 0) {
        return 0;
    }

    int requiredSum = (totalSum + target) / 2;

    // dp[s] = number of ways to form sum s
    vector<long long> dp(requiredSum + 1, 0);

    dp[0] = 1;

    for (int x : nums) {

        // Reverse traversal prevents reuse
        for (int j = requiredSum; j >= x; j--) {

            dp[j] += dp[j - x];
        }
    }

    return (int)dp[requiredSum];
}

int main() {

    vector<int> nums = {1, 1, 1, 1, 1};

    int target = 3;

    cout << findTargetSumWays(nums, target);

    return 0;
}
```

Output:

text

```text
5
```

Complexity:

- Time: $O(N \times TargetSum)$
- Space: $O(TargetSum)$

For very large inputs, use a sufficiently wide integer type and account for the problem's required modulo or overflow constraints.
