#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
int stack[MAX];
int top = -1;

void push(int x) { stack[++top] = x; }

int pop() { return stack[top--]; }

int peek() { return stack[top]; }

int size() { return top + 1; }

int getMin() {
    if (size() == 0) return -1;  // Indicating stack is empty
    int min = stack[0];
    for (int i = 1; i <= top; i++) {
        if (stack[i] < min) {
            min = stack[i];
        }
    }
    return min;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int x;
            scanf("%d", &x);
            push(x);
        } else if (op == 2) {
            if (size() == 0) {
                printf("Stack Empty\n");
            } else {
                printf("Popped: %d\n", pop());
            }
        } else if (op == 3) {
            int min = getMin();
            if (min == -1) {
                printf("Stack Empty\n");
            } else {
                printf("Minimum: %d\n", min);
            }
        } else if (op == 4) {
            if (size() == 0) {
                printf("Stack Empty\n");
            } else {
                printf("Top: %d\n", peek());
            }
        }
    }

    return 0;
}
