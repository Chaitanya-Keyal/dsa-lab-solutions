#include <stdio.h>
#include <stdlib.h>

#define MAX 1000005

int q[MAX], st[MAX];
int f = 0, r = -1, cnt = 0;
int top = -1;

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

void push(int x) { st[++top] = x; }

int pop() { return st[top--]; }

int stack_size() { return top + 1; }

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        enqueue(x);
    }

    for (int i = 0; i < k; i++) {
        push(dequeue());
    }

    while (stack_size() > 0) {
        enqueue(pop());
    }

    for (int i = 0; i < n - k; i++) {
        enqueue(dequeue());
    }

    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", dequeue());
    }
    printf("\n");

    return 0;
}
