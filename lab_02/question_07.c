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
    int X;
    scanf("%d", &X);

    struct Node* current = head;
    struct Node* prev = NULL;
    struct Node* newTail = tail;

    while (current != NULL && current != tail->next) {
        if (current->data == X) {
            struct Node* temp = current;
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            current = current->next;
            newTail->next = temp;
            newTail = temp;
            newTail->next = NULL;
        } else {
            prev = current;
            current = current->next;
        }
    }

    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    return 0;
}
