#include <stdio.h>
#include <stdlib.h>

void sort(int intervals[][2], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (intervals[j][0] > intervals[j + 1][0]) {
                int temp[2];
                temp[0] = intervals[j][0];
                temp[1] = intervals[j][1];
                intervals[j][0] = intervals[j + 1][0];
                intervals[j][1] = intervals[j + 1][1];
                intervals[j + 1][0] = temp[0];
                intervals[j + 1][1] = temp[1];
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

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (count == 0 || intervals[i][0] > intervals[count - 1][1]) {
            intervals[count][0] = intervals[i][0];
            intervals[count][1] = intervals[i][1];
            count++;
        } else if (intervals[i][1] > intervals[count - 1][1]) {
            intervals[count - 1][1] = intervals[i][1];
        }
    }

    for (int i = 0; i < count; i++) {
        printf("%d %d\n", intervals[i][0], intervals[i][1]);
    }

    return 0;
}
