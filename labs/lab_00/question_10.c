#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int dp[1001][1001];
int minCost(int i, int j, int cuts[]) {
    if (i > j) {
        return 0;
    }
    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    int cost = cuts[j + 1] - cuts[i - 1];
    int min_cost = 1000000000;
    for (int k = i; k <= j; k++) {
        int current_cost = cost + minCost(i, k - 1, cuts) + minCost(k + 1, j, cuts);
        if (current_cost < min_cost) {
            min_cost = current_cost;
        }
    }
    dp[i][j] = min_cost;
    return dp[i][j];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int cuts[m + 2];
    cuts[0] = 0;
    for (int i = 0; i < m; i++) {
        scanf("%d", &cuts[i + 1]);
    }
    cuts[m + 1] = n;
    sort(cuts, m + 2);
    for (int i = 0; i <= m + 1; i++) {
        for (int j = 0; j <= m + 1; j++) {
            dp[i][j] = -1;
        }
    }
    printf("%d\n", minCost(1, m, cuts));
    return 0;
}
