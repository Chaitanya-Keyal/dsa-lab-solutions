#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000
#define MAXN 1000

typedef struct {
    int h;
    int r;
    int c;
} Node;

int elevation[MAXN][MAXN];
char visited[MAXN][MAXN];
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
        if (heap[parent].h <= heap[idx].h) {
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

        if (left < heap_size && heap[left].h < heap[smallest].h) {
            smallest = left;
        }
        if (right < heap_size && heap[right].h < heap[smallest].h) {
            smallest = right;
        }

        if (smallest == idx) {
            break;
        }

        swap(&heap[idx], &heap[smallest]);
        idx = smallest;
    }
}

void insert_heap(int h, int r, int c) {
    heap[heap_size].h = h;
    heap[heap_size].r = r;
    heap[heap_size].c = c;
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

void push_boundary_cell(int r, int c) {
    if (visited[r][c]) {
        return;
    }
    visited[r][c] = 1;
    insert_heap(elevation[r][c], r, c);
}

int main() {
    int r, c;
    scanf("%d %d", &r, &c);

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &elevation[i][j]);
        }
    }

    if (r <= 2 || c <= 2) {
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < r; i++) {
        push_boundary_cell(i, 0);
        push_boundary_cell(i, c - 1);
    }
    for (int j = 0; j < c; j++) {
        push_boundary_cell(0, j);
        push_boundary_cell(r - 1, j);
    }

    int water = 0;
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    while (heap_size > 0) {
        Node cur = delete_min();

        for (int d = 0; d < 4; d++) {
            int nr = cur.r + dr[d];
            int nc = cur.c + dc[d];

            if (nr < 0 || nr >= r || nc < 0 || nc >= c) {
                continue;
            }

            if (visited[nr][nc]) {
                continue;
            }
            visited[nr][nc] = 1;

            int nh = elevation[nr][nc];
            if (nh < cur.h) {
                water += cur.h - nh;
                insert_heap(cur.h, nr, nc);
            } else {
                insert_heap(nh, nr, nc);
            }
        }
    }

    printf("%d\n", water);
    return 0;
}
