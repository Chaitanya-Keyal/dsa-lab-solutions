#include <stdio.h>
#include <stdlib.h>

#define MAX 1000005

int q[MAX];
int f = 0, r = -1, cnt = 0;

void enqueue(int x) {
    q[++r] = x;
    cnt++;
}

int dequeue() {
    cnt--;
    return q[f++];
}

int front() { return q[f]; }

int size() { return cnt; }

int main() {
    int n;
    int gas[MAX], dist[MAX];
    long long fuel = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &gas[i]);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &dist[i]);
    }

    for (int i = 0; i < 2 * n; i++) {
        int idx = i % n;
        enqueue(idx);
        fuel += (long long)gas[idx] - dist[idx];

        while (size() > 0 && fuel < 0) {
            int removed = dequeue();
            fuel -= (long long)gas[removed] - dist[removed];
        }

        if (size() == n) {
            printf("%d\n", front());
            return 0;
        }
    }

    printf("-1\n");

    return 0;
}
