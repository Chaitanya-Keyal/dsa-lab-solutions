#include <stdio.h>
#include <stdlib.h>

int dp[1000][1000];

int paths(int i, int j) {
    if (i < 0 || j < 0) {
        return 0;
    }
    if (dp[i][j] != -1) {
        return dp[i][j];
    }
    dp[i][j] = paths(i - 1, j) + paths(i, j - 1);
    return dp[i][j];
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    int grid[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
            dp[i][j] = -1;
        }
    }
    dp[0][0] = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                dp[i][j] = 0;
            }
        }
    }
    printf("%d\n", paths(m - 1, n - 1) % 1000000007);
    return 0;
}
