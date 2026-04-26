#include <stdio.h>
#include <stdlib.h>

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int bay[m];
    for (int i = 0; i < m; i++) bay[i] = -1;

    for (int i = 0; i < n; i++) {
        int id;
        scanf("%d", &id);

        int idx = id % m;
        while (1) {
            if (bay[idx] == -1) {
                bay[idx] = id;
                break;
            }
            if (id >= 1000 && bay[idx] < 1000) {
                int kicked = bay[idx];
                bay[idx] = id;
                id = kicked;
            }
            idx = (idx + 1) % m;
        }
    }

    for (int i = 0; i < m; i++) {
        printf("%d ", bay[i]);
    }
    printf("\n");

    return 0;
}
