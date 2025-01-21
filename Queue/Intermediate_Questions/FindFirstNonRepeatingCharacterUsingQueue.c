#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_COUNT 256

// Node structure to represent each element in the queue
struct Node {
    char data;
    struct Node* next;
};

// Queue structure to hold front and rear pointers
struct Queue {
    struct Node* front;
    struct Node* rear;
};

// Function to create a new node
struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize an empty queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
int isQueueEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

// Function to enqueue a character into the queue
void enqueue(struct Queue* queue, char data) {
    struct Node* newNode = createNode(data);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

// Function to dequeue a character from the queue
char dequeue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        return '\0';
    }
    struct Node* temp = queue->front;
    char data = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return data;
}

// Function to find the first non-repeating character in the stream
void firstNonRepeating(char* stream) {
    int count[CHAR_COUNT] = {0};
    struct Queue* queue = createQueue();
    
    for (int i = 0; stream[i] != '\0'; i++) {
        char ch = stream[i];
        enqueue(queue, ch);
        count[ch]++;
        
        while (!isQueueEmpty(queue) && count[queue->front->data] > 1) {
            dequeue(queue);
        }

        if (!isQueueEmpty(queue)) {
            printf("First non-repeating character so far: %c\n", queue->front->data);
        } else {
            printf("No non-repeating character so far\n");
        }
    }

    // Free the dynamically allocated queue after processing
    free(queue);
}

int main() {
    char stream[100];
    printf("Enter the stream of characters: ");
    scanf("%s", stream);
    firstNonRepeating(stream);
    return 0;
}
