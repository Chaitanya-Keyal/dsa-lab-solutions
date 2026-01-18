#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

int main() {
    int N, K;
    scanf("%d", &N);
    scanf("%d", &K);
    int A[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    qsort(A, N, sizeof(int), compare);

    int maxCount = 0;
    int left = 0;

    for (int right = 0; right < N; right++) {
        while (A[right] - A[left] > K) {
            left++;
        }
        maxCount =
            (right - left + 1 > maxCount) ? (right - left + 1) : maxCount;
    }

    printf("%d\n", maxCount);
    return 0;
}
