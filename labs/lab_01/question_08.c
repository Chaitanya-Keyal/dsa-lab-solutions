#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);
    int arr[N], D, K;
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    scanf("%d", &D);
    scanf("%d", &K);
    K = K % N;
    if (D == 0) {  // Left Rotate
        for (int i = 0; i < N; i++) {
            printf("%d ", arr[(i + K) % N]);
        }
    } else {  // Right Rotate
        for (int i = 0; i < N; i++) {
            printf("%d ", arr[(i - K + N) % N]);
        }
    }
    printf("\n");

    return 0;
}
