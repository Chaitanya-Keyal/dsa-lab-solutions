#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000
#define MAXK 1000
#define MAXM 1000

typedef struct {
    int value;
    int list_id;
    int idx;
} Node;

int lists[MAXK][MAXM];
int list_len[MAXK];
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

void insert_heap(int value, int list_id, int idx) {
    heap[heap_size].value = value;
    heap[heap_size].list_id = list_id;
    heap[heap_size].idx = idx;
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
    int k;
    scanf("%d", &k);

    for (int i = 0; i < k; i++) {
        int m;
        scanf("%d", &m);
        list_len[i] = m;

        for (int j = 0; j < m; j++) {
            scanf("%d", &lists[i][j]);
        }
    }

    int current_max = lists[0][0];
    for (int i = 0; i < k; i++) {
        int v = lists[i][0];
        insert_heap(v, i, 0);
        if (v > current_max) {
            current_max = v;
        }
    }

    int best_l = heap[0].value;
    int best_r = current_max;

    while (heap_size == k) {
        Node cur = delete_min();
        int cur_l = cur.value;

        if (current_max - cur_l < best_r - best_l ||
            (current_max - cur_l == best_r - best_l && cur_l < best_l)) {
            best_l = cur_l;
            best_r = current_max;
        }

        int next_idx = cur.idx + 1;
        if (next_idx >= list_len[cur.list_id]) {
            break;
        }

        int next_val = lists[cur.list_id][next_idx];
        insert_heap(next_val, cur.list_id, next_idx);
        if (next_val > current_max) {
            current_max = next_val;
        }
    }

    printf("%d %d\n", best_l, best_r);
    return 0;
}
