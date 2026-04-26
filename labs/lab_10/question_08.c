#include <stdio.h>
#include <stdlib.h>

long long merge_count(int a[], int tmp[], int left, int right) {
    if (right - left <= 1) return 0;

    int mid = (left + right) / 2;
    long long count = 0;

    count += merge_count(a, tmp, left, mid);
    count += merge_count(a, tmp, mid, right);

    int k = left;
    for (int j = mid; j < right; j++) {
        while (k < mid && a[k] <= 2 * a[j]) k++;
        count += mid - k;
    }

    int i = left, j = mid, idx = left;
    while (i < mid && j < right) tmp[idx++] = a[i] <= a[j] ? a[i++] : a[j++];
    while (i < mid) tmp[idx++] = a[i++];
    while (j < right) tmp[idx++] = a[j++];
    for (int x = left; x < right; x++) a[x] = tmp[x];

    return count;
}

int main() {
    int n;
    scanf("%d", &n);

    int a[n], tmp[n];
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    printf("%lld\n", merge_count(a, tmp, 0, n));

    return 0;
}
