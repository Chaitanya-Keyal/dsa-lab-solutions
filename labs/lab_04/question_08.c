#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int arr[n];
    int max = 0, total = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        if (arr[i] > max) {
            max = arr[i];
        }
        total += arr[i];
    }

    int l = max, r = total;
    while (l < r) {
        int mid = (l + r) / 2;
        int painters = 1;
        int current_load = 0;
        for (int i = 0; i < n; i++) {
            if (current_load + arr[i] <= mid) {
                current_load += arr[i];
            } else {
                painters++;
                current_load = arr[i];
            }
        }
        if (painters <= k) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    printf("%d\n", l);

    return 0;
}
