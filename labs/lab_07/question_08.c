#include <stdio.h>
#include <stdlib.h>

#define MAX 1000005
#define LEN 32

char q[MAX][LEN];
int f = 0, r = -1, cnt = 0;

void enqueue(const char* x) {
    int i = 0;
    while (x[i] != '\0') {
        q[r + 1][i] = x[i];
        i++;
    }
    q[r + 1][i] = '\0';
    r++;
    cnt++;
}

void dequeue(char* out) {
    int i = 0;
    while (q[f][i] != '\0') {
        out[i] = q[f][i];
        i++;
    }
    out[i] = '\0';
    f++;
    cnt--;
}

char* front() { return q[f]; }

int size() { return cnt; }

int main() {
    char cur[LEN], s0[LEN], s1[LEN];
    int n;
    scanf("%d", &n);

    if (n <= 0) {
        printf("\n");
        return 0;
    }

    enqueue("1");

    for (int i = 1; i <= n; i++) {
        dequeue(cur);

        if (i > 1) printf(" ");
        printf("%s", cur);

        int len = 0;
        while (cur[len] != '\0') {
            s0[len] = cur[len];
            s1[len] = cur[len];
            len++;
        }
        s0[len] = '0';
        s0[len + 1] = '\0';
        s1[len] = '1';
        s1[len + 1] = '\0';

        enqueue(s0);
        enqueue(s1);
    }
    printf("\n");

    return 0;
}
