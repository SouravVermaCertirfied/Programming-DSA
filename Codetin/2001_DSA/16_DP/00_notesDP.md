## Dynamic Programming (DP)

**Dynamic Programming** is an optimization technique used to solve problems that have: - **Overlapping subproblems** and  **Optimal substructure**.

DP trades extra memory for faster execution by avoiding repeated work.

> It is not nesssary that DP uses a extra space or recursion. As long as Overlapping subproblems and optimal substructure are present it is considered a DP. Eg Kandane's Algoirthm.
### Core Idea
Solve each subproblem once and **store its result** to avoid recomputation.

### 🧠 Approaches
1. **Memoization (Top-Down)** =  Recursive + Uses cache (DP array/map)

2. **Tabulation (Bottom-Up)**  = Iterative + Builds solution from base cases

## Example Issustration
Find Nth Fibonacci number using both the memoization and tabulation approch.

### 1. Memoization
```c
int fibonacci(int n, vector<int>& dp) {
    if (n <= 1)
        return n;

    if (dp[n] != -1)
        return dp[n];

    return dp[n] = fibonacci(n - 1, dp) + fibonacci(n - 2, dp);
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
    int a, b, c = 0;
    for(int i=0; i<=n; i++){
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}
```