#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int front;
    int rear;
    int size;
    int queue[MAX];
} Queue;

void initializeQueue(Queue *q, int size) {
    q->front = -1;
    q->rear = -1;
    q->size = size;
}

void enqueue(Queue *q, int element) {
    if (q->rear == q->size - 1) {
        printf("Queue Overflow! Cannot enqueue %d\n", element);
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->queue[++q->rear] = element;
    printf("Enqueued: %d\n", element);
}

int dequeue(Queue *q) {
    if (q->front == -1 || q->front > q->rear) {
        printf("Queue Underflow! Cannot dequeue.\n");
        return -1;
    }
    int dequeuedElement = q->queue[q->front++];
    if (q->front > q->rear) {
        q->front = q->rear = -1; 
    }
    return dequeuedElement;
}
void display(Queue *q) {
    if (q->front == -1 || q->front > q->rear) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->queue[i]);
    }
    printf("\n");
}
int main() {
    Queue q;
    int size, choice, element;

    printf("Enter the size of the queue: ");
    scanf("%d", &size);

    if (size > MAX) {
        printf("Size exceeds maximum limit of %d.\n", MAX);
        return 1;
    }

    initializeQueue(&q, size);

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
                enqueue(&q, element);
                break;
            case 2:
                element = dequeue(&q);
                if (element != -1) {
                    printf("Dequeued: %d\n", element);
                }
                break;
            case 3:
                display(&q);
                break;
            case 4:
                printf("Exiting The Program\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
