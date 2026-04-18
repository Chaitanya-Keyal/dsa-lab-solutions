#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) { return a > b ? a : b; }

int solve(int arr[], int left, int right) {
    if (left > right) {
        return -1000000000;
    }
    if (left == right) {
        return arr[left];
    }

    int mid = (left + right) / 2;
    int leftMax = solve(arr, left, mid);
    int rightMax = solve(arr, mid + 1, right);

    int crossMax = arr[mid];
    int sum = arr[mid];
    for (int i = mid - 1; i >= left; i--) {
        sum += arr[i];
        crossMax = max(crossMax, sum);
    }
    sum = crossMax;
    for (int i = mid + 1; i <= right; i++) {
        sum += arr[i];
        crossMax = max(crossMax, sum);
    }

    return max(max(leftMax, rightMax), crossMax);
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("%d\n", solve(arr, 0, n - 1));
    return 0;
}
