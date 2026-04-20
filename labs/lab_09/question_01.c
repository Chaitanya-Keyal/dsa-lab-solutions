#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    int left;
    int right;
} Node;

static int create_node(Node nodes[], int* node_count, int value) {
    int index = *node_count;
    nodes[index].value = value;
    nodes[index].left = -1;
    nodes[index].right = -1;
    (*node_count)++;
    return index;
}

static int insert_bst(Node nodes[], int* node_count, int root, int value) {
    if (root == -1) {
        return create_node(nodes, node_count, value);
    }

    int current = root;
    while (1) {
        if (value < nodes[current].value) {
            if (nodes[current].left == -1) {
                nodes[current].left = create_node(nodes, node_count, value);
                break;
            }
            current = nodes[current].left;
        } else {
            if (nodes[current].right == -1) {
                nodes[current].right = create_node(nodes, node_count, value);
                break;
            }
            current = nodes[current].right;
        }
    }

    return root;
}

static int find_lca_bst(Node nodes[], int root, int u, int v) {
    int current = root;
    while (current != -1) {
        if (u < nodes[current].value && v < nodes[current].value) {
            current = nodes[current].left;
        } else if (u > nodes[current].value && v > nodes[current].value) {
            current = nodes[current].right;
        } else {
            return nodes[current].value;
        }
    }
    return -1;
}

int main() {
    int n;
    scanf("%d", &n);

    Node nodes[n];
    int node_count = 0;
    int root = -1;

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        root = insert_bst(nodes, &node_count, root, x);
    }

    int u, v;
    scanf("%d %d", &u, &v);

    printf("%d\n", find_lca_bst(nodes, root, u, v));
    return 0;
}
