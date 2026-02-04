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
    // Separate even and odd lists
    struct Node* evenHead = NULL;
    struct Node* evenTail = NULL;
    struct Node* oddHead = NULL;
    struct Node* oddTail = NULL;
    struct Node* current = head;
    while (current != NULL) {
        if (current->data % 2 == 0) {
            if (evenHead == NULL) {
                evenHead = current;
                evenTail = current;
            } else {
                evenTail->next = current;
                evenTail = current;
            }
        } else {
            if (oddHead == NULL) {
                oddHead = current;
                oddTail = current;
            } else {
                oddTail->next = current;
                oddTail = current;
            }
        }
        current = current->next;
    }
    // Combine even and odd lists
    if (evenTail != NULL) {
        evenTail->next = oddHead;
    }
    if (oddTail != NULL) {
        oddTail->next = NULL;
    }
    // Print modified list
    struct Node* modifiedHead = (evenHead != NULL) ? evenHead : oddHead;
    while (modifiedHead != NULL) {
        printf("%d ", modifiedHead->data);
        modifiedHead = modifiedHead->next;
    }
    return 0;
}
