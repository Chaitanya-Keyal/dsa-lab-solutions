#include <stdio.h>

typedef struct Node {
    int value;
    int left;
    int right;
} Node;

static int create_node(Node nodes[], int* node_count, int value, int value_to_index[]) {
    int index = *node_count;
    nodes[index].value = value;
    nodes[index].left = -1;
    nodes[index].right = -1;
    value_to_index[value] = index;
    (*node_count)++;
    return index;
}

static int insert_bst(Node nodes[], int* node_count, int root, int value, int value_to_index[]) {
    if (root == -1) {
        return create_node(nodes, node_count, value, value_to_index);
    }

    int current = root;
    while (1) {
        if (value < nodes[current].value) {
            if (nodes[current].left == -1) {
                nodes[current].left = create_node(nodes, node_count, value, value_to_index);
                break;
            }
            current = nodes[current].left;
        } else {
            if (nodes[current].right == -1) {
                nodes[current].right = create_node(nodes, node_count, value, value_to_index);
                break;
            }
            current = nodes[current].right;
        }
    }

    return root;
}

static int fill_subtree_sizes(Node nodes[], int root, int subtree_size[]) {
    if (root == -1) {
        return 0;
    }

    int left_size = fill_subtree_sizes(nodes, nodes[root].left, subtree_size);
    int right_size = fill_subtree_sizes(nodes, nodes[root].right, subtree_size);
    subtree_size[root] = 1 + left_size + right_size;
    return subtree_size[root];
}

int main() {
    int n;
    scanf("%d", &n);

    Node nodes[n];
    int subtree_size[n];
    int insertion_order[n];
    int value_to_index[n + 1];

    int node_count = 0;
    int root = -1;

    for (int i = 0; i < n; i++) {
        scanf("%d", &insertion_order[i]);
        root = insert_bst(nodes, &node_count, root, insertion_order[i], value_to_index);
    }

    fill_subtree_sizes(nodes, root, subtree_size);

    for (int i = 0; i < n; i++) {
        int idx = value_to_index[insertion_order[i]];
        printf("%d ", subtree_size[idx] - 1);
    }
    printf("\n");

    return 0;
}
