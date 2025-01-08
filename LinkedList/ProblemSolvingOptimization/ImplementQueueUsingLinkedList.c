#include <stdio.h>
#include <stdlib.h>

// Define a Node for the queue
struct Node {
    int value;
    struct Node* next;
};

// Define a structure for the queue with front and rear pointers
struct Queue {
    struct Node* front;
    struct Node* rear;
    int size; // To track the number of elements in the queue
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize a new queue
struct Queue* createQueue() {
    struct Queue* newQueue = (struct Queue*)malloc(sizeof(struct Queue));
    newQueue->front = newQueue->rear = NULL;
    newQueue->size = 0; // Initialize size to 0
    return newQueue;
}

// Function to enqueue an element into the queue
void enqueue(struct Queue* queue, int newData) {
    struct Node* newNode = createNode(newData);

    if (queue->rear == NULL) {
        // If the queue is empty, both front and rear point to the new node
        queue->front = queue->rear = newNode;
        printf("%d enqueued to the queue.\n", newData);
    } else {
        // Add the new node at the end of the queue and update the rear pointer
        queue->rear->next = newNode;
        queue->rear = newNode;
        printf("%d enqueued to the queue.\n", newData);
    }

    queue->size++; // Increment the size of the queue
}

// Function to dequeue an element from the queue
int dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        printf("Queue underflow! Cannot dequeue from an empty queue.\n");
        return -1; // Return -1 to indicate an error
    }

    struct Node* nodeToDequeue = queue->front;
    int dequeuedData = nodeToDequeue->value;

    // Move the front pointer to the next node
    queue->front = queue->front->next;

    // If the front becomes NULL, set the rear to NULL as well
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(nodeToDequeue);
    queue->size--; // Decrement the size of the queue
    return dequeuedData;
}

// Function to check if the queue is empty
int isQueueEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

// Function to display the queue
void displayQueue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Queue elements (front to rear): ");
    struct Node* currentNode = queue->front;
    while (currentNode != NULL) {
        printf("%d ", currentNode->value);
        currentNode = currentNode->next;
    }
    printf("\n");
}

// Main function
int main() {
    struct Queue* queue = createQueue();
    int operationChoice, newData, dequeuedData;

    printf("Queue Operations Using Linked List:\n");
    printf("1. Enqueue\n");
    printf("2. Dequeue\n");
    printf("3. Display Queue\n");
    printf("4. Check if Queue is Empty\n");
    printf("5. Exit\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &operationChoice);

        switch (operationChoice) {
            case 1: // Enqueue
                printf("Enter the value to enqueue: ");
                scanf("%d", &newData);
                enqueue(queue, newData);
                break;
            case 2: // Dequeue
                dequeuedData = dequeue(queue);
                if (dequeuedData != -1) {
                    printf("Dequeued value: %d\n", dequeuedData);
                }
                break;
            case 3: // Display
                displayQueue(queue);
                break;
            case 4: // Is Empty
                printf("Queue is %s\n", isQueueEmpty(queue) ? "Empty" : "Not Empty");
                break;
            case 5: // Exit
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}
