#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int max_int(int a, int b) { return (a > b) ? a : b; }
static int min_int(int a, int b) { return (a < b) ? a : b; }

int main() {
    int n, m;
    scanf("%d", &n);
    int nums1[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums1[i]);
    }
    scanf("%d", &m);
    int nums2[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &nums2[i]);
    }

    int* small_arr = (n < m) ? nums1 : nums2;
    int* large_arr = (n < m) ? nums2 : nums1;
    int small_size = (n < m) ? n : m;
    int large_size = (n < m) ? m : n;
    int left_size = (small_size + large_size + 1) / 2;

    int l = 0, r = small_size;
    while (l <= r) {
        int i = (l + r) / 2;
        int j = left_size - i;

        int small_left = (i == 0) ? INT_MIN : small_arr[i - 1];
        int small_right = (i == small_size) ? INT_MAX : small_arr[i];

        int large_left = (j == 0) ? INT_MIN : large_arr[j - 1];
        int large_right = (j == large_size) ? INT_MAX : large_arr[j];

        if (small_left <= large_right && large_left <= small_right) {
            if ((small_size + large_size) % 2 == 0) {
                int left_max = max_int(small_left, large_left);
                int right_min = min_int(small_right, large_right);
                double median = (double)(left_max + right_min) / 2;
                printf("%.2f\n", median);
            } else {
                int median = max_int(small_left, large_left);
                printf("%.2f\n", (double)median);
            }
            break;
        } else if (small_left > large_right) {
            r = i - 1;
        } else {
            l = i + 1;
        }
    }
    return 0;
}
