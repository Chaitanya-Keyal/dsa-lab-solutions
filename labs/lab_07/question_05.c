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

int back() { return q[r]; }

void pop_back() {
    r--;
    cnt--;
}

int size() { return cnt; }

int main() {
    int arr[MAX];
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < n; i++) {
        while (size() > 0 && front() <= i - k) {
            dequeue();
        }

        while (size() > 0 && arr[back()] <= arr[i]) {
            pop_back();
        }

        enqueue(i);

        if (i >= k - 1) {
            if (i > k - 1) printf(" ");
            printf("%d", arr[front()]);
        }
    }
    printf("\n");

    return 0;
}
