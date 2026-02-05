#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int matrix[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int layers = (n < m ? n : m) / 2;
    for (int layer = 0; layer < layers; layer++) {
        int top = layer, bottom = n - layer - 1;
        int left = layer, right = m - layer - 1;

        if (top == bottom || left == right) continue;

        int saved = matrix[top][left];

        if (layer % 2 == 0) {  // Odd layer (0-based)
            for (int i = top; i < bottom; i++) matrix[i][left] = matrix[i + 1][left];
            for (int j = left; j < right; j++) matrix[bottom][j] = matrix[bottom][j + 1];
            for (int i = bottom; i > top; i--) matrix[i][right] = matrix[i - 1][right];
            for (int j = right; j > left + 1; j--) matrix[top][j] = matrix[top][j - 1];
            matrix[top][left + 1] = saved;
        } else {
            for (int j = left; j < right; j++) matrix[top][j] = matrix[top][j + 1];
            for (int i = top; i < bottom; i++) matrix[i][right] = matrix[i + 1][right];
            for (int j = right; j > left; j--) matrix[bottom][j] = matrix[bottom][j - 1];
            for (int i = bottom; i > top + 1; i--) matrix[i][left] = matrix[i - 1][left];
            matrix[top + 1][left] = saved;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
