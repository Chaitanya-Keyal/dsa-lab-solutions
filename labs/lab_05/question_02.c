#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int max_len = 2, start = 1;
    int curr_len = 2, curr_diff = arr[1] - arr[0];
    for (int i = 3; i <= n; i++) {
        int diff = arr[i - 1] - arr[i - 2];
        if (diff == curr_diff) {
            curr_len++;
        } else {
            if (curr_len > max_len) {
                max_len = curr_len;
                start = i - curr_len + 1;
            }
            curr_diff = diff;
            curr_len = 2;
        }
    }
    if (curr_len > max_len) {
        max_len = curr_len;
        start = n - curr_len + 1;
    }
    printf("%d %d\n", start, start + max_len - 1);

    return 0;
}
