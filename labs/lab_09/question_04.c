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

    int queue[n];
    int front = 0;
    int rear = 0;
    queue[rear++] = root;

    int output[n];
    int output_count = 0;
    int left_to_right = 1;

    while (front < rear) {
        int level_size = rear - front;

        int level_values[level_size];

        for (int i = 0; i < level_size; i++) {
            int idx = queue[front++];
            level_values[i] = nodes[idx].value;

            if (nodes[idx].left != -1) {
                queue[rear++] = nodes[idx].left;
            }
            if (nodes[idx].right != -1) {
                queue[rear++] = nodes[idx].right;
            }
        }

        if (left_to_right) {
            for (int i = 0; i < level_size; i++) {
                output[output_count++] = level_values[i];
            }
        } else {
            for (int i = level_size - 1; i >= 0; i--) {
                output[output_count++] = level_values[i];
            }
        }

        left_to_right = !left_to_right;
    }

    for (int i = 0; i < output_count; i++) {
        printf("%d ", output[i]);
    }
    printf("\n");

    return 0;
}
