#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

char stack[MAX];
int top = -1;

void push(char x) { stack[++top] = x; }

char pop() { return stack[top--]; }

char peek() { return stack[top]; }

int size() { return top + 1; }

int main() {
    int n;
    scanf("%d", &n);
    char encoded[n + 1];
    scanf("%s", encoded);

    for (int i = 0; encoded[i] != '\0'; i++) {
        if (encoded[i] != ']') {
            push(encoded[i]);
        } else {
            char part[MAX];
            int part_len = 0;

            while (top >= 0 && peek() != '[') {
                part[part_len++] = pop();
            }

            pop();

            int repeat = 0;
            int place = 1;
            while (top >= 0 && isdigit((unsigned char)peek())) {
                repeat += (pop() - '0') * place;
                place *= 10;
            }

            for (int r = 0; r < repeat; r++) {
                for (int j = part_len - 1; j >= 0; j--) {
                    push(part[j]);
                }
            }
        }
    }

    push('\0');
    printf("%s", stack);

    return 0;
}
