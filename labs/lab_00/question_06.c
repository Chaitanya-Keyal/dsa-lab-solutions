#include <stdio.h>
#include <stdlib.h>

int dp[1001][1001];

int max_palindrome(int i, int j, char s[]) {
    if (i > j) {
        return 0;
    }
    if (i == j) {
        return 1;
    }
    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    if (s[i] == s[j]) {
        dp[i][j] = 2 + max_palindrome(i + 1, j - 1, s);
    } else {
        int skip_left = max_palindrome(i + 1, j, s);
        int skip_right = max_palindrome(i, j - 1, s);
        dp[i][j] = skip_left > skip_right ? skip_left : skip_right;
    }

    return dp[i][j];
}

int main() {
    int n;
    scanf("%d", &n);
    char s[n + 1];
    scanf("%s", s);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = -1;
        }
    }
    printf("%d\n", max_palindrome(0, n - 1, s));

    return 0;
}
