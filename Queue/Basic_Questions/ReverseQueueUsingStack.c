#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node* next;
};
struct Stack {
    int top;
    int capacity;
    int* array;
};
struct Queue {
    struct Node* front;
    struct Node* rear;
};

void initializeQueue(struct Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}
int isQueueEmpty(struct Queue* q) {
    return q->front == NULL;
}
void enqueue(struct Queue* q, int element) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed! Cannot enqueue %d.\n", element);
        return;
    }
    newNode->data = element;
    newNode->next = NULL;

    if (isQueueEmpty(q)) {
        q->front = newNode;
    } else {
        q->rear->next = newNode;
    }
    q->rear = newNode;
    printf("Enqueued: %d\n", element);
}
int dequeue(struct Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue Underflow! Cannot dequeue.\n");
        return -1;
    }

    struct Node* temp = q->front;
    int dequeuedElement = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL; 
    }

    free(temp);
    return dequeuedElement;
}
void displayQueue(struct Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Queue: ");
    struct Node* current = q->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isStackFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}
int isStackEmpty(struct Stack* stack) {
    return stack->top == -1;
}
void push(struct Stack* stack, int element) {
    if (isStackFull(stack)) {
        printf("Stack Overflow! Cannot push %d.\n", element);
        return;
    }
    stack->array[++stack->top] = element;
}

int pop(struct Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack Underflow! Cannot pop.\n");
        return -1;
    }
    return stack->array[stack->top--];
}
void reverseQueue(struct Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty! Cannot reverse.\n");
        return;
    }
    struct Stack* stack = createStack(100);
    while (!isQueueEmpty(q)) {
        int dequeuedElement = dequeue(q);
        push(stack, dequeuedElement);
    }
    while (!isStackEmpty(stack)) {
        int poppedElement = pop(stack);
        enqueue(q, poppedElement);
    }

    printf("Queue reversed successfully.\n");
    free(stack->array);
    free(stack);
}
int main() {
    struct Queue q;
    initializeQueue(&q);

    int choice, element;

    while (1) {
        printf("\nQueue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display Queue\n");
        printf("4. Reverse Queue\n");
        printf("5. Exit\n");
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
                displayQueue(&q);
                break;
            case 4:
                reverseQueue(&q);
                break;
            case 5:
                printf("Exiting The Program\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
