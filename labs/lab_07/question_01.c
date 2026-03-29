#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000

int s1[MAX], s2[MAX];
int t1 = -1, t2 = -1;

void push(int s[], int* t, int x) { s[++(*t)] = x; }

int pop(int s[], int* t) { return s[(*t)--]; }

int peek(int s[], int t) { return s[t]; }

int size(int t) { return t + 1; }

void shift_if_needed() {
    if (size(t2) != 0) return;
    while (size(t1) != 0) {
        push(s2, &t2, pop(s1, &t1));
    }
}

void enqueue(int x) { push(s1, &t1, x); }

int dequeue() {
    shift_if_needed();
    if (size(t2) == 0) return -1;
    return pop(s2, &t2);
}

int front() {
    shift_if_needed();
    if (size(t2) == 0) return -1;
    return peek(s2, t2);
}

int queue_size() { return size(t1) + size(t2); }

int main() {
    int t;

    if (scanf("%d", &t) != 1) {
        return 0;
    }

    for (int i = 0; i < t; i++) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int x;
            scanf("%d", &x);
            enqueue(x);
        } else if (op == 2) {
            printf("%d\n", dequeue());
        } else if (op == 3) {
            printf("%d\n", front());
        }
    }

    return 0;
}
