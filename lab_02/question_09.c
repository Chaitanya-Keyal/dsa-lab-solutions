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
    qsort(A, N, sizeof(int), compare);
    int even = 0;
    int odd = 0;
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0 && A[i] % 2 == 0) {
            even++;
        } else if (i % 2 == 1 && A[i] % 2 == 1) {
            odd++;
        }
    }
    printf("%d, %d\n", even, odd);
    return 0;
}
