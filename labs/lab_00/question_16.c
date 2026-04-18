#include <stdio.h>
#include <stdlib.h>

int mergeAndCount(int arr[], int temp[], int left, int mid, int right, int k) {
    int i = left;
    int j = mid;
    int count = 0;

    for (int x = left; x < mid; x++) {
        while (j <= right && arr[x] > (long long)k * arr[j]) {
            j++;
        }
        count += j - mid;
    }

    i = left;
    j = mid;
    int index = left;

    while (i < mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[index++] = arr[i++];
        } else {
            temp[index++] = arr[j++];
        }
    }

    while (i < mid) {
        temp[index++] = arr[i++];
    }
    while (j <= right) {
        temp[index++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return count;
}

int mergeSortAndCount(int arr[], int temp[], int left, int right, int k) {
    int count = 0;
    if (left < right) {
        int mid = (left + right) / 2;

        count += mergeSortAndCount(arr, temp, left, mid, k);
        count += mergeSortAndCount(arr, temp, mid + 1, right, k);

        count += mergeAndCount(arr, temp, left, mid + 1, right, k);
    }
    return count;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int temp[n];
    int result = mergeSortAndCount(arr, temp, 0, n - 1, k);
    printf("%d\n", result);

    return 0;
}
