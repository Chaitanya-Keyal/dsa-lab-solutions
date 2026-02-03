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
    int index = 0;
    int group_size = 1;
    while (index < n) {
        int end_index = index + group_size;
        if (end_index > n) {
            end_index = n;
        }
        sort(arr, index, end_index);
        index += group_size;
        group_size++;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
