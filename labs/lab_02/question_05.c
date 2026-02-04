#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);
    struct Node {
        int data;
        struct Node* next;
    };
    struct Node* head = NULL;
    struct Node* tail = NULL;
    for (int i = 0; i < N; i++) {
        int value;
        scanf("%d", &value);
        struct Node* newNode = malloc(sizeof(struct Node));
        newNode->data = value;
        newNode->next = NULL;
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    struct Node* dummy = malloc(sizeof(struct Node));
    dummy->next = head;
    struct Node* prev = dummy;
    struct Node* curr = head;

    while (curr != NULL && curr->next != NULL) {
        struct Node* next = curr->next;
        struct Node* nextPair = next->next;

        // Swap
        prev->next = next;
        next->next = curr;
        curr->next = nextPair;

        // Move forward
        prev = curr;
        curr = nextPair;
    }
    head = dummy->next;
    free(dummy);

    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    return 0;
}
