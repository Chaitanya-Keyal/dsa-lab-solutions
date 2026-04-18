#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int lis[n];
    int lds[n];

    for (int i = 0; i < n; i++) {
        lis[i] = 1;
        lds[i] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && lis[j] + 1 > lis[i]) {
                lis[i] = lis[j] + 1;
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (arr[j] < arr[i] && lds[j] + 1 > lds[i]) {
                lds[i] = lds[j] + 1;
            }
        }
    }

    int max_len = 0;
    for (int i = 0; i < n; i++) {
        int len = lis[i] + lds[i] - 1;
        if (len > max_len) {
            max_len = len;
        }
    }
    printf("%d\n", max_len);

    return 0;
}
