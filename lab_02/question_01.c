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
    // Find middle
    struct Node* slow = head;
    struct Node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    // Reverse second half
    struct Node* prev = NULL;
    struct Node* curr = slow;
    while (curr != NULL) {
        struct Node* nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }
    // Compare
    struct Node* firstHalf = head;
    struct Node* secondHalf = prev;
    int isPalindrome = 1;
    while (secondHalf != NULL) {
        if (firstHalf->data != secondHalf->data) {
            isPalindrome = 0;
            break;
        }
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }
    if (isPalindrome) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}
