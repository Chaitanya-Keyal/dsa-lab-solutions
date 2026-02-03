#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, d;
    scanf("%d %d", &n, &d);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int max = 0, total = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        total += arr[i];
    }

    int l = max, r = total;
    while (l < r) {
        int mid = (l + r) / 2;
        int days = 1;
        int current_load = 0;
        for (int i = 0; i < n; i++) {
            if (current_load + arr[i] <= mid) {
                current_load += arr[i];
            } else {
                days++;
                current_load = arr[i];
            }
        }
        if (days <= d) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    printf("%d\n", l);

    return 0;
}
