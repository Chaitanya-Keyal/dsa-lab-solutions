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

    int pivot = 0, l = 0, r = n - 1;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] > arr[r]) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    pivot = l;

    l = 0;
    r = n - 1;
    if (target >= arr[pivot] && target <= arr[r]) {
        l = pivot;
    } else {
        r = pivot - 1;
    }

    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == target) {
            printf("%d\n", mid);
            return 0;
        } else if (arr[mid] < target) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("-1\n");

    return 0;
}
