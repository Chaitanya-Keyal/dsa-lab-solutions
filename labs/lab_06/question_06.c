#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
char stack[MAX];
int top = -1;

void push(char x) { stack[++top] = x; }

char pop() { return stack[top--]; }

char peek() { return stack[top]; }

int size() { return top + 1; }

int main() {
    char string[MAX];
    scanf("%s", string);
    int max_length = 0;
    int last_invalid = -1;
    for (int i = 0; string[i] != '\0'; i++) {
        char ch = string[i];
        if (ch == '(') {
            push(i);
        } else {
            if (size() == 0) {
                last_invalid = i;
            } else {
                pop();
                int length = size() == 0 ? i - last_invalid : i - peek();
                if (length > max_length) {
                    max_length = length;
                }
            }
        }
    }
    printf("%d\n", max_length);

    return 0;
}
