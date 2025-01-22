#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char* data;  
    struct Node* next;
};

struct Node* front = NULL;
struct Node* rear = NULL;

struct Node* createNode(const char* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = (char*)malloc(strlen(data) + 1);  // Allocate memory for the string
    strcpy(newNode->data, data);  // Copy the string into the node
    newNode->next = NULL;
    return newNode;
}

void enqueue(const char* data) {
    struct Node* newNode = createNode(data);
    if (rear == NULL) {
        front = rear = newNode;
        return;
    }
    rear->next = newNode;
    rear = newNode;
}

char* dequeue() {
    if (front == NULL) {
        return NULL;
    }
    struct Node* temp = front;
    char* data = temp->data;
    front = front->next;
    if (front == NULL) {
        rear = NULL;
    }
    free(temp);
    return data;
}

int isEmpty() {
    return front == NULL;
}

void rotateQueueLeft(int k) {
    if (front == NULL || k == 0) {
        return;
    }
    // Store the first `k` elements temporarily
    char* temp[k];
    for (int i = 0; i < k; i++) {
        if (front != NULL) {
            temp[i] = dequeue();
        }
    }

    // Enqueue all remaining elements
    struct Node* tempNode = front;
    while (tempNode != NULL) {
        char* data = dequeue();
        enqueue(data);
        free(data);  // Free the dequeued string to avoid memory leaks
        tempNode = tempNode->next;
    }

    // Enqueue the `k` elements back at the rear
    for (int i = 0; i < k; i++) {
        enqueue(temp[i]);
        free(temp[i]);  // Free the temporary string after enqueuing
    }
}

void printQueue() {
    struct Node* temp = front;
    while (temp != NULL) {
        printf("%s ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int n, k;

    printf("Enter the number of elements in the queue: ");
    scanf("%d", &n);

    printf("Enter the elements of the queue (space-separated):\n");
    for (int i = 0; i < n; i++) {
        char temp[32];
        scanf("%s", temp);
        enqueue(temp);  
    }

    printf("Original queue: ");
    printQueue();

    printf("Enter the number of positions to rotate left: ");
    scanf("%d", &k);

    rotateQueueLeft(k);

    printf("Queue after rotating left by %d positions: ", k);
    printQueue();

    return 0;
}
