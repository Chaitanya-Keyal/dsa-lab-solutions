#include <stdio.h>
#include <stdlib.h>

#define MAX 1000005

int time_arr[MAX], dir_arr[MAX], ans[MAX];
int q0[MAX], q1[MAX];
int f0 = 0, r0 = -1, c0 = 0;
int f1 = 0, r1 = -1, c1 = 0;

void enqueue0(int x) {
    q0[++r0] = x;
    c0++;
}
int dequeue0() {
    c0--;
    return q0[f0++];
}

void enqueue1(int x) {
    q1[++r1] = x;
    c1++;
}
int dequeue1() {
    c1--;
    return q1[f1++];
}

int main() {
    int n = 0;
    int i = 0, served = 0;
    int t = 0;
    int last_dir = -1;

    while (scanf("%d", &time_arr[n]) == 1) {
        n++;
        int ch = getchar();
        if (ch == '\n' || ch == EOF) break;
    }

    for (int j = 0; j < n; j++) {
        scanf("%d", &dir_arr[j]);
    }

    while (served < n) {
        if (c0 == 0 && c1 == 0 && i < n && t < time_arr[i]) {
            t = time_arr[i];
            last_dir = -1;
        }

        while (i < n && time_arr[i] <= t) {
            if (dir_arr[i] == 0) {
                enqueue0(i);
            } else {
                enqueue1(i);
            }
            i++;
        }

        if (c0 == 0 && c1 == 0) {
            continue;
        }

        int person;
        if (c0 == 0) {
            person = dequeue1();
            last_dir = 1;
        } else if (c1 == 0) {
            person = dequeue0();
            last_dir = 0;
        } else if (last_dir == -1 || last_dir == 1) {
            person = dequeue1();
            last_dir = 1;
        } else {
            person = dequeue0();
            last_dir = 0;
        }

        ans[person] = t;
        served++;
        t++;
    }

    for (int j = 0; j < n; j++) {
        if (j > 0) printf(" ");
        printf("%d", ans[j]);
    }
    printf("\n");

    return 0;
}
