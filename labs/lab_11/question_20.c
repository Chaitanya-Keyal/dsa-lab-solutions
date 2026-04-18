#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int piles[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &piles[i]);
    }

    if ((n - 1) % (k - 1) != 0) {
        printf("-1\n");
        return 0;
    }

    int pref[n + 1];
    pref[0] = 0;
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + piles[i];
    }

    int dp[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = (i == j) ? 0 : 1000000000;
        }
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;

            for (int m = i; m < j; m += (k - 1)) {
                int candidate = dp[i][m] + dp[m + 1][j];
                if (candidate < dp[i][j]) {
                    dp[i][j] = candidate;
                }
            }

            if ((len - 1) % (k - 1) == 0) {
                dp[i][j] += pref[j + 1] - pref[i];
            }
        }
    }

    printf("%d\n", dp[0][n - 1]);
    return 0;
}
