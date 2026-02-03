#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int l = 0, r = n - 1;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] > arr[mid + 1]) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    printf("%d\n", l);

    return 0;
}
