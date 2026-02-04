#include <stdio.h>
#include <stdlib.h>

int main() {
    int N1, N2;
    scanf("%d", &N1);
    int arr1[N1];
    for (int i = 0; i < N1; i++) {
        scanf("%d", &arr1[i]);
    }
    scanf("%d", &N2);
    int arr2[N2];
    for (int i = 0; i < N2; i++) {
        scanf("%d", &arr2[i]);
    }

    int mergedSize = N1 + N2;
    int merged[mergedSize];
    int i = 0, j = 0, k = 0;
    while (i < N1 && j < N2) {
        if (arr1[i] < arr2[j]) {
            merged[k++] = arr1[i++];
        } else {
            merged[k++] = arr2[j++];
        }
    }
    while (i < N1) {
        merged[k++] = arr1[i++];
    }
    while (j < N2) {
        merged[k++] = arr2[j++];
    }
    for (int i = 0; i < mergedSize; i++) {
        printf("%d ", merged[i]);
    }

    return 0;
}
