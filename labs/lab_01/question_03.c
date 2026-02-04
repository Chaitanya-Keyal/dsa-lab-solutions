#include <stdio.h>
#include <stdlib.h>

int main() {
    char str[1000];
    fgets(str, sizeof(str), stdin);
    int words = 0, vowels = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t') {
            words++;
        }
        char ch = str[i];
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
            ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U') {
            vowels++;
        }
    }
    printf("Words: %d\n", words);
    printf("Vowels: %d\n", vowels);
    printf("Reversed: ");
    int i;
    for (i = 0; str[i] != '\0'; i++);
    for (i = i - 1; i >= 0; i--) {
        if (str[i] == '\n') continue;  // Skip newline at the end
        putchar(str[i]);
    }
    return 0;
}
