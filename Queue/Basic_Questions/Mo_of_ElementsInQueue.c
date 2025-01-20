#include <stdio.h>
#include <stdlib.h>

// Node structure for the queue
struct Node {
    int value;           // Data in the node
    struct Node* next;   // Pointer to the next node
};

// Queue structure
struct Queue {
    struct Node* head;   // Front of the queue
    struct Node* tail;   // Rear of the queue
};

// Function to initialize the queue
void initializeQueue(struct Queue* queue) {
    queue->head = NULL;
    queue->tail = NULL;
}

// Function to check if the queue is empty
int isQueueEmpty(struct Queue* queue) {
    return queue->head == NULL;
}

// Function to enqueue an element into the queue
void enqueue(struct Queue* queue, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed! Cannot enqueue %d.\n", value);
        return;
    }
    newNode->value = value;
    newNode->next = NULL;

    if (isQueueEmpty(queue)) {
        queue->head = newNode;  // Set head if the queue is empty
    } else {
        queue->tail->next = newNode;  // Add the new node to the end
    }
    queue->tail = newNode;  // Update tail to the new node
    printf("Enqueued: %d\n", value);
}

// Function to display the queue
void displayQueue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Queue: ");
    struct Node* nodePointer = queue->head;
    while (nodePointer != NULL) {
        printf("%d ", nodePointer->value);
        nodePointer = nodePointer->next;
    }
    printf("\n");
}

// Function to count the number of elements in the queue
int countElements(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        return 0;
    }

    int count = 0;
    struct Node* nodePointer = queue->head;
    while (nodePointer != NULL) {
        count++;
        nodePointer = nodePointer->next;
    }

    return count;
}

int main() {
    struct Queue queue;
    initializeQueue(&queue);

    int choice, value;

    while (1) {
        printf("\nQueue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Display Queue\n");
        printf("3. Count Elements\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to enqueue: ");
                scanf("%d", &value);
                enqueue(&queue, value);
                break;

            case 2:
                displayQueue(&queue);
                break;

            case 3:
                printf("Number of elements in the queue: %d\n", countElements(&queue));
                break;

            case 4:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
