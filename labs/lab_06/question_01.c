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
    int prices[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &prices[i]);
    }

    int span[n];
    for (int i = 0; i < n; i++) {
        while (size() > 0 && prices[getTop()] <= prices[i]) {
            pop();
        }
        span[i] = size() == 0 ? i + 1 : i - getTop();
        push(i);
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", span[i]);
    }
    printf("\n");

    return 0;
}
