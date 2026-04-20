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

static int count_in_range(Node nodes[], int root, int l, int r) {
    if (root == -1) {
        return 0;
    }

    int value = nodes[root].value;

    if (value < l) {
        return count_in_range(nodes, nodes[root].right, l, r);
    }

    if (value > r) {
        return count_in_range(nodes, nodes[root].left, l, r);
    }

    return 1 + count_in_range(nodes, nodes[root].left, l, r) +
           count_in_range(nodes, nodes[root].right, l, r);
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

    int l, r;
    scanf("%d %d", &l, &r);

    printf("%d\n", count_in_range(nodes, root, l, r));

    return 0;
}
