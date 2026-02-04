#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

int main() {
    int N;
    scanf("%d", &N);
    int A[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    int B[N + 2];
    for (int i = 0; i < N + 2; i++) {
        scanf("%d", &B[i]);
    }
    qsort(A, N, sizeof(int), compare);
    qsort(B, N + 2, sizeof(int), compare);
    int i = 0, j = 0;
    while (i < N && j < N + 2) {
        if (A[i] == B[j]) {
            i++;
            j++;
        } else {
            printf("%d ", B[j]);
            j++;
        }
    }
    while (j < N + 2) {
        printf("%d ", B[j]);
        j++;
    }

    return 0;
}
