#include <stdio.h>
#include <stdlib.h>

int solve(int pref[], int temp[], int left, int right, int lower, int upper) {
    if (right - left <= 1) {
        return 0;
    }

    int mid = left + (right - left) / 2;
    int count =
        solve(pref, temp, left, mid, lower, upper) + solve(pref, temp, mid, right, lower, upper);

    int low = mid;
    int high = mid;
    for (int i = left; i < mid; i++) {
        while (low < right && pref[low] - pref[i] < lower) {
            low++;
        }
        while (high < right && pref[high] - pref[i] <= upper) {
            high++;
        }
        count += (high - low);
    }

    int i = left;
    int j = mid;
    int k = left;
    while (i < mid && j < right) {
        if (pref[i] <= pref[j]) {
            temp[k++] = pref[i++];
        } else {
            temp[k++] = pref[j++];
        }
    }
    while (i < mid) {
        temp[k++] = pref[i++];
    }
    while (j < right) {
        temp[k++] = pref[j++];
    }
    for (i = left; i < right; i++) {
        pref[i] = temp[i];
    }

    return count;
}

int main() {
    int n, lower, upper;
    scanf("%d %d %d", &n, &lower, &upper);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int pref[n + 1];
    int temp[n + 1];
    pref[0] = 0;
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + arr[i];
    }

    printf("%d\n", solve(pref, temp, 0, n + 1, lower, upper));
    return 0;
}
