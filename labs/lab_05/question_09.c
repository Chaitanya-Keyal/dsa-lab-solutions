#include <stdio.h>
#include <stdlib.h>

void sort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
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
    sort(arr, n);

    int found = 0;
    for (int i = 0; i < n - 2; i++) {
        if (arr[i] > 0) break;  // All remaining sums will be positive
        if (i > 0 && arr[i] == arr[i - 1]) continue;  // Skip duplicates
        if (arr[i] + arr[i + 1] + arr[i + 2] > 0)
            break;  // Smallest sum too large
        if (arr[i] + arr[n - 2] + arr[n - 1] < 0)
            continue;  // Largest sum too small
        int l = i + 1, r = n - 1;
        while (l < r) {
            int sum = arr[i] + arr[l] + arr[r];
            if (sum == 0) {
                printf("%d %d %d\n", arr[i], arr[l], arr[r]);
                found = 1;
                while (l < r && arr[l] == arr[l + 1]) l++;
                while (l < r && arr[r] == arr[r - 1]) r--;
                l++;
                r--;
            } else if (sum < 0) {
                l++;
            } else {
                r--;
            }
        }
    }
    if (!found) {
        printf("No triplets found\n");
    }

    return 0;
}
