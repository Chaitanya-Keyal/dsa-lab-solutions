#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, g;
    scanf("%d %d", &n, &g);
    int arr[n];
    int max = 0;
    int total_income = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        total_income += arr[i];
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    if (total_income < g) {
        printf("-1\n");
        return 0;
    }
    int l = 0, r = max;
    while (l < r) {
        int mid = (l + r) / 2;
        int total_tax = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] <= mid) {
                total_tax += arr[i];
            } else {
                total_tax += mid;
            }
        }
        if (total_tax >= g) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    printf("%d\n", l);

    return 0;
}
