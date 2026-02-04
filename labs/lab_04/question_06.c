#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int r, c;
    scanf("%d %d", &r, &c);
    int matrix[r][c];
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int low = 1, high = INT_MAX;
    int desired = (r * c + 1) / 2;
    while (low < high) {
        int mid = low + (high - low) / 2;
        int place = 0;

        for (int i = 0; i < r; i++) {
            int l = 0, h = c - 1;
            while (l <= h) {
                int m = l + (h - l) / 2;
                if (matrix[i][m] <= mid) {
                    l = m + 1;
                } else {
                    h = m - 1;
                }
            }
            place += l;
        }

        if (place < desired) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    printf("%d\n", low);

    return 0;
}
