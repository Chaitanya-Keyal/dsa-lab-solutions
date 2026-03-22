#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
int stack[MAX];
int top = -1;

void push(int x) { stack[++top] = x; }

int pop() { return stack[top--]; }

int peek() { return stack[top]; }

int size() { return top + 1; }

int main() {
    int n;
    scanf("%d", &n);
    int seq1[n], seq2[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &seq1[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &seq2[i]);
    }
    int operations[2 * n];
    int op_index = 0;
    int to_match = 0;
    for (int i = 0; i < n; i++) {
        push(seq1[i]);
        operations[op_index++] = 1;  // Push
        while (size() > 0 && peek() == seq2[to_match]) {
            pop();
            operations[op_index++] = -1;  // Pop
            to_match++;
        }
    }
    if (to_match != n) {
        printf("Impossible\n");
        return 0;
    }

    for (int i = 0; i < op_index; i++) {
        if (operations[i] == 1) {
            printf("Push\n");
        } else {
            printf("Pop\n");
        }
    }

    return 0;
}
