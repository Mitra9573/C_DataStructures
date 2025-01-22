#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int priority;
    struct Node* next;
};

struct Node* createNode(int data, int priority) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

struct Node* enqueue(struct Node* head, int data, int priority) {
    struct Node* newNode = createNode(data, priority);

    
    if (head == NULL || priority < head->priority) {
        newNode->next = head;
        head = newNode;
        return head;
    }

    struct Node* temp = head;
    while (temp->next != NULL && temp->next->priority <= priority) {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;

    return head;
}


struct Node* dequeue(struct Node* head) {
    if (head == NULL) {
        printf("Queue is empty!\n");
        return NULL;
    }

    struct Node* temp = head;
    head = head->next;
    printf("Dequeued: %d with priority %d\n", temp->data, temp->priority);
    free(temp);

    return head;
}

void displayQueue(struct Node* head) {
    if (head == NULL) {
        printf("Queue is empty!\n");
        return;
    }

    struct Node* temp = head;
    printf("Priority Queue: \n");
    while (temp != NULL) {
        printf("Data: %d, Priority: %d\n", temp->data, temp->priority);
        temp = temp->next;
    }
}

int main() {
    struct Node* priorityQueue = NULL;
    int choice, data, priority;

    do {
        printf("\nPriority Queue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                printf("Enter priority: ");
                scanf("%d", &priority);
                priorityQueue = enqueue(priorityQueue, data, priority);
                break;

            case 2:
                priorityQueue = dequeue(priorityQueue);
                break;

            case 3:
                displayQueue(priorityQueue);
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
