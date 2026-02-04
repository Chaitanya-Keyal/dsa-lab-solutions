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
    struct Node* current = head;
    while (current != NULL) {
        struct Node* sumNode = malloc(sizeof(struct Node));
        if (current->next == NULL) {
            sumNode->data = current->data;
            sumNode->next = NULL;
            current->next = sumNode;
        } else {
            sumNode->data = current->data + current->next->data;
            sumNode->next = current->next->next;
            current->next->next = sumNode;
        }
        current = sumNode->next;
    }
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    return 0;
}
