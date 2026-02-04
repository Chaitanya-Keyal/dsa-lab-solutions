#include <stdio.h>
#include <stdlib.h>

int compare(int a[2], int b[2]) {
    if (a[0] != b[0]) {
        return a[0] - b[0];
    }
    return a[1] - b[1];
}

void sort(int intervals[][2], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compare(intervals[j], intervals[j + 1]) > 0) {
                int temp0 = intervals[j][0];
                int temp1 = intervals[j][1];
                intervals[j][0] = intervals[j + 1][0];
                intervals[j][1] = intervals[j + 1][1];
                intervals[j + 1][0] = temp0;
                intervals[j + 1][1] = temp1;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int intervals[n][2];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &intervals[i][0], &intervals[i][1]);
    }

    sort(intervals, n);

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", intervals[i][0], intervals[i][1]);
    }

    int max_end = intervals[0][1];
    int contiguous = 1;
    for (int i = 1; i < n; i++) {
        if (intervals[i][0] > max_end) {
            contiguous = 0;
            break;
        }
        if (intervals[i][1] > max_end) {
            max_end = intervals[i][1];
        }
    }

    if (contiguous) {
        printf("Contiguous\n");
    } else {
        printf("Fragmented\n");
    }

    return 0;
}
