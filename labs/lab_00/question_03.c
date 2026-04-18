#include <stdio.h>
#include <stdlib.h>

int dp[1001][1001];

int countWays(int i, int j, char source[], char target[]) {
    if (j == 0) {
        return 1;
    }
    if (i == 0) {
        return 0;
    }
    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    dp[i][j] = countWays(i - 1, j, source, target);
    if (source[i - 1] == target[j - 1]) {
        dp[i][j] += countWays(i - 1, j - 1, source, target);
    }

    return dp[i][j];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char source[n + 1];
    char target[m + 1];
    scanf("%s", source);
    scanf("%s", target);

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = -1;
        }
    }

    printf("%d\n", countWays(n, m, source, target));

    return 0;
}
