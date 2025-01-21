#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for the queue
struct Node {
    char* data;  // Dynamically allocated string
    struct Node* next;
};

// Queue structure to hold the front and rear pointers
struct Queue {
    struct Node* front;
    struct Node* rear;
};

// Function to create a new node with dynamic memory for string
struct Node* createNode(const char* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = (char*)malloc(strlen(data) + 1);  // Allocate memory for the string
    strcpy(newNode->data, data);  // Copy the string into the node
    newNode->next = NULL;
    return newNode;
}

// Function to initialize a queue
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
const char* dequeue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        return NULL;
    }
    struct Node* tempNode = queue->front;
    const char* data = tempNode->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(tempNode->data);  // Free the dynamically allocated string
    free(tempNode);         // Free the node
    return data;
}

// Function to generate binary numbers from 1 to n
void generateBinaryNumbers(int n) {
    struct Queue* queue = createQueue();  // Create a new queue
    enqueue(queue, "1");  // Start with "1"

    for (int i = 1; i <= n; i++) {
        const char* current = dequeue(queue);  // Dequeue the front item
        printf("%s\n", current);  // Print the current binary number

        // Prepare next binary numbers by appending "0" and "1" to the current string
        char next1[32], next2[32];

        strcpy(next1, current);
        strcat(next1, "0");

        strcpy(next2, current);
        strcat(next2, "1");

        // Enqueue the next binary numbers
        enqueue(queue, next1);
        enqueue(queue, next2);
    }

    // Free the queue memory
    struct Node* currentNode = queue->front;
    while (currentNode != NULL) {
        struct Node* nextNode = currentNode->next;
        free(currentNode->data);  // Free the string in the node
        free(currentNode);         // Free the node itself
        currentNode = nextNode;
    }
    free(queue);  // Free the queue structure
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    printf("Binary numbers from 1 to %d:\n", n);
    generateBinaryNumbers(n);

    return 0;
}
