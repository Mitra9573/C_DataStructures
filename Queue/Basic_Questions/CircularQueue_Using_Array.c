#include <stdio.h>
#include <stdlib.h>

struct CircularQueue {
    int front;
    int rear;
    int capacity;
    int* queueArray;
};

// Function to initialize the circular queue
void initializeQueue(struct CircularQueue* queue, int capacity) {
    queue->front = -1;
    queue->rear = -1;
    queue->capacity = capacity;
    queue->queueArray = (int*)malloc(capacity * sizeof(int));
    if (queue->queueArray == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
}

// Function to check if the queue is empty
int isQueueEmpty(struct CircularQueue* queue) {
    return queue->front == -1;
}

// Function to check if the queue is full
int isQueueFull(struct CircularQueue* queue) {
    return (queue->rear + 1) % queue->capacity == queue->front;
}

// Function to add an element to the queue
void enqueue(struct CircularQueue* queue, int element) {
    if (isQueueFull(queue)) {
        printf("Queue Overflow! Cannot enqueue %d.\n", element);
        return;
    }
    if (isQueueEmpty(queue)) {
        queue->front = 0; // Set front to 0 if the queue is empty
    }
    queue->rear = (queue->rear + 1) % queue->capacity; // Circular increment
    queue->queueArray[queue->rear] = element;
    printf("Enqueued: %d\n", element);
}

// Function to remove an element from the queue
int dequeue(struct CircularQueue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue Underflow! Cannot dequeue.\n");
        return -1;
    }
    int dequeuedElement = queue->queueArray[queue->front];
    if (queue->front == queue->rear) { // If the queue has only one element
        queue->front = -1; 
        queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % queue->capacity; // Circular increment
    }
    return dequeuedElement;
}

// Function to display the elements in the queue
void displayQueue(struct CircularQueue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue: ");
    int i = queue->front;
    while (1) {
        printf("%d ", queue->queueArray[i]);
        if (i == queue->rear) {
            break;
        }
        i = (i + 1) % queue->capacity; // Circular increment
    }
    printf("\n");
}

// Main function to interact with the user
int main() {
    struct CircularQueue queue;
    int capacity, choice, element;

    // Dynamic input for the capacity of the circular queue
    printf("Enter the capacity of the circular queue: ");
    scanf("%d", &capacity);

    if (capacity <= 0) {
        printf("Invalid queue capacity.\n");
        return 1;
    }

    initializeQueue(&queue, capacity);

    while (1) {
        // Display menu options
        printf("\nCircular Queue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to enqueue: ");
                scanf("%d", &element);
                enqueue(&queue, element);
                break;
            case 2:
                element = dequeue(&queue);
                if (element != -1) {
                    printf("Dequeued: %d\n", element);
                }
                break;
            case 3:
                displayQueue(&queue);
                break;
            case 4:
                printf("Exiting the program.\n");
                free(queue.queueArray); // Free dynamically allocated memory
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
