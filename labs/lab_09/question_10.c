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

static int find_node(Node nodes[], int root, int x) {
    int current = root;
    while (current != -1) {
        if (nodes[current].value == x) {
            return current;
        }
        if (x < nodes[current].value) {
            current = nodes[current].left;
        } else {
            current = nodes[current].right;
        }
    }
    return -1;
}

static int subtree_sum(Node nodes[], int root) {
    if (root == -1) {
        return 0;
    }
    return nodes[root].value + subtree_sum(nodes, nodes[root].left) +
           subtree_sum(nodes, nodes[root].right);
}

int main() {
    int n;
    scanf("%d", &n);

    Node nodes[n];
    int node_count = 0;
    int root = -1;

    for (int i = 0; i < n; i++) {
        int v;
        scanf("%d", &v);
        root = insert_bst(nodes, &node_count, root, v);
    }

    int x;
    scanf("%d", &x);

    int node_idx = find_node(nodes, root, x);
    printf("%d\n", subtree_sum(nodes, node_idx));

    return 0;
}
