#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node* next;
};

struct Queue {
    struct Node* head;  // Front of the queue
    struct Node* tail;  // Rear of the queue
};

void initializeQueue(struct Queue* queue) {
    queue->head = NULL;
    queue->tail = NULL;
}

int isQueueEmpty(struct Queue* queue) {
    return queue->head == NULL;
}

void enqueue(struct Queue* queue, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed! Cannot enqueue %d.\n", value);
        return;
    }
    newNode->value = value;
    newNode->next = NULL;

    if (isQueueEmpty(queue)) {
        queue->head = newNode;
    } else {
        queue->tail->next = newNode;
    }
    queue->tail = newNode;
    printf("Enqueued: %d\n", value);
}

// Recursive helper function to display the queue
void displayQueueHelper(struct Node* current) {
    if (current == NULL) {
        return;
    }
    printf("%d ", current->value);
    displayQueueHelper(current->next);
}

// Display the entire queue recursively
void displayQueue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }

    displayQueueHelper(queue->head); // Display using recursive helper
}

int main() {
    struct Queue queue;
    initializeQueue(&queue);

    int choice, value;
    int numElements;

    while (1) {
        printf("\nQueue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Display Queue\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of elements you want to enqueue: ");
                scanf("%d", &numElements);

                for (int i = 0; i < numElements; i++) {
                    printf("Enter value for element %d: ", i + 1);
                    scanf("%d", &value);
                    enqueue(&queue, value);
                }
                break;

            case 2:
                printf("Queue: ");
                displayQueue(&queue);
                printf("\n");
                break;

            case 3:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
