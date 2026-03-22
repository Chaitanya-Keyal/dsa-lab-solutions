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
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    long long sum = 0;
    for (int i = 0; i < n; i++) {
        while (size() > 0 && arr[peek()] >= arr[i]) {
            int idx = pop();
            int left = size() > 0 ? peek() : -1;
            sum += (long long)arr[idx] * (idx - left) * (i - idx);
        }
        push(i);
    }
    while (size() > 0) {
        int idx = pop();
        int left = size() > 0 ? peek() : -1;
        sum += (long long)arr[idx] * (idx - left) * (n - idx);
    }
    printf("%lld\n", sum);

    return 0;
}
