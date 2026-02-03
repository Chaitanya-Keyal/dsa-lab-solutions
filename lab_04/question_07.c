#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int l = 0, r = n - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        int missing_count = arr[mid] - (mid + 1);
        if (missing_count < k) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("%d\n", l + k);

    return 0;
}
