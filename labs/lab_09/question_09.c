#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    int left;
    int right;
    int color;
    int parent;
} Node;

static int create_node(Node nodes[], int* node_count, int value) {
    int index = *node_count;
    nodes[index].value = value;
    nodes[index].left = -1;
    nodes[index].right = -1;
    nodes[index].color = 0;
    nodes[index].parent = -1;
    (*node_count)++;
    return index;
}

static int rotate_left(Node nodes[], int idx, int* root) {
    int r = nodes[idx].right;
    nodes[idx].right = nodes[r].left;
    if (nodes[r].left != -1) nodes[nodes[r].left].parent = idx;
    nodes[r].parent = nodes[idx].parent;
    if (nodes[idx].parent == -1) {
        *root = r;
    } else if (idx == nodes[nodes[idx].parent].left) {
        nodes[nodes[idx].parent].left = r;
    } else {
        nodes[nodes[idx].parent].right = r;
    }
    nodes[r].left = idx;
    nodes[idx].parent = r;
    return r;
}

static int rotate_right(Node nodes[], int idx, int* root) {
    int l = nodes[idx].left;
    nodes[idx].left = nodes[l].right;
    if (nodes[l].right != -1) nodes[nodes[l].right].parent = idx;
    nodes[l].parent = nodes[idx].parent;
    if (nodes[idx].parent == -1) {
        *root = l;
    } else if (idx == nodes[nodes[idx].parent].right) {
        nodes[nodes[idx].parent].right = l;
    } else {
        nodes[nodes[idx].parent].left = l;
    }
    nodes[l].right = idx;
    nodes[idx].parent = l;
    return l;
}

static void fix_insert(Node nodes[], int idx, int* root) {
    while (idx != -1 && nodes[idx].parent != -1 && nodes[nodes[idx].parent].color == 0) {
        int p = nodes[idx].parent;
        int gp = nodes[p].parent;
        if (gp == -1) break;

        if (p == nodes[gp].left) {
            int u = nodes[gp].right;
            if (u != -1 && nodes[u].color == 0) {
                nodes[p].color = 1;
                nodes[u].color = 1;
                nodes[gp].color = 0;
                idx = gp;
            } else {
                if (idx == nodes[p].right) {
                    idx = p;
                    rotate_left(nodes, idx, root);
                    p = nodes[idx].parent;
                    gp = nodes[p].parent;
                }
                nodes[p].color = 1;
                nodes[gp].color = 0;
                rotate_right(nodes, gp, root);
            }
        } else {
            int u = nodes[gp].left;
            if (u != -1 && nodes[u].color == 0) {
                nodes[p].color = 1;
                nodes[u].color = 1;
                nodes[gp].color = 0;
                idx = gp;
            } else {
                if (idx == nodes[p].left) {
                    idx = p;
                    rotate_right(nodes, idx, root);
                    p = nodes[idx].parent;
                    gp = nodes[p].parent;
                }
                nodes[p].color = 1;
                nodes[gp].color = 0;
                rotate_left(nodes, gp, root);
            }
        }
    }
    nodes[*root].color = 1;
}

static int insert_rbt(Node nodes[], int* node_count, int root, int value, int* root_ptr) {
    if (root == -1) {
        int idx = create_node(nodes, node_count, value);
        *root_ptr = idx;
        nodes[idx].color = 1;
        return idx;
    }

    int current = root;
    int idx = -1;

    while (current != -1) {
        if (value < nodes[current].value) {
            if (nodes[current].left == -1) {
                idx = create_node(nodes, node_count, value);
                nodes[idx].parent = current;
                nodes[current].left = idx;
                break;
            }
            current = nodes[current].left;
        } else {
            if (nodes[current].right == -1) {
                idx = create_node(nodes, node_count, value);
                nodes[idx].parent = current;
                nodes[current].right = idx;
                break;
            }
            current = nodes[current].right;
        }
    }

    if (idx != -1) {
        fix_insert(nodes, idx, root_ptr);
    }

    return *root_ptr;
}

static int get_black_height(Node nodes[], int idx) {
    if (idx == -1) return 0;
    int left_height = get_black_height(nodes, nodes[idx].left);
    return left_height + nodes[idx].color;
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
        root = insert_rbt(nodes, &node_count, root, x, &root);
    }

    printf("%d\n", get_black_height(nodes, root));

    return 0;
}
