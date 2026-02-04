#include <stdio.h>
#include <stdlib.h>

int main() {
    int k;
    scanf("%d", &k);

    int l = 0, r = 1000;
    int res = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (mid * mid <= k) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("%d\n", res);

    return 0;
}
