#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
void appendNode(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head;  
        return;
    }

    struct Node* temp = *head;
    while (temp->next != *head) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = *head;
}
void displayList(struct Node* head) {
    if (head == NULL) return;
    
    struct Node* temp = head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}
void splitCircularList(struct Node* head) {
    if (head == NULL || head->next == head) {
        printf("List is too small to split.\n");
        return;
    }
    struct Node *slow = head, *fast = head;
    while (fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }
    struct Node* firstHalf = head;
    struct Node* secondHalf = slow->next;
    slow->next = head; 
    struct Node* temp = secondHalf;
    while (temp->next != head) {
        temp = temp->next;
    }
    temp->next = secondHalf; 

    printf("First half: ");
    displayList(firstHalf);

    printf("Second half: ");
    displayList(secondHalf);
}

int main() {
    struct Node* head = NULL;
    int value;
    printf("Enter elements for the circular linked list (enter -1 to stop):\n");
    while (1) {
        printf("Enter value: ");
        scanf("%d", &value);
        if (value == -1) break;
        appendNode(&head, value);
    }
    printf("Original Circular Linked List: ");
    displayList(head);
    splitCircularList(head);

    return 0;
}
