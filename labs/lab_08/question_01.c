#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000

int heap[MAX];
int heap_size = 0;

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void heapify_up(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap[parent] <= heap[idx]) {
            break;
        }
        swap(&heap[parent], &heap[idx]);
        idx = parent;
    }
}

void heapify_down(int idx) {
    while (1) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;

        if (left < heap_size && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < heap_size && heap[right] < heap[smallest]) {
            smallest = right;
        }

        if (smallest == idx) {
            break;
        }

        swap(&heap[idx], &heap[smallest]);
        idx = smallest;
    }
}

void insert_heap(int value) {
    heap[heap_size] = value;
    heap_size++;
    heapify_up(heap_size - 1);
}

int delete_min() {
    if (heap_size == 0) {
        return -1;
    }

    int min_value = heap[0];
    heap[0] = heap[heap_size - 1];
    heap_size--;
    heapify_down(0);
    return min_value;
}

int main() {
    int k, n;
    scanf("%d %d", &k, &n);

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);

        if (heap_size < k) {
            insert_heap(x);
        } else if (x > heap[0]) {
            delete_min();
            insert_heap(x);
        }

        if (heap_size < k) {
            printf("-1 ");
        } else {
            printf("%d ", heap[0]);
        }
    }

    printf("\n");
    return 0;
}
