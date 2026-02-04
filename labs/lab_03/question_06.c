#include <stdio.h>
#include <stdlib.h>

int f(int x) { return 2 * (x * x * x) - (x * x) + 5 * x; }

int main() {
    int y;
    scanf("%d", &y);

    int l = 0, r = 80;
    int ans = 0;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (f(mid) <= y) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    printf("%d\n", ans);

    return 0;
}
