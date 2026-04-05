#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000

typedef struct {
    int d;
    int r;
} Mission;

Mission missions[MAX];

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

void bubble_sort(int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (missions[j].d > missions[j + 1].d) {
                Mission t = missions[j];
                missions[j] = missions[j + 1];
                missions[j + 1] = t;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &missions[i].d, &missions[i].r);
    }

    bubble_sort(n);

    long long total_reward = 0;
    for (int i = 0; i < n; i++) {
        int deadline = missions[i].d;
        int reward = missions[i].r;

        if (heap_size < deadline) {
            insert_heap(reward);
            total_reward += reward;
        } else if (heap_size > 0 && heap[0] < reward) {
            total_reward -= delete_min();
            insert_heap(reward);
            total_reward += reward;
        }
    }

    printf("%lld\n", total_reward);
    return 0;
}
