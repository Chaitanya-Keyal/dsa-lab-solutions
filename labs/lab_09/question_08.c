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

static int inorder_successor(Node nodes[], int root, int x) {
    int current = root;
    int successor = -1;

    while (current != -1) {
        int value = nodes[current].value;

        if (x < value) {
            successor = value;
            current = nodes[current].left;
        } else if (x > value) {
            current = nodes[current].right;
        } else {
            break;
        }
    }

    if (current == -1) {
        return -1;
    }

    if (nodes[current].right != -1) {
        int next = nodes[current].right;
        while (nodes[next].left != -1) {
            next = nodes[next].left;
        }
        return nodes[next].value;
    }

    return successor;
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

    printf("%d\n", inorder_successor(nodes, root, x));

    return 0;
}
