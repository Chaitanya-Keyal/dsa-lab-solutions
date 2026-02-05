#include <stdio.h>
#include <stdlib.h>

struct Element {
    int value;
    int index;
};

int compare(struct Element* a, struct Element* b) {
    if (a->value != b->value) {
        return a->value - b->value;
    } else {
        return a->index - b->index;
    }
}

void merge(struct Element arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    struct Element L[n1];
    struct Element R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compare(&L[i], &R[j]) <= 0) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];

    while (j < n2) arr[k++] = R[j++];
}

void merge_sort(struct Element arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    struct Element arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i].value);
        arr[i].index = i;
    }
    merge_sort(arr, 0, n - 1);
    for (int i = 1; i < n; i++) {
        if (arr[i].value == arr[i - 1].value && abs(arr[i].index - arr[i - 1].index) > k) {
            printf("%d %d\n", arr[i - 1].index, arr[i].index);
            return 0;
        }
    }
    printf("-1\n");

    return 0;
}
