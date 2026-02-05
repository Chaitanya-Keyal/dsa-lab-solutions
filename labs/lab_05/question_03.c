#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int xor_all = 0;
    for (int i = 0; i < n; i++) {
        xor_all ^= arr[i];
    }

    int xor_left = 0;
    for (int i = 1; i < n - 1; i++) {
        xor_left ^= arr[i - 1];
        int xor_right = xor_all ^ xor_left ^ arr[i];
        if (xor_left == xor_right) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");

    return 0;
}
