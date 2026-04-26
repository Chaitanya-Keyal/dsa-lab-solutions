#include <stdio.h>
#include <stdlib.h>

struct Node {
    int id;
    struct Node* next;
};

int main() {
    int m, nA, nB;
    scanf("%d %d %d", &m, &nA, &nB);

    struct Node* table[m];
    for (int i = 0; i < m; i++) table[i] = NULL;

    for (int i = 0; i < nA; i++) {
        int id;
        scanf("%d", &id);

        int h = id % m;
        struct Node* prev = NULL;
        struct Node* curr = table[h];

        while (curr != NULL && curr->id < id) {
            prev = curr;
            curr = curr->next;
        }

        struct Node* node = malloc(sizeof(struct Node));
        node->id = id;
        node->next = curr;

        if (prev == NULL) {
            table[h] = node;
        } else {
            prev->next = node;
        }
    }

    int found = 0;
    int results[nB];
    int count = 0;

    for (int i = 0; i < nB; i++) {
        int id;
        scanf("%d", &id);

        struct Node* curr = table[id % m];
        while (curr != NULL) {
            if (curr->id == id) {
                results[count++] = id;
                found = 1;
                break;
            }
            if (curr->id > id) break;
            curr = curr->next;
        }
    }

    if (!found) {
        printf("Intersection: None\n");
    } else {
        printf("Intersection:");
        for (int i = 0; i < count; i++) printf(" %d", results[i]);
        printf("\n");
    }

    return 0;
}
