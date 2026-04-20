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

static int kth_smallest(Node nodes[], int root, int n, int k) {
    int stack[n];
    int top = -1;
    int current = root;
    int visited = 0;

    while (current != -1 || top != -1) {
        while (current != -1) {
            stack[++top] = current;
            current = nodes[current].left;
        }

        current = stack[top--];
        visited++;
        if (visited == k) {
            return nodes[current].value;
        }

        current = nodes[current].right;
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

    int k;
    scanf("%d", &k);

    printf("%d\n", kth_smallest(nodes, root, n, k));

    return 0;
}
