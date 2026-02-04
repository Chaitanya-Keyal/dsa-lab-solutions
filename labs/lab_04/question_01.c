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
    int k;
    scanf("%d", &k);

    int row = 0, col = n - 1;
    while (row < m && col >= 0) {
        if (matrix[row][col] == k) {
            printf("%d %d\n", row, col);
            return 0;
        } else if (matrix[row][col] > k) {
            col--;
        } else {
            row++;
        }
    }
    printf("-1\n");
    return 0;
}
