#include <stdio.h>
#include <stdlib.h>

void sort(int* arr, int start, int end) {
    for (int i = start; i < end - 1; i++) {
        for (int j = start; j < end - i + start - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int l = 0;
    int r = n - 1;
    int k = 1;
    while (l <= r) {
        if (r - l + 1 <= k) {
            sort(arr, l, r + 1);
            break;
        }
        if (k % 2 == 1) {
            sort(arr, l, l + k);
            l += k;
        } else {
            sort(arr, r - k + 1, r + 1);
            r -= k;
        }
        k++;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
