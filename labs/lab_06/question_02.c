#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
int stack[MAX];
int top = -1;

void push(int x) { stack[++top] = x; }

int pop() { return stack[top--]; }

int getTop() { return stack[top]; }

int size() { return top + 1; }

int main() {
    int n;
    scanf("%d", &n);
    int temps[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &temps[i]);
    }
    int wait[n];
    for (int i = n - 1; i >= 0; i--) {
        while (size() > 0 && temps[getTop()] <= temps[i]) {
            pop();
        }
        wait[i] = size() == 0 ? 0 : getTop() - i;
        push(i);
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", wait[i]);
    }
    printf("\n");

    return 0;
}
