#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, h;
    scanf("%d %d", &n, &h);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int l = 1, r = 1e9;
    int res = r;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        long long total_hours = 0;

        for (int i = 0; i < n; i++) {
            total_hours += (arr[i] + mid - 1) / mid;
        }

        if (total_hours <= h) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    printf("%d\n", res);

    return 0;
}
