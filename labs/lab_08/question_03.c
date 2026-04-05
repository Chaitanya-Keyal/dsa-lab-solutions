#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000

int min_heap[MAX], min_size = 0;
int max_heap[MAX], max_size = 0;

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void min_heapify_up(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (min_heap[parent] <= min_heap[idx]) {
            break;
        }
        swap(&min_heap[parent], &min_heap[idx]);
        idx = parent;
    }
}

void min_heapify_down(int idx) {
    while (1) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;

        if (left < min_size && min_heap[left] < min_heap[smallest]) {
            smallest = left;
        }
        if (right < min_size && min_heap[right] < min_heap[smallest]) {
            smallest = right;
        }

        if (smallest == idx) {
            break;
        }

        swap(&min_heap[idx], &min_heap[smallest]);
        idx = smallest;
    }
}

void insert_min(int value) {
    min_heap[min_size] = value;
    min_size++;
    min_heapify_up(min_size - 1);
}

int delete_min() {
    if (min_size == 0) {
        return -1;
    }

    int min_value = min_heap[0];
    min_heap[0] = min_heap[min_size - 1];
    min_size--;
    min_heapify_down(0);
    return min_value;
}

void max_heapify_up(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (max_heap[parent] >= max_heap[idx]) {
            break;
        }
        swap(&max_heap[parent], &max_heap[idx]);
        idx = parent;
    }
}

void max_heapify_down(int idx) {
    while (1) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int largest = idx;

        if (left < max_size && max_heap[left] > max_heap[largest]) {
            largest = left;
        }
        if (right < max_size && max_heap[right] > max_heap[largest]) {
            largest = right;
        }

        if (largest == idx) {
            break;
        }

        swap(&max_heap[idx], &max_heap[largest]);
        idx = largest;
    }
}

void insert_max(int value) {
    max_heap[max_size] = value;
    max_size++;
    max_heapify_up(max_size - 1);
}

int delete_max() {
    if (max_size == 0) {
        return -1;
    }

    int max_value = max_heap[0];
    max_heap[0] = max_heap[max_size - 1];
    max_size--;
    max_heapify_down(0);
    return max_value;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);

        if (max_size == 0 || x <= max_heap[0]) {
            insert_max(x);
        } else {
            insert_min(x);
        }

        if (max_size > min_size + 1) {
            insert_min(delete_max());
        } else if (min_size > max_size) {
            insert_max(delete_min());
        }

        if (max_size == min_size) {
            double median = ((double)max_heap[0] + (double)min_heap[0]) / 2.0;
            printf("%.1f ", median);
        } else {
            printf("%.1f ", (double)max_heap[0]);
        }
    }

    printf("\n");
    return 0;
}
