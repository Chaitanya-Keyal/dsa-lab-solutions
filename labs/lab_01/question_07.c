#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char str[1000];
    fgets(str, sizeof(str), stdin);
    char compressed[2000];
    int count = 0, index = 0;
    for (int i = 0; str[i] != '\0' && str[i] != '\n'; i++) {
        count = 1;
        while (str[i] == str[i + 1]) {
            count++;
            i++;
        }
        compressed[index++] = str[i];
        index += sprintf(&compressed[index], "%d", count);
    }
    compressed[index] = '\0';
    if (index > strlen(str) - 1) {
        printf("%s", str);
    } else {
        printf("%s\n", compressed);
    }
}
