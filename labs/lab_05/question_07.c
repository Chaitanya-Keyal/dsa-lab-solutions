#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int k;
    scanf("%d", &k);

    int l = 0, r = n - 1;
    int target = n - k;  // kth largest is (n-k)th smallest
    while (l <= r) {
        int pivot = arr[r];
        int i = l;
        for (int j = l; j < r; j++) {
            if (arr[j] <= pivot) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
            }
        }
        arr[r] = arr[i];
        arr[i] = pivot;

        if (i == target) {
            printf("%d\n", arr[i]);
            break;
        } else if (i < target) {
            l = i + 1;
        } else {
            r = i - 1;
        }
    }

    return 0;
}
