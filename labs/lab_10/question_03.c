#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    int value;
    struct Node* next;
};

int main() {
    int m, q;
    scanf("%d %d", &m, &q);

    struct Node* table[m];
    for (int i = 0; i < m; i++) table[i] = NULL;

    for (int i = 0; i < q; i++) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int pid, qty;
            scanf("%d %d", &pid, &qty);

            int h = pid % m;
            struct Node* curr = table[h];
            struct Node* tail = NULL;

            while (curr != NULL) {
                if (curr->key == pid) {
                    curr->value += qty;
                    break;
                }
                tail = curr;
                curr = curr->next;
            }

            if (curr == NULL) {
                struct Node* node = malloc(sizeof(struct Node));
                node->key = pid;
                node->value = qty;
                node->next = NULL;
                if (tail == NULL)
                    table[h] = node;
                else
                    tail->next = node;
            }

        } else {
            for (int j = 0; j < m; j++) {
                printf("Index %d: ", j);
                if (table[j] == NULL) {
                    printf("Empty\n");
                } else {
                    struct Node* curr = table[j];
                    while (curr != NULL) {
                        printf("[%d:%d]", curr->key, curr->value);
                        if (curr->next != NULL) printf(" -> ");
                        curr = curr->next;
                    }
                    printf("\n");
                }
            }
        }
    }

    return 0;
}
