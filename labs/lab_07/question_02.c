#include <stdio.h>
#include <stdlib.h>

#define MAX 1000005

char q[MAX];
int f = 0, r = -1, cnt = 0;

void enqueue(char x) {
    q[++r] = x;
    cnt++;
}

char dequeue() {
    cnt--;
    return q[f++];
}

char front() { return q[f]; }

int size() { return cnt; }

int main() {
    char s[MAX];
    int freq[26] = {0};

    scanf("%s", s);

    for (int i = 0; s[i] != '\0'; i++) {
        char ch = s[i];
        enqueue(ch);
        freq[ch - 'a']++;

        while (size() > 0 && freq[front() - 'a'] > 1) {
            dequeue();
        }

        if (i > 0) printf(" ");
        if (size() == 0) {
            printf("-1");
        } else {
            printf("%c", front());
        }
    }
    printf("\n");

    return 0;
}
