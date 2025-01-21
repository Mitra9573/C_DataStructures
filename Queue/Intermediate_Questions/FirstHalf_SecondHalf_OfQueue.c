#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char* data;  // Dynamically allocated string
    struct Node* next;
};

// Queue structure with front and rear pointers
struct Queue {
    struct Node* front;
    struct Node* rear;
};

// Function to create a new node with dynamic string allocation
struct Node* createNode(const char* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = (char*)malloc(strlen(data) + 1);  // Allocate memory for the string
    strcpy(newNode->data, data);  // Copy the string into the node
    newNode->next = NULL;
    return newNode;
}

// Function to initialize a new queue
struct Queue* createQueue() {
    struct Queue* newQueue = (struct Queue*)malloc(sizeof(struct Queue));
    newQueue->front = newQueue->rear = NULL;
    return newQueue;
}

// Function to check if the queue is empty
int isQueueEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

// Function to enqueue a string into the queue
void enqueue(struct Queue* queue, const char* data) {
    struct Node* newNode = createNode(data);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

// Function to dequeue a string from the queue
char* dequeue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        return NULL;
    }
    struct Node* tempNode = queue->front;
    char* data = tempNode->data;  // Get the string data
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(tempNode);  // Free the node but keep the string
    return data;
}

// Function to interleave the elements in the queue
void interleaveQueue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        return;
    }

    struct Node* tempNode = queue->front;
    int size = 0;

    // Calculate the size of the queue
    while (tempNode != NULL) {
        size++;
        tempNode = tempNode->next;
    }

    int mid = size / 2;

    // Store the first half of the queue in an array
    char* firstHalf[mid];
    for (int i = 0; i < mid; i++) {
        firstHalf[i] = dequeue(queue);
    }

    // Store the second half of the queue in another array
    char* secondHalf[size - mid];
    for (int i = 0; i < size - mid; i++) {
        secondHalf[i] = dequeue(queue);
    }

    // Interleave elements from both halves back into the queue
    for (int i = 0; i < mid; i++) {
        enqueue(queue, firstHalf[i]);  // Enqueue from the first half
        enqueue(queue, secondHalf[i]); // Enqueue from the second half
    }

    // If the queue size is odd, enqueue the last element of the second half
    if (size % 2 != 0) {
        enqueue(queue, secondHalf[mid]);
    }

    // Free the dynamically allocated memory for the strings in arrays
    for (int i = 0; i < mid; i++) {
        free(firstHalf[i]);
    }
    for (int i = 0; i < size - mid; i++) {
        free(secondHalf[i]);
    }
}

// Function to print the queue
void printQueue(struct Queue* queue) {
    struct Node* tempNode = queue->front;
    while (tempNode != NULL) {
        printf("%s ", tempNode->data);
        tempNode = tempNode->next;
    }
    printf("\n");
}

// Main function
int main() {
    int numElements;

    // Create a new dynamic queue
    struct Queue* queue = createQueue();

    // Input number of elements in the queue
    printf("Enter the number of elements in the queue: ");
    scanf("%d", &numElements);

    printf("Enter the elements of the queue (space-separated):\n");
    for (int i = 0; i < numElements; i++) {
        char temp[32];
        scanf("%s", temp);  // Read the string
        enqueue(queue, temp);  // Enqueue the string
    }

    // Print the original queue
    printf("Original queue: ");
    printQueue(queue);

    // Interleave the elements in the queue
    interleaveQueue(queue);

    // Print the queue after interleaving
    printf("Queue after interleaving: ");
    printQueue(queue);

    // Free the dynamically allocated memory for the queue
    struct Node* currentNode = queue->front;
    while (currentNode != NULL) {
        struct Node* nextNode = currentNode->next;
        free(currentNode->data);  // Free the string in each node
        free(currentNode);         // Free the node itself
        currentNode = nextNode;
    }
    free(queue);  // Free the queue structure

    return 0;
}
