#include <stdio.h>
#include <stdlib.h>

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    int matrix[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    int a1, b1, a2, b2;
    scanf("%d %d %d %d", &a1, &b1, &a2, &b2);

    int prefix[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            prefix[i][j] = matrix[i][j];

            if (i > 0) prefix[i][j] += prefix[i - 1][j];

            if (j > 0) prefix[i][j] += prefix[i][j - 1];

            if (i > 0 && j > 0) prefix[i][j] -= prefix[i - 1][j - 1];
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", prefix[i][j]);
        }
        printf("\n");
    }

    int sum = prefix[a2 - 1][b2 - 1];
    if (a1 > 1) sum -= prefix[a1 - 2][b2 - 1];
    if (b1 > 1) sum -= prefix[a2 - 1][b1 - 2];
    if (a1 > 1 && b1 > 1) sum += prefix[a1 - 2][b1 - 2];

    printf("Sum = %d\n", sum);

    return 0;
}
