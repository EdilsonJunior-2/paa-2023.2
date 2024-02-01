#include <stdio.h>

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve the 0/1 Knapsack problem with two constraints (weight and volume)
int knapsack(int W, int V, int wt[], int vol[], int val[], int n) {
    int i, w, v;
    int dp[n + 1][W + 1][V + 1];

    // Build the dp table in a bottom-up manner
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            for (v = 0; v <= V; v++) {
                if (i == 0 || w == 0 || v == 0)
                    dp[i][w][v] = 0;
                else if (wt[i - 1] <= w && vol[i - 1] <= v)
                    dp[i][w][v] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]][v - vol[i - 1]], dp[i - 1][w][v]);
                else
                    dp[i][w][v] = dp[i - 1][w][v];
            }
        }
    }

    // The result is stored in dp[n][W][V]
    return dp[n][W][V];
}

int main() {
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 15};
    int vol[] = {3, 2, 1};
    int W = 50;
    int V = 5;
    int n = sizeof(val) / sizeof(val[0]);

    printf("Maximum value that can be obtained = %d\n", knapsack(W, V, wt, vol, val, n));

    return 0;
}
