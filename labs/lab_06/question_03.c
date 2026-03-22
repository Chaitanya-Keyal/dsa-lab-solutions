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
    int heights[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    int maxArea = 0;
    for (int i = 0; i < n; i++) {
        while (size() > 0 && heights[peek()] >= heights[i]) {
            int height = heights[pop()];
            int width = size() == 0 ? i : i - peek() - 1;
            int area = height * width;
            if (area > maxArea) {
                maxArea = area;
            }
        }
        push(i);
    }
    while (size() > 0) {
        int height = heights[pop()];
        int width = size() == 0 ? n : n - peek() - 1;
        int area = height * width;
        if (area > maxArea) {
            maxArea = area;
        }
    }
    printf("%d\n", maxArea);

    return 0;
}
