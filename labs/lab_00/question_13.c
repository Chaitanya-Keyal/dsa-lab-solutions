#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) { return a < b ? a : b; }

int dp[1001][1001];

int solve(int left, int right, int caches[]) {
    if (left > right) {
        return 0;
    }
    if (left == right) {
        return caches[left];
    }
    if (dp[left][right] != -1) {
        return dp[left][right];
    }

    int pickLeft =
        caches[left] + min(solve(left + 2, right, caches), solve(left + 1, right - 1, caches));
    int pickRight =
        caches[right] + min(solve(left + 1, right - 1, caches), solve(left, right - 2, caches));

    dp[left][right] = pickLeft > pickRight ? pickLeft : pickRight;
    return dp[left][right];
}

int main() {
    int n;
    scanf("%d", &n);
    int caches[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &caches[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }

    printf("%d\n", solve(0, n - 1, caches));

    return 0;
}
