#include <stdio.h>
#include <stdlib.h>

int dp[1001][1001][2];

int max(int arr[], int size) {
    int max_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

int maxProfit(int day, int k, int holding, int prices[], int n) {
    if (day == n || k == 0) {
        return 0;
    }
    if (dp[day][k][holding] != -1) {
        return dp[day][k][holding];
    }

    int skip = maxProfit(day + 1, k, holding, prices, n);
    int buy = 0, sell = 0;

    if (!holding) {
        buy = -prices[day] + maxProfit(day + 1, k, 1, prices, n);
    } else {
        sell = prices[day] + maxProfit(day + 1, k - 1, 0, prices, n);
    }

    int profits[] = {skip, buy, sell};
    dp[day][k][holding] = max(profits, 3);
    return dp[day][k][holding];
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int prices[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &prices[i]);
    }

    for (int i = 0; i < 1001; i++) {
        for (int j = 0; j < 1001; j++) {
            dp[i][j][0] = -1;
            dp[i][j][1] = -1;
        }
    }

    printf("%d\n", maxProfit(0, k, 0, prices, n));
    return 0;
}
