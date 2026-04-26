#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    int freq;
    struct Node* next;
};

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    struct Node* table[m];
    for (int i = 0; i < m; i++) table[i] = NULL;

    for (int i = 0; i < n; i++) {
        int k;
        scanf("%d", &k);

        int h = k % m;
        struct Node* curr = table[h];
        struct Node* tail = NULL;

        while (curr != NULL) {
            if (curr->key == k) {
                curr->freq++;
                break;
            }
            tail = curr;
            curr = curr->next;
        }

        if (curr == NULL) {
            struct Node* node = malloc(sizeof(struct Node));
            node->key = k;
            node->freq = 1;
            node->next = NULL;
            if (tail == NULL)
                table[h] = node;
            else
                tail->next = node;
        }
    }

    for (int i = 0; i < m; i++) {
        printf("Index %d: ", i);
        if (table[i] == NULL) {
            printf("Empty\n");
        } else {
            struct Node* curr = table[i];
            while (curr != NULL) {
                printf("[%d:%d]", curr->key, curr->freq);
                if (curr->next != NULL) printf(" -> ");
                curr = curr->next;
            }
            printf("\n");
        }
    }

    int max_freq = 0, min_key = -1;
    for (int i = 0; i < m; i++) {
        struct Node* curr = table[i];
        while (curr != NULL) {
            if (curr->freq > max_freq || (curr->freq == max_freq && curr->key < min_key)) {
                max_freq = curr->freq;
                min_key = curr->key;
            }
            curr = curr->next;
        }
    }

    printf("%d %d\n", min_key, max_freq);

    return 0;
}
