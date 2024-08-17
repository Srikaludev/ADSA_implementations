#include<stdio.h>

// Function to find the maximum value obtainable by cutting up a rod of length n
int rodCutting(int price[], int n) {
    int dp[n + 1];
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        int max_val = -1;
        for (int j = 0; j < i; j++) {
            max_val = fmax(max_val, price[j] + dp[i - j - 1]);
        }
        dp[i] = max_val;
    }

    return dp[n];
}

int rodCuttingTopDown(int price[], int n, int memo[]) {
    if (n == 0) {
        return 0;
    }

    // Check if the result is already computed and stored in memo
    if (memo[n] != -1) {
        return memo[n];
    }

    int max_val = -1;

    // Recursively consider all possible cuts and calculate the maximum value
    for (int i = 0; i < n; i++) {
        max_val = fmax(max_val, price[i] + rodCuttingTopDown(price, n - i - 1, memo));
    }

    // Memoize the result before returning
    memo[n] = max_val;

    return max_val;
}
int main() {
    int n;
    printf("Enter the length of the rod: ");
    scanf("%d", &n);

    int price[n];
    printf("Enter the price for each piece of the rod:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &price[i]);
    }

    int max_value = rodCutting(price, n);

    printf("Maximum value obtainable by cutting up the rod: %d\n", max_value);

    return 0;
}
