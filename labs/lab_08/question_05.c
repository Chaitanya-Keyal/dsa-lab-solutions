#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000
#define MAXN 1000

typedef struct {
    int value;
    int row;
    int col;
} Node;

int matrix[MAXN][MAXN];
Node heap[MAX];
int heap_size = 0;

void swap(Node* a, Node* b) {
    Node t = *a;
    *a = *b;
    *b = t;
}

void heapify_up(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap[parent].value <= heap[idx].value) {
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

        if (left < heap_size && heap[left].value < heap[smallest].value) {
            smallest = left;
        }
        if (right < heap_size && heap[right].value < heap[smallest].value) {
            smallest = right;
        }

        if (smallest == idx) {
            break;
        }

        swap(&heap[idx], &heap[smallest]);
        idx = smallest;
    }
}

void insert_heap(int value, int row, int col) {
    heap[heap_size].value = value;
    heap[heap_size].row = row;
    heap[heap_size].col = col;
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
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int k;
    scanf("%d", &k);

    for (int i = 0; i < n; i++) {
        insert_heap(matrix[i][0], i, 0);
    }

    int answer = -1;
    for (int cnt = 0; cnt < k && heap_size > 0; cnt++) {
        Node cur = delete_min();
        answer = cur.value;

        if (cur.col + 1 < n) {
            int next_col = cur.col + 1;
            insert_heap(matrix[cur.row][next_col], cur.row, next_col);
        }
    }

    printf("%d\n", answer);
    return 0;
}
