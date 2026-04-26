#include <stdio.h>
#include <stdlib.h>

int main() {
    int m, q;
    scanf("%d %d", &m, &q);

    int table[m];
    for (int i = 0; i < m; i++) table[i] = -1;

    for (int i = 0; i < q; i++) {
        int op, x;
        scanf("%d %d", &op, &x);

        int h = x % m;

        if (op == 1) {
            int first_deleted = -1;
            for (int j = 0; j < m; j++) {
                int idx = (h + j) % m;
                if (table[idx] == -2 && first_deleted == -1) first_deleted = idx;
                if (table[idx] == -1) {
                    table[first_deleted != -1 ? first_deleted : idx] = x;
                    break;
                }
            }
            if (first_deleted != -1 && table[first_deleted] != x) {
                table[first_deleted] = x;
            }

        } else if (op == 2) {
            for (int j = 0; j < m; j++) {
                int idx = (h + j) % m;
                if (table[idx] == -1) break;
                if (table[idx] == x) {
                    table[idx] = -2;
                    break;
                }
            }

        } else {
            int found = 0;
            for (int j = 0; j < m; j++) {
                int idx = (h + j) % m;
                if (table[idx] == -1) break;
                if (table[idx] == x) {
                    found = 1;
                    break;
                }
            }
            printf("%s\n", found ? "Found" : "Not Found");
        }
    }

    for (int i = 0; i < m; i++) {
        printf("%d ", table[i]);
    }
    printf("\n");

    return 0;
}
