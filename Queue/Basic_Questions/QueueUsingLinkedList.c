#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node* next;
};

struct Queue {
    struct Node* front;
    struct Node* rear;
};

void initializeQueue(struct Queue* que) {
    que->front = NULL;
    que->rear = NULL;
}

void enqueue(struct Queue* que, int element) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed! Cannot enqueue %d\n", element);
        return;
    }
    newNode->data = element;
    newNode->next = NULL;

    if (que->rear == NULL) { 
        que->front = newNode;
        que->rear = newNode;
    } else {
        que->rear->next = newNode;
        que->rear = newNode;
    }
    printf("Enqueued: %d\n", element);
}
int dequeue(struct Queue* que) {
    if (que->front == NULL) { 
        printf("Queue Underflow! Cannot dequeue.\n");
        return -1;
    }

    struct Node* temp = que->front;
    int dequeuedElement = temp->data;
    que->front = que->front->next;

    if (que->front == NULL) {
        que->rear = NULL;
    }

    free(temp);
    return dequeuedElement;
}
void display(struct Queue* que) {
    if (que->front == NULL) {
        printf("Queue is empty!\n");
        return;
    }

    struct Node* current = que->front;
    printf("Queue: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
int main() {
    struct Queue que;
    initializeQueue(&que);

    int choice, element;

    while (1) {
        printf("\nQueue Operations:\n");
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
                enqueue(&que, element);
                break;
            case 2:
                element = dequeue(&que);
                if (element != -1) {
                    printf("Dequeued: %d\n", element);
                }
                break;
            case 3:
                display(&que);
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
