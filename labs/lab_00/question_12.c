#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) { return a > b ? a : b; }

int solve(int left, int right, char s[], int k) {
    if (right - left + 1 < k) {
        return 0;
    }

    int freq[26] = {0};
    for (int i = left; i <= right; i++) {
        freq[s[i] - 'a']++;
    }

    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0 && freq[i] < k) {
            char ch = 'a' + i;
            int max_len = 0;
            int start = left;

            for (int j = left; j <= right; j++) {
                if (s[j] == ch) {
                    max_len = max(max_len, solve(start, j - 1, s, k));
                    start = j + 1;
                }
            }
            max_len = max(max_len, solve(start, right, s, k));
            return max_len;
        }
    }

    return right - left + 1;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    char s[n + 1];
    scanf("%s", s);

    printf("%d\n", solve(0, n - 1, s, k));

    return 0;
}
