#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    int a[n];
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j]) {
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }

    int max_levels = 1;
    while ((1 << max_levels) < n) max_levels++;

    int top = 0;
    while ((1 << (top + 1)) < n) top++;

    int stride[max_levels + 1];
    int lsize[max_levels + 1];
    int* levels[max_levels + 1];

    for (int i = 0; i <= top; i++) {
        stride[i] = 1 << i;
        lsize[i] = 0;
        for (int j = 0; j < n; j += stride[i]) lsize[i]++;
        levels[i] = malloc(lsize[i] * sizeof(int));
        int idx = 0;
        for (int j = 0; j < n; j += stride[i]) levels[i][idx++] = a[j];
    }

    for (int qi = 0; qi < q; qi++) {
        int x;
        scanf("%d", &x);

        int steps = 0;
        int level = top;
        int pos = 0;
        int found = 0;

        while (1) {
            if (levels[level][pos] == x) {
                found = 1;
                break;
            }

            if (pos + 1 < lsize[level] && levels[level][pos + 1] <= x) {
                pos++;
                steps++;
            } else {
                if (level == 0) break;
                int val = levels[level][pos];
                int new_pos = pos * 2;
                level--;
                pos = new_pos;
                steps++;
            }
        }
        printf("%d ", found ? steps : -1);
    }
    printf("\n");

    return 0;
}
