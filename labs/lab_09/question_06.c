#include <stdio.h>

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

static int find_lca(Node nodes[], int root, int a, int b) {
    int current = root;

    while (current != -1) {
        int value = nodes[current].value;

        if (a < value && b < value) {
            current = nodes[current].left;
        } else if (a > value && b > value) {
            current = nodes[current].right;
        } else {
            return current;
        }
    }

    return -1;
}

static int sum_on_path(Node nodes[], int start, int target) {
    int current = start;
    int sum = 0;

    while (current != -1) {
        int value = nodes[current].value;
        sum += value;

        if (value == target) {
            return sum;
        }

        if (target < value) {
            current = nodes[current].left;
        } else {
            current = nodes[current].right;
        }
    }

    return 0;
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

    int a, b;
    scanf("%d %d", &a, &b);

    int lca = find_lca(nodes, root, a, b);
    int sum_lca_to_a = sum_on_path(nodes, lca, a);
    int sum_lca_to_b = sum_on_path(nodes, lca, b);

    int answer = sum_lca_to_a + sum_lca_to_b - nodes[lca].value;
    printf("%d\n", answer);

    return 0;
}
