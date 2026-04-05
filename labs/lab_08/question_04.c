#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000

typedef struct {
    long long sum;
    int i;
    int j;
} Node;

int a[MAX], b[MAX];
Node heap[MAX];
int heap_size = 0;

int smaller(Node x, Node y) {
    if (x.sum != y.sum) {
        return x.sum < y.sum;
    }
    if (x.j != y.j) {
        return x.j < y.j;
    }
    return x.i < y.i;
}

void swap(Node* x, Node* y) {
    Node t = *x;
    *x = *y;
    *y = t;
}

void heapify_up(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (!smaller(heap[idx], heap[parent])) {
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

        if (left < heap_size && smaller(heap[left], heap[smallest])) {
            smallest = left;
        }
        if (right < heap_size && smaller(heap[right], heap[smallest])) {
            smallest = right;
        }

        if (smallest == idx) {
            break;
        }

        swap(&heap[idx], &heap[smallest]);
        idx = smallest;
    }
}

void insert_heap(long long sum, int i, int j) {
    heap[heap_size].sum = sum;
    heap[heap_size].i = i;
    heap[heap_size].j = j;
    heap_size++;
    heapify_up(heap_size - 1);
}

Node delete_min() {
    Node min_value = heap[0];
    heap[0] = heap[heap_size - 1];
    heap_size--;
    heapify_down(0);
    return min_value;
}

int main() {
    int n1, n2;
    scanf("%d %d", &n1, &n2);

    for (int i = 0; i < n1; i++) {
        scanf("%d", &a[i]);
    }
    for (int j = 0; j < n2; j++) {
        scanf("%d", &b[j]);
    }

    int k;
    scanf("%d", &k);

    for (int i = 0; i < n1; i++) {
        insert_heap((long long)a[i] + b[0], i, 0);
    }

    for (int cnt = 0; cnt < k && heap_size > 0; cnt++) {
        Node cur = delete_min();
        printf("%d %d\n", a[cur.i], b[cur.j]);

        if (cur.j + 1 < n2) {
            insert_heap((long long)a[cur.i] + b[cur.j + 1], cur.i, cur.j + 1);
        }
    }

    return 0;
}
