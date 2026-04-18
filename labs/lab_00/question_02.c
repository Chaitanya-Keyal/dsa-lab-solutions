#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int payment;
    int hours;
} Project;

int dp[1001][1001];

int maxPay(int n, int h, Project projects[]) {
    if (n == 0 || h == 0) {
        return 0;
    }
    if (dp[n][h] != -1) {
        return dp[n][h];
    }
    if (projects[n - 1].hours > h) {
        dp[n][h] = maxPay(n - 1, h, projects);
    } else {
        int include = projects[n - 1].payment + maxPay(n - 1, h - projects[n - 1].hours, projects);
        int exclude = maxPay(n - 1, h, projects);
        dp[n][h] = include > exclude ? include : exclude;
    }
    return dp[n][h];
}

int main() {
    int n, h;
    scanf("%d %d", &n, &h);
    Project projects[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &projects[i].payment);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &projects[i].hours);
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= h; j++) {
            dp[i][j] = -1;
        }
    }

    printf("%d\n", maxPay(n, h, projects));

    return 0;
}
