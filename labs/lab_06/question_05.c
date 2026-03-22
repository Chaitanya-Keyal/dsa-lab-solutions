#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
float stack[MAX];
int top = -1;

void push(float x) { stack[++top] = x; }

float pop() { return stack[top--]; }

float peek() { return stack[top]; }

int size() { return top + 1; }

int main() {
    char expression[MAX];
    scanf("%s", expression);
    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];
        if (ch >= '0' && ch <= '9') {
            push(ch - '0');
        } else {
            if (size() < 2) {
                printf("Invalid Expression\n");
                return 0;
            }
            float right = pop();
            float left = pop();
            float result;
            switch (ch) {
                case '+':
                    result = left + right;
                    break;
                case '-':
                    result = left - right;
                    break;
                case '*':
                    result = left * right;
                    break;
                case '/':
                    if (right == 0) {
                        printf("Invalid Expression\n");
                        return 0;
                    }
                    result = left / right;
                    break;
                default:
                    printf("Invalid Expression\n");
                    return 0;
            }
            push(result);
        }
    }
    if (size() != 1) {
        printf("Invalid Expression\n");
        return 0;
    }
    printf("%.2f\n", peek());

    return 0;
}
