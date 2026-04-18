#include <stdio.h>
#include <stdlib.h>

int dp[1001][1001];

int matches(int n, int m, char s[], char p[]) {
    if (m == 0) {
        return n == 0;
    }
    if (n == 0) {
        for (int i = 0; i < m; i++) {
            if (p[i] != '*') {
                return 0;
            }
        }
        return 1;
    }
    if (dp[n][m] != -1) {
        return dp[n][m];
    }

    if (p[m - 1] == s[n - 1] || p[m - 1] == '?') {
        dp[n][m] = matches(n - 1, m - 1, s, p);
    } else if (p[m - 1] == '*') {
        dp[n][m] = matches(n, m - 1, s, p) || matches(n - 1, m, s, p);
    } else {
        dp[n][m] = 0;
    }

    return dp[n][m];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char s[n + 1];
    char p[m + 1];
    scanf("%s", s);
    scanf("%s", p);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = -1;
        }
    }
    if (matches(n, m, s, p)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    return 0;
}
