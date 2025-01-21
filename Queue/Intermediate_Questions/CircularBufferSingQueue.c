#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Queue {
    struct Node* front;
    struct Node* rear;
    int currentSize;
    int maxSize;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

struct Queue* createQueue(int maxSize) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    queue->currentSize = 0;
    queue->maxSize = maxSize;
    return queue;
}

int isQueueFull(struct Queue* queue) {
    return queue->currentSize == queue->maxSize;
}

int isQueueEmpty(struct Queue* queue) {
    return queue->currentSize == 0;
}

void enqueue(struct Queue* queue, int value) {
    if (isQueueFull(queue)) {
        // Remove the front element to make space
        struct Node* temp = queue->front;
        queue->front = queue->front->next;
        free(temp);
        
        // Decrease current size
        queue->currentSize--;
    }

    // Create a new node
    struct Node* newNode = createNode(value);

    if (isQueueEmpty(queue)) {
        // If the queue is empty, both front and rear point to the new node
        queue->front = queue->rear = newNode;
    } else {
        // Otherwise, add the new node at the rear
        queue->rear->next = newNode;
        queue->rear = newNode;
    }

    // Increase current size
    queue->currentSize++;
}

int dequeue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        return -1;  // Return -1 if queue is empty
    }

    // Remove the front element
    struct Node* temp = queue->front;
    int value = temp->data;
    queue->front = queue->front->next;

    // If the queue becomes empty, reset the rear pointer as well
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);

    // Decrease current size
    queue->currentSize--;

    return value;
}

void printQueue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    struct Node* temp = queue->front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int maxSize, numElements, value;

    // Get the maximum size of the queue from the user
    printf("Enter the maximum size of the queue: ");
    scanf("%d", &maxSize);

    // Create a queue with the specified size
    struct Queue* queue = createQueue(maxSize);

    // Get the number of elements to enqueue
    printf("Enter the number of elements to enqueue: ");
    scanf("%d", &numElements);

    // Enqueue the elements
    for (int i = 0; i < numElements; i++) {
        printf("Enter value to enqueue: ");
        scanf("%d", &value);
        enqueue(queue, value);
    }

    // Print the current queue
    printf("Queue after enqueuing elements:\n");
    printQueue(queue);

    // Enqueue more elements, which will overwrite the old ones due to full queue
    printf("Enqueuing more elements:\n");
    enqueue(queue, 100);
    enqueue(queue, 200);
    enqueue(queue, 300);

    // Print the updated queue
    printf("Queue after overwriting old elements:\n");
    printQueue(queue);

    // Free the allocated memory (optional, but good practice)
    while (!isQueueEmpty(queue)) {
        dequeue(queue);
    }
    free(queue);

    return 0;
}
