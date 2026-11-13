# Longest Common Subsequence (LCS) – Complete DSA Interview Preparation in C++

Very Important DP Topic Easy to Hard

The Longest Common Subsequence (LCS) is one of the most important Dynamic Programming problems. It is frequently asked in coding interviews, placement examinations, and technical rounds.

LCS is the foundation for several other important DP problems, including:

- Longest Common Substring
- Shortest Common Supersequence
- Minimum Insertions and Deletions
- Longest Palindromic Subsequence
- Longest Repeating Subsequence
- Edit Distance
- Print LCS

We'll cover the important approaches, complete C++ implementations, dry runs, problem statements, complexities, and interview variations.

## 1. Understanding Longest Common Subsequence

### Problem statement

You are given two strings `s1` and `s2`.

Find the length of the longest subsequence that is common to both strings.

Important: A subsequence is formed by deleting zero or more characters without changing the relative order of the remaining characters.

The characters do not need to be continuous.

### Example 1

text

```text
Input:
s1 = "abcde"
s2 = "ace"

Output:
3
```

Explanation:

The common subsequence is:

text

```text
a c e
```

Its length is 3.

### Example 2

text

```text
Input:
s1 = "abc"
s2 = "acb"

Output:
2
```

Possible longest common subsequences:

text

```text
ab
```

or

text

```text
ac
```

Both have length 2.

### Subsequence vs Substring

This is a very important interview concept.

Subsequence example

Original string: ABCDE

### A

### B

### C

### D

### E

ACE is a valid subsequence.

Substring example

Original string: ABCDE

### A

### B

### C

### D

### E

BCD is a valid substring.

| Subsequence | Substring |
| --- | --- |
| Characters need not be continuous | Characters must be continuous |
| Relative order must remain same | Relative order must remain same |
| Example: ACE | Example: BCD |

## 2. Recursive Approach (Brute Force)

### Problem statement

Find the length of the Longest Common Subsequence using recursion.

### Intuition

We compare the last characters of both strings.

There are two possibilities:

Case 1: Characters match

If:

cpp

```cpp
s1[i] == s2[j]
```

Then this character belongs to the common subsequence.

We add 1 and move both pointers backward.

$$
1+solve(i-1,j-1)
$$

Case 2: Characters do not match

We have two choices:

- Ignore the current character of the first string.
- Ignore the current character of the second string.

Take the maximum of both possibilities.

$$
\max(solve(i-1,j),solve(i,j-1))
$$

### Recurrence relation

$$
LCS(i,j)=
\begin{cases}
0 & i<0 \text{ or } j<0\\
1+LCS(i-1,j-1) & s1[i]=s2[j]\\
\max(LCS(i-1,j),LCS(i,j-1)) & otherwise
\end{cases}
$$

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

// Recursive function to calculate LCS length
int solve(int i, int j, string& s1, string& s2) {

    // Base case:
    // If either string is completely traversed,
    // no common subsequence is possible.
    if (i < 0 || j < 0) {
        return 0;
    }

    // If current characters match
    if (s1[i] == s2[j]) {

        // Include this character in LCS
        return 1 + solve(i - 1, j - 1, s1, s2);
    }

    // If characters do not match:
    // Option 1: Ignore current character of s1
    int moveS1 = solve(i - 1, j, s1, s2);

    // Option 2: Ignore current character of s2
    int moveS2 = solve(i, j - 1, s1, s2);

    // Return maximum of both possibilities
    return max(moveS1, moveS2);
}

int longestCommonSubsequence(string s1, string s2) {

    int n = s1.size();
    int m = s2.size();

    // Start from the last character of both strings
    return solve(n - 1, m - 1, s1, s2);
}

int main() {

    string s1 = "abcde";
    string s2 = "ace";

    cout << longestCommonSubsequence(s1, s2);

    return 0;
}
```

Output:

text

```text
3
```

### Complexity analysis

- Time Complexity: Exponential, upper bounded by $O(2^{N+M})$.
- Auxiliary Space: $O(N+M)$ recursion stack.

Problem: Many overlapping subproblems are calculated repeatedly. We can optimize this using memoization.

## 3. Memoization (Top-Down DP)

Important Interview Approach### Problem statement

Solve LCS using recursion and memoization so that the same subproblem is not calculated repeatedly.

### Intuition

We create a 2D DP array:

cpp

```cpp
dp[i][j]
```

Meaning:

`dp[i][j]` stores the LCS length between:

- First string from index `0` to `i`.
- Second string from index `0` to `j`.

If the answer is already calculated, return it directly.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int solve(int i, int j,
          string& s1, string& s2,
          vector<vector<int>>& dp) {

    // Base case
    if (i < 0 || j < 0) {
        return 0;
    }

    // Return previously calculated answer
    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    // If characters match
    if (s1[i] == s2[j]) {

        return dp[i][j] =
            1 + solve(i - 1, j - 1, s1, s2, dp);
    }

    // If characters do not match
    int moveS1 = solve(i - 1, j, s1, s2, dp);

    int moveS2 = solve(i, j - 1, s1, s2, dp);

    // Store maximum result
    return dp[i][j] = max(moveS1, moveS2);
}

int longestCommonSubsequence(string s1, string s2) {

    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(
        n, vector<int>(m, -1)
    );

    return solve(n - 1, m - 1, s1, s2, dp);
}

int main() {

    string s1 = "abcde";
    string s2 = "ace";

    cout << longestCommonSubsequence(s1, s2);

    return 0;
}
```

Output:

text

```text
3
```

### Complexity analysis

- Time Complexity: $O(N \times M)$
- Space Complexity: $O(N \times M)$ for DP + $O(N+M)$ recursion stack.

## 4. Tabulation (Bottom-Up DP)

Most Important Approach### Problem statement

Solve the Longest Common Subsequence problem using an iterative Dynamic Programming approach without recursion.

### Intuition

We create a 2D DP array:

$$
dp[i][j]
$$

Meaning:

`dp[i][j]` represents the LCS length between:

- First `i` characters of `s1`.
- First `j` characters of `s2`.

Important difference: In tabulation, we use 1-based DP indexing to avoid negative indices.

### Recurrence relation

If characters match:

$$
dp[i][j]=1+dp[i-1][j-1]
$$

If characters do not match:

$$
dp[i][j]=\max(dp[i-1][j],dp[i][j-1])
$$

Base case:

$$
dp[0][j]=dp[i][0]=0
$$

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int longestCommonSubsequence(string s1, string s2) {

    int n = s1.size();
    int m = s2.size();

    // DP table of size (n+1) x (m+1)
    // Extra row and column handle empty strings.
    vector<vector<int>> dp(
        n + 1, vector<int>(m + 1, 0)
    );

    // Traverse both strings
    for (int i = 1; i <= n; i++) {

        for (int j = 1; j <= m; j++) {

            // If current characters match
            if (s1[i - 1] == s2[j - 1]) {

                // Include matching character
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }

            else {

                // Ignore one character from either string
                dp[i][j] = max(
                    dp[i - 1][j],
                    dp[i][j - 1]
                );
            }
        }
    }

    // LCS length of complete strings
    return dp[n][m];
}

int main() {

    string s1 = "abcde";
    string s2 = "ace";

    cout << longestCommonSubsequence(s1, s2);

    return 0;
}
```

Output:

text

```text
3
```

### Dry Run

Consider:

text

```text
s1 = "abc"
s2 = "ac"
```

The DP table will be:

|  | "" | a | c |
| --- | --- | --- | --- |
| "" | 0 | 0 | 0 |
| a | 0 | 1 | 1 |
| b | 0 | 1 | 1 |
| c | 0 | 1 | 2 |

Therefore:

$$
dp[3][2]=2
$$

The longest common subsequence is `"ac"`.

### Complexity analysis

- Time Complexity: $O(N \times M)$
- Space Complexity: $O(N \times M)$

## 5. Space Optimization (Two 1D Arrays)

Very Important for Interviews### Problem statement

Find the LCS length using less memory than the 2D DP approach.

### Intuition

In tabulation, we use:

cpp

```cpp
dp[i][j]
```

But to calculate the current row, we only need:

- Previous row.
- Current row's previous column.

Therefore, we can use two 1D arrays:

cpp

```cpp
prev[]
curr[]
```

### Recurrence

If characters match:

$$
curr[j]=1+prev[j-1]
$$

Otherwise:

$$
curr[j]=\max(prev[j],curr[j-1])
$$

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int longestCommonSubsequence(string s1, string s2) {

    int n = s1.size();
    int m = s2.size();

    // Previous and current DP rows
    vector<int> prev(m + 1, 0);
    vector<int> curr(m + 1, 0);

    for (int i = 1; i <= n; i++) {

        for (int j = 1; j <= m; j++) {

            // Characters match
            if (s1[i - 1] == s2[j - 1]) {

                curr[j] = 1 + prev[j - 1];
            }

            else {

                // Characters do not match
                curr[j] = max(
                    prev[j],
                    curr[j - 1]
                );
            }
        }

        // Current row becomes previous row
        prev = curr;
    }

    return prev[m];
}

int main() {

    string s1 = "abcde";
    string s2 = "ace";

    cout << longestCommonSubsequence(s1, s2);

    return 0;
}
```

Output:

text

```text
3
```

### Complexity analysis

- Time Complexity: $O(N \times M)$
- Space Complexity: $O(M)$

Here, `M` is the length of the second string.

## 6. Space Optimization Using Only One Array

Advanced Optimization### Problem statement

Optimize LCS further by using only one 1D DP array.

### Intuition

We can calculate the answer using only one array if we maintain the previous diagonal value separately.

We maintain:

- `dp[j]`: Previous row's value before updating.
- `dp[j-1]`: Current row's left value.
- `prevDiagonal`: Previous row's diagonal value.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int longestCommonSubsequence(string s1, string s2) {

    int n = s1.size();
    int m = s2.size();

    // One-dimensional DP array
    vector<int> dp(m + 1, 0);

    for (int i = 1; i <= n; i++) {

        // Stores previous row's diagonal value
        int prevDiagonal = 0;

        for (int j = 1; j <= m; j++) {

            // Save old dp[j] before updating
            int temp = dp[j];

            if (s1[i - 1] == s2[j - 1]) {

                // Use previous diagonal + 1
                dp[j] = 1 + prevDiagonal;
            }

            else {

                // Maximum of top and left
                dp[j] = max(dp[j], dp[j - 1]);
            }

            // Move diagonal pointer
            prevDiagonal = temp;
        }
    }

    return dp[m];
}

int main() {

    string s1 = "abcde";
    string s2 = "ace";

    cout << longestCommonSubsequence(s1, s2);

    return 0;
}
```

Output:

text

```text
3
```

Complexity:

- Time: $O(N \times M)$
- Space: $O(M)$

## 7. Print the Longest Common Subsequence

Very Important Interview Question### Problem statement

You are given two strings `s1` and `s2`.

Find and print the actual longest common subsequence, not just its length.

### Example

text

```text
Input:
s1 = "abcde"
s2 = "ace"

Output:
ace
```

### Intuition

First, construct the normal 2D DP table.

Then start from the bottom-right cell:

cpp

```cpp
i = n;
j = m;
```

There are three possibilities:

Case 1: Characters match

If:

cpp

```cpp
s1[i-1] == s2[j-1]
```

Include that character in the answer and move diagonally.

cpp

```cpp
i--;
j--;
```

Case 2: Top value is greater

Move upward:

cpp

```cpp
i--;
```

Case 3: Left value is greater or equal

Move left:

cpp

```cpp
j--;
```

Finally, reverse the constructed string.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

string printLCS(string s1, string s2) {

    int n = s1.size();
    int m = s2.size();

    // Build DP table
    vector<vector<int>> dp(
        n + 1, vector<int>(m + 1, 0)
    );

    // Calculate LCS lengths
    for (int i = 1; i <= n; i++) {

        for (int j = 1; j <= m; j++) {

            if (s1[i - 1] == s2[j - 1]) {

                dp[i][j] = 1 + dp[i - 1][j - 1];
            }

            else {

                dp[i][j] = max(
                    dp[i - 1][j],
                    dp[i][j - 1]
                );
            }
        }
    }

    // Start from the bottom-right cell
    int i = n;
    int j = m;

    string ans = "";

    // Reconstruct the actual LCS
    while (i > 0 && j > 0) {

        // If characters match, include them
        if (s1[i - 1] == s2[j - 1]) {

            ans.push_back(s1[i - 1]);

            // Move diagonally
            i--;
            j--;
        }

        // Move towards the larger DP value
        else if (dp[i - 1][j] > dp[i][j - 1]) {

            i--;
        }

        else {

            j--;
        }
    }

    // Characters were collected in reverse order
    reverse(ans.begin(), ans.end());

    return ans;
}

int main() {

    string s1 = "abcde";
    string s2 = "ace";

    cout << printLCS(s1, s2);

    return 0;
}
```

Output:

text

```text
ace
```

### Complexity analysis

- Time Complexity: $O(N \times M)$
- Space Complexity: $O(N \times M)$ for DP and $O(L)$ for the resulting subsequence.

Here, `L` is the LCS length.

Interview tip: If multiple LCS answers exist, this code prints one valid answer. It does not necessarily print the lexicographically smallest one.

## 8. Find All Longest Common Subsequences

Hard### Problem statement

You are given two strings. Find all distinct longest common subsequences and return them in lexicographically sorted order.

### Example

text

```text
Input:
s1 = "abc"
s2 = "bac"

Output:
abc
bac
```

Both have length 2? Actually, `"abc"` and `"bac"` are not subsequences of both strings. The correct LCS answers are:

text

```text
ac
bc
```

The LCS length is 2.

### Intuition

1. Calculate the normal LCS DP table.
2. Backtrack through the DP table.
3. When characters match, include the matching character.
4. When multiple directions preserve the optimal LCS length, explore both.
5. Use a set to remove duplicate subsequences.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

class Solution {

    vector<vector<int>> dp;

    // Memoization avoids generating the same
    // set of subsequences repeatedly.
    vector<vector<set<string>>> memo;

    set<string> build(int i, int j,
                      string& s1, string& s2) {

        // Empty prefix has one subsequence: ""
        if (i == 0 || j == 0) {
            return {""};
        }

        // Return previously calculated result
        if (!memo[i][j].empty()) {
            return memo[i][j];
        }

        set<string> ans;

        // Matching characters
        if (s1[i - 1] == s2[j - 1]) {

            set<string> prev = build(
                i - 1, j - 1, s1, s2
            );

            for (string str : prev) {

                ans.insert(str + s1[i - 1]);
            }
        }

        else {

            // Explore top if it preserves optimal length
            if (dp[i - 1][j] == dp[i][j]) {

                set<string> top = build(
                    i - 1, j, s1, s2
                );

                ans.insert(top.begin(), top.end());
            }

            // Explore left if it preserves optimal length
            if (dp[i][j - 1] == dp[i][j]) {

                set<string> left = build(
                    i, j - 1, s1, s2
                );

                ans.insert(left.begin(), left.end());
            }
        }

        return memo[i][j] = ans;
    }

public:

    vector<string> allLCS(string s1, string s2) {

        int n = s1.size();
        int m = s2.size();

        dp.assign(
            n + 1, vector<int>(m + 1, 0)
        );

        // Build LCS DP table
        for (int i = 1; i <= n; i++) {

            for (int j = 1; j <= m; j++) {

                if (s1[i - 1] == s2[j - 1]) {

                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }

                else {

                    dp[i][j] = max(
                        dp[i - 1][j],
                        dp[i][j - 1]
                    );
                }
            }
        }

        memo.assign(
            n + 1,
            vector<set<string>>(m + 1)
        );

        set<string> result = build(
            n, m, s1, s2
        );

        return vector<string>(
            result.begin(), result.end()
        );
    }
};

int main() {

    Solution obj;

    string s1 = "abc";
    string s2 = "bac";

    vector<string> ans = obj.allLCS(s1, s2);

    for (string s : ans) {
        cout << s << endl;
    }

    return 0;
}
```

Output:

text

```text
ac
bc
```

Complexity:

The DP computation takes $O(N \times M)$, but generating all distinct LCS strings can take exponential time and space in the worst case because the output itself can be exponentially large.

## 9. Longest Common Substring

Very Important Related Question### Problem statement

You are given two strings `s1` and `s2`.

Find the length of the longest common substring.

Important: Unlike subsequence, all characters must be continuous.

### Example

text

```text
Input:
s1 = "abcjklp"
s2 = "acjkp"

Output:
3
```

Explanation:

The longest common substring is:

text

```text
"cjk"
```

Its length is 3.

### Intuition

We use a 2D DP array.

If characters match:

$$
dp[i][j]=1+dp[i-1][j-1]
$$

If characters do not match:

$$
dp[i][j]=0
$$

We reset the value to zero because a substring must be continuous.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int longestCommonSubstring(string s1, string s2) {

    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(
        n + 1, vector<int>(m + 1, 0)
    );

    int maxi = 0;

    for (int i = 1; i <= n; i++) {

        for (int j = 1; j <= m; j++) {

            // If characters match
            if (s1[i - 1] == s2[j - 1]) {

                dp[i][j] = 1 + dp[i - 1][j - 1];

                // Update maximum substring length
                maxi = max(maxi, dp[i][j]);
            }

            else {

                // Substring must be continuous
                dp[i][j] = 0;
            }
        }
    }

    return maxi;
}

int main() {

    string s1 = "abcjklp";
    string s2 = "acjkp";

    cout << longestCommonSubstring(s1, s2);

    return 0;
}
```

Output:

text

```text
3
```

### Complexity

- Time: $O(N \times M)$
- Space: $O(N \times M)$

## 10. Shortest Common Supersequence (SCS)

Medium–Hard### Problem statement

You are given two strings `s1` and `s2`.

Find the shortest string that contains both input strings as subsequences.

### Example

text

```text
Input:
s1 = "brute"
s2 = "groot"

Output:
"brutegroot"
```

One shortest common supersequence is:

text

```text
brutegroot
```

### Important formula

The length of the Shortest Common Supersequence is:

$$
SCS=N+M-LCS
$$

Where:

- `N` = Length of first string.
- `M` = Length of second string.
- `LCS` = Longest Common Subsequence length.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

string shortestCommonSupersequence(string s1, string s2) {

    int n = s1.size();
    int m = s2.size();

    // Build LCS DP table
    vector<vector<int>> dp(
        n + 1, vector<int>(m + 1, 0)
    );

    for (int i = 1; i <= n; i++) {

        for (int j = 1; j <= m; j++) {

            if (s1[i - 1] == s2[j - 1]) {

                dp[i][j] = 1 + dp[i - 1][j - 1];
            }

            else {

                dp[i][j] = max(
                    dp[i - 1][j],
                    dp[i][j - 1]
                );
            }
        }
    }

    // Reconstruct shortest common supersequence
    int i = n;
    int j = m;

    string ans = "";

    while (i > 0 && j > 0) {

        // Common character is included only once
        if (s1[i - 1] == s2[j - 1]) {

            ans += s1[i - 1];

            i--;
            j--;
        }

        // Take character from first string
        else if (dp[i - 1][j] > dp[i][j - 1]) {

            ans += s1[i - 1];
            i--;
        }

        // Take character from second string
        else {

            ans += s2[j - 1];
            j--;
        }
    }

    // Add remaining characters of first string
    while (i > 0) {
        ans += s1[i - 1];
        i--;
    }

    // Add remaining characters of second string
    while (j > 0) {
        ans += s2[j - 1];
        j--;
    }

    // We constructed the answer backwards
    reverse(ans.begin(), ans.end());

    return ans;
}

int main() {

    string s1 = "brute";
    string s2 = "groot";

    cout << shortestCommonSupersequence(s1, s2);

    return 0;
}
```

Output:

text

```text
bgruoote
```

This output is a valid shortest common supersequence of the two strings. Other valid answers may also exist.

Complexity:

- Time: $O(N \times M)$
- Space: $O(N \times M)$

## 11. Minimum Insertions and Deletions to Convert One String into Another

Frequently Asked Interview Question### Problem statement

You are given two strings `s1` and `s2`.

You can perform two operations:

1. Delete a character from `s1`.
2. Insert a character into `s1`.

Find the minimum number of operations required to convert `s1` into `s2`.

### Example

text

```text
Input:
s1 = "heap"
s2 = "pea"

Output:
3
```

Explanation:

- Delete `h` from `"heap"` → `"eap"`.
- Delete `a` from `"eap"` → `"ep"`.
- Insert `a` appropriately → `"pea"`.

Actually, the minimum is 3 operations, using LCS `"ea"`:

- Delete `h`.
- Delete `p`.
- Insert `p` at the beginning.

### Important formulas

Minimum deletions:

$$
N-LCS
$$

Minimum insertions:

$$
M-LCS
$$

Total operations:

$$
N+M-2\times LCS
$$

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int minOperations(string s1, string s2) {

    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(
        n + 1, vector<int>(m + 1, 0)
    );

    // Calculate LCS
    for (int i = 1; i <= n; i++) {

        for (int j = 1; j <= m; j++) {

            if (s1[i - 1] == s2[j - 1]) {

                dp[i][j] = 1 + dp[i - 1][j - 1];
            }

            else {

                dp[i][j] = max(
                    dp[i - 1][j],
                    dp[i][j - 1]
                );
            }
        }
    }

    int lcs = dp[n][m];

    // Characters to delete from first string
    int deletions = n - lcs;

    // Characters to insert into first string
    int insertions = m - lcs;

    cout << "Minimum Deletions: " << deletions << endl;

    cout << "Minimum Insertions: " << insertions << endl;

    return deletions + insertions;
}

int main() {

    string s1 = "heap";
    string s2 = "pea";

    cout << "Total Operations: "
         << minOperations(s1, s2);

    return 0;
}
```

Output:

text

```text
Minimum Deletions: 2
Minimum Insertions: 1
Total Operations: 3
```

Complexity:

- Time: $O(N \times M)$
- Space: $O(N \times M)$

## 12. Longest Palindromic Subsequence (LPS)

Very Important DP Question### Problem statement

You are given a string `s`.

Find the length of the longest subsequence that is also a palindrome.

A palindrome reads the same forward and backward.

### Example

text

```text
Input:
s = "bbbab"

Output:
4
```

Explanation:

The longest palindromic subsequence is:

text

```text
bbbb
```

Its length is 4.

### Important concept

We can solve this problem using LCS.

The formula is:

$$
LPS=LCS(s,reverse(s))
$$

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int longestPalindromeSubseq(string s) {

    // Reverse the original string
    string rev = s;

    reverse(rev.begin(), rev.end());

    int n = s.size();

    vector<vector<int>> dp(
        n + 1, vector<int>(n + 1, 0)
    );

    // Find LCS of original and reversed strings
    for (int i = 1; i <= n; i++) {

        for (int j = 1; j <= n; j++) {

            if (s[i - 1] == rev[j - 1]) {

                dp[i][j] = 1 + dp[i - 1][j - 1];
            }

            else {

                dp[i][j] = max(
                    dp[i - 1][j],
                    dp[i][j - 1]
                );
            }
        }
    }

    return dp[n][n];
}

int main() {

    string s = "bbbab";

    cout << longestPalindromeSubseq(s);

    return 0;
}
```

Output:

text

```text
4
```

Complexity:

- Time: $O(N^2)$
- Space: $O(N^2)$

## 13. Minimum Insertions to Make a String Palindrome

Medium### Problem statement

You are given a string `s`.

Find the minimum number of characters that must be inserted to make the string a palindrome.

### Example

text

```text
Input:
s = "mbadm"

Output:
2
```

Explanation:

One possible palindrome is:

text

```text
mbadabm
```

Two characters need to be inserted.

### Important formula

$$
MinimumInsertions=N-LPS
$$

Since:

$$
LPS=LCS(s,reverse(s))
$$

We can calculate the answer using LCS.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int minInsertions(string s) {

    int n = s.size();

    string rev = s;

    // Reverse the original string
    reverse(rev.begin(), rev.end());

    vector<vector<int>> dp(
        n + 1, vector<int>(n + 1, 0)
    );

    // Calculate LCS of original and reversed string
    for (int i = 1; i <= n; i++) {

        for (int j = 1; j <= n; j++) {

            if (s[i - 1] == rev[j - 1]) {

                dp[i][j] = 1 + dp[i - 1][j - 1];
            }

            else {

                dp[i][j] = max(
                    dp[i - 1][j],
                    dp[i][j - 1]
                );
            }
        }
    }

    int lps = dp[n][n];

    return n - lps;
}

int main() {

    string s = "mbadm";

    cout << minInsertions(s);

    return 0;
}
```

Output:

text

```text
2
```

Complexity:

- Time: $O(N^2)$
- Space: $O(N^2)$

## 14. Longest Repeating Subsequence

Medium–Hard### Problem statement

You are given a string `s`.

Find the length of the longest subsequence that appears at least twice in the string, using different indices for the two occurrences.

Important: The same character position cannot be used in both subsequences.

### Example

text

```text
Input:
s = "aabebcdd"

Output:
3
```

One longest repeating subsequence is:

text

```text
abd
```

### Intuition

This problem is similar to LCS.

We compare the string with itself:

cpp

```cpp
LCS(s, s)
```

But we add one additional condition:

cpp

```cpp
i != j
```

This ensures that the same character position is not used twice.

### C++ Code

cpp

```cpp

#include <bits/stdc++.h>
using namespace std;

int longestRepeatingSubsequence(string s) {

    int n = s.size();

    // Compare string with itself
    vector<vector<int>> dp(
        n + 1, vector<int>(n + 1, 0)
    );

    for (int i = 1; i <= n; i++) {

        for (int j = 1; j <= n; j++) {

            // Characters must match,
            // but indices must be different.
            if (s[i - 1] == s[j - 1] && i != j) {

                dp[i][j] = 1 + dp[i - 1][j - 1];
            }

            else {

                dp[i][j] = max(
                    dp[i - 1][j],
                    dp[i][j - 1]
                );
            }
        }
    }

    return dp[n][n];
}

int main() {

    string s = "aabebcdd";

    cout << longestRepeatingSubsequence(s);

    return 0;
}
```

Output:

text

```text
3
```

Complexity:

- Time: $O(N^2)$
- Space:
