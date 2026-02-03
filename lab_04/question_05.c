#include <stdio.h>
#include <stdlib.h>

int count_ones(int x) {
    int count = 0;
    while (x) {
        count += x & 1;
        x >>= 1;
    }
    return count;
};

int compare(int a, int b) {
    int strength_a = count_ones(a);
    int strength_b = count_ones(b);

    if (strength_a != strength_b) {
        return strength_b - strength_a;  // Higher strength first
    } else {
        return b - a;  // Higher numerical value first
    }
}

void sort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compare(arr[j], arr[j + 1]) > 0) {
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
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
