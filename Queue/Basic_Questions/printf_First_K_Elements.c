#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Define the Queue structure with dynamic memory for the queue array
typedef struct {
    int front;
    int rear;
    int queueSize;
    int* queueArray;
} Queue;

// Function to initialize the queue with a dynamic array
void initializeQueue(Queue* queue, int size) {
    queue->front = -1;
    queue->rear = -1;
    queue->queueSize = size;
    queue->queueArray = (int*)malloc(sizeof(int) * size);  // Dynamically allocate memory
    if (queue->queueArray == NULL) {
        printf("Memory allocation failed! Cannot initialize the queue.\n");
        exit(1);
    }
}

// Function to check if the queue is empty
int isQueueEmpty(Queue* queue) {
    return queue->front == -1 || queue->front > queue->rear;
}

// Function to enqueue an element into the queue
void enqueue(Queue* queue, int value) {
    if (queue->rear == queue->queueSize - 1) {
        printf("Queue Overflow! Cannot enqueue %d\n", value);
        return;
    }
    if (queue->front == -1) {
        queue->front = 0;  // Set front if the queue is empty
    }
    queue->queueArray[++queue->rear] = value;
    printf("Enqueued: %d\n", value);
}

// Function to dequeue an element from the queue
int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue Underflow! Cannot dequeue.\n");
        return -1;
    }
    int dequeuedValue = queue->queueArray[queue->front++];
    if (queue->front > queue->rear) {  // Reset queue if it is empty after dequeue
        queue->front = queue->rear = -1;
    }
    return dequeuedValue;
}

// Function to display the current elements of the queue
void displayQueue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Queue: ");
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("%d ", queue->queueArray[i]);
    }
    printf("\n");
}

int main() {
    Queue queue;
    int queueSize, choice, value;

    // Prompt user for the queue size
    printf("Enter the size of the queue: ");
    scanf("%d", &queueSize);

    if (queueSize > MAX) {
        printf("Size exceeds maximum limit of %d.\n", MAX);
        return 1;
    }

    // Initialize the queue with dynamic memory allocation
    initializeQueue(&queue, queueSize);

    while (1) {
        // Display queue operations menu
        printf("\nQueue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display Queue\n");
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
                value = dequeue(&queue);
                if (value != -1) {
                    printf("Dequeued: %d\n", value);
                }
                break;
            case 3:
                displayQueue(&queue);
                break;
            case 4:
                printf("Exiting the Program\n");
                // Free dynamically allocated memory before exiting
                free(queue.queueArray);
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
