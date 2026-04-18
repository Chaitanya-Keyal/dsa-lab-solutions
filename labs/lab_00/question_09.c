#include <stdio.h>
#include <stdlib.h>

int dp[1001][1001];

int min(int arr[], int size) {
    int minimum = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < minimum) {
            minimum = arr[i];
        }
    }
    return minimum;
}

int minSteps(int i, int j, char seqA[], char seqB[]) {
    if (i == 0) {
        return j;
    }
    if (j == 0) {
        return i;
    }
    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    if (seqA[i - 1] == seqB[j - 1]) {
        dp[i][j] = minSteps(i - 1, j - 1, seqA, seqB);
    } else {
        int insert_op = minSteps(i, j - 1, seqA, seqB) + 1;
        int delete_op = minSteps(i - 1, j, seqA, seqB) + 1;
        int replace_op = minSteps(i - 1, j - 1, seqA, seqB) + 1;
        int operations[3] = {insert_op, delete_op, replace_op};
        dp[i][j] = min(operations, 3);
    }
    return dp[i][j];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char seqA[n + 1];
    char seqB[m + 1];
    scanf("%s", seqA);
    scanf("%s", seqB);

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = -1;
        }
    }
    printf("%d\n", minSteps(n, m, seqA, seqB));

    return 0;
}
