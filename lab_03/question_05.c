#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int target;
    scanf("%d", &target);

    int l = 0, r = n - 1;
    int first = -1, last = -1;

    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == target) {
            first = mid;
            r = mid - 1;
        } else if (arr[mid] < target) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    l = 0;
    r = n - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == target) {
            last = mid;
            l = mid + 1;
        } else if (arr[mid] < target) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("%d %d\n", first, last);

    return 0;
}
