#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int l = 1, r = arr[n - 1] - arr[0], ans = 0;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        int count = 1, last_pos = arr[0];
        for (int i = 1; i < n; i++) {
            if (arr[i] - last_pos >= mid) {
                count++;
                last_pos = arr[i];
            }
        }
        if (count >= k) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("%d\n", ans);

    return 0;
}
