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
        if (heap[parent] >= heap[idx]) {
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
        int largest = idx;

        if (left < heap_size && heap[left] > heap[largest]) {
            largest = left;
        }
        if (right < heap_size && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest == idx) {
            break;
        }

        swap(&heap[idx], &heap[largest]);
        idx = largest;
    }
}

void insert_heap(int value) {
    heap[heap_size] = value;
    heap_size++;
    heapify_up(heap_size - 1);
}

int delete_max() {
    if (heap_size == 0) {
        return -1;
    }

    int max_value = heap[0];
    heap[0] = heap[heap_size - 1];
    heap_size--;
    heapify_down(0);
    return max_value;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int freq[26] = {0};
    for (int i = 0; i < n; i++) {
        char ch;
        scanf(" %c", &ch);
        freq[ch - 'A']++;
    }

    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            insert_heap(freq[i]);
        }
    }

    int total_time = 0;
    while (heap_size > 0) {
        int used = 0;
        int temp[26];
        int temp_size = 0;

        for (int slot = 0; slot <= k; slot++) {
            if (heap_size == 0) {
                break;
            }

            int count = delete_max();
            count--;
            used++;

            if (count > 0) {
                temp[temp_size++] = count;
            }
        }

        for (int i = 0; i < temp_size; i++) {
            insert_heap(temp[i]);
        }

        if (heap_size == 0) {
            total_time += used;
        } else {
            total_time += k + 1;
        }
    }

    printf("%d\n", total_time);
    return 0;
}
