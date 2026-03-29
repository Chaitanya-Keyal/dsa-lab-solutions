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
    int n, k;
    int tickets[MAX];
    long long time = 0;

    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf("%d", &tickets[i]);
        enqueue(i);
    }

    while (size() > 0) {
        int person = dequeue();
        tickets[person]--;
        time++;

        if (tickets[person] == 0) {
            if (person == k) {
                printf("%lld\n", time);
                return 0;
            }
        } else {
            enqueue(person);
        }
    }

    return 0;
}
