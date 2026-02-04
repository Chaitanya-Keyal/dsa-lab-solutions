#include <stdio.h>
#include <stdlib.h>

int findUnion(int* A, int N1, int* B, int N2) {
    int unionArr[N1 + N2];
    int k = 0;

    for (int i = 0; i < N1; i++) {
        unionArr[k++] = A[i];
    }

    for (int i = 0; i < N2; i++) {
        int found = 0;
        for (int j = 0; j < N1; j++) {
            if (B[i] == A[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            unionArr[k++] = B[i];
        }
    }

    printf("Union: ");
    for (int i = 0; i < k; i++) {
        printf("%d ", unionArr[i]);
    }

    return 0;
}

int findIntersection(int* A, int N1, int* B, int N2) {
    printf("Intersection: ");
    int foundAny = 0;
    for (int i = 0; i < N1; i++) {
        for (int j = 0; j < N2; j++) {
            if (A[i] == B[j]) {
                printf("%d ", A[i]);
                foundAny = 1;
                break;
            }
        }
    }
    if (!foundAny) {
        printf("(None)");
    }
    return 0;
}

int main() {
    int N1, N2;
    scanf("%d", &N1);
    int A[N1];
    for (int i = 0; i < N1; i++) {
        scanf("%d", &A[i]);
    }
    scanf("%d", &N2);
    int B[N2];
    for (int i = 0; i < N2; i++) {
        scanf("%d", &B[i]);
    }

    findUnion(A, N1, B, N2);
    printf("\n");
    findIntersection(A, N1, B, N2);

    return 0;
}
