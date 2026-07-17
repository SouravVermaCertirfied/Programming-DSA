## Dynamic Programming (DP)

**Dynamic Programming** is an optimization technique used to solve problems that have: - **Overlapping subproblems** and  **Optimal substructure**.

DP trades extra memory for faster execution by avoiding repeated work.

> It is not nesssary that DP uses a extra space or recursion. As long as Overlapping subproblems and optimal substructure are present it is considered a DP. Eg Kandane's Algoirthm.
### Core Idea
Solve each subproblem once and **store its result** to avoid recomputation.

### 🧠 Approaches
1. **Memoization (Top-Down)** =  Recursive + Uses cache (DP array/map)
2. **Tabulation (Bottom-Up)**  = Iterative + Builds solution from base cases
---
| Feature           | Memoization (Top-Down DP)                         | Tabulation (Bottom-Up DP)                          |
| ----------------- | ------------------------------------------------- | -------------------------------------------------- |
| Approach          | Uses recursion                                    | Uses iteration (loops)                             |
| Direction         | Starts from the final problem and breaks down     | Starts from the smallest subproblems and builds up |
| Storage           | Uses a DP array/table to store computed results   | Uses a DP array/table to store results             |
| Calculation order | Only calculates required states                   | Calculates all states                              |
| Recursion         | Required                                          | Not required                                       |
| Stack memory      | Uses recursion stack                              | No recursion stack                                 |
| Speed             | Usually slightly slower due to recursion overhead | Usually faster due to iterative approach           |
| Code complexity   | Easier to write from recursive solutions          | Requires understanding the order of computation    |

---

## Example Issustration
Find Nth Fibonacci number using both the memoization and tabulation approch.

### 1. Memoization
```c
int helper(int n, vector<int> &dp){
    if(dp[n]!=-1) return dp[n];
    if(n==0 || n==1){ 
        dp[n] = n;
        return n;
    }
    dp[n] = helper(n-2, dp) + helper(n-1, dp);
    return dp[n];
}
int fib(int n) {
    vector<int> dp(n+1, -1);
    helper(n, dp);
    return dp[n];
}
```

### 2. Tabulation 
```c
int fibonacci(int n) {
    if (n <= 1)
        return n;

    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2];

    return dp[n];
}

```

## 3. Best solution for Fiboncci
The above approches are only used to show the memoization and tablulation techique. however, the best approch to solve this question is as below. using only two extra variables and 1 pass.  
This shows that DP may not always be the optimal solution.

```c
int fib(int n){

    if(n==1 || n==0)
        return n;
    int a = 0;
    int b = 1;
    int sum = 0;
    for(int i=2; i<=n; i++){
        sum = a + b;
        a = b;
        b = sum;
    }
    return sum;
}
```