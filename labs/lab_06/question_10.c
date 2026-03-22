#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* right;
    struct Node* down;
} Node;

static Node* create_node(int vertex) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->vertex = vertex;
    node->right = NULL;
    node->down = NULL;
    return node;
}

int main() {
    int V;
    scanf("%d", &V);

    Node* head = NULL;
    Node* prev_row = NULL;

    for (int i = 0; i < V; i++) {
        Node* row = create_node(i);
        if (head == NULL) {
            head = row;
        } else {
            prev_row->down = row;
        }
        prev_row = row;

        Node* tail = row;
        for (int j = 0; j < V; j++) {
            int value;
            scanf("%d", &value);
            if (value == 1) {
                Node* neighbor = create_node(j);
                tail->right = neighbor;
                tail = neighbor;
            }
        }
    }

    for (Node* row = head; row != NULL; row = row->down) {
        printf("%d", row->vertex);
        for (Node* cur = row->right; cur != NULL; cur = cur->right) {
            printf(" -> %d", cur->vertex);
        }
        printf("\n");

        if (row->down != NULL) {
            printf("|\n");
        }
    }

    return 0;
}
