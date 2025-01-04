#include <stdio.h>
#include <stdlib.h>


struct Queue {
    int* arr;
    int front, rear, size, capacity;
};

struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->rear = queue->size = 0;
    queue->arr = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}
int isEmpty(struct Queue* queue) {
    return queue->size == 0;
}
int isFull(struct Queue* queue) {
    return queue->size == queue->capacity;
}
void enqueue(struct Queue* queue, int value) {
    if (isFull(queue)) {
        printf("Queue is full\n");
        return;
    }
    queue->arr[queue->rear] = value;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->size++;
}
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    int value = queue->arr[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return value;
}
int front(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue->arr[queue->front];
}
struct Stack {
    struct Queue* queue1;
    struct Queue* queue2;
};
struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->queue1 = createQueue(capacity);
    stack->queue2 = createQueue(capacity);
    return stack;
}
void push(struct Stack* stack, int value) {
    enqueue(stack->queue1, value);
}
int pop(struct Stack* stack) {
    if (isEmpty(stack->queue1)) {
        printf("Stack is empty\n");
        return -1;
    }

    while (stack->queue1->size > 1) {
        enqueue(stack->queue2, dequeue(stack->queue1));
    }
    int poppedValue = dequeue(stack->queue1);
    struct Queue* temp = stack->queue1;
    stack->queue1 = stack->queue2;
    stack->queue2 = temp;
    
    return poppedValue;
}
int top(struct Stack* stack) {
    if (isEmpty(stack->queue1)) {
        printf("Stack is empty\n");
        return -1;
    }
    while (stack->queue1->size > 1) {
        enqueue(stack->queue2, dequeue(stack->queue1));
    }
    int topValue = front(stack->queue1);
    enqueue(stack->queue1, dequeue(stack->queue1));
    struct Queue* temp = stack->queue1;
    stack->queue1 = stack->queue2;
    stack->queue2 = temp;

    return topValue;
}

int main() {
    int capacity = 5;
    struct Stack* stack = createStack(capacity);
    int choice, value;

    while (1) {
        printf("\nChoose an operation:\n");
        printf("1. Push\n2. Pop\n3. Top\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                printf("Enter a value to push: ");
                scanf("%d", &value);
                push(stack, value);
                printf("%d pushed to the stack.\n", value);
                break;

            case 2: 
                value = pop(stack);
                if (value != -1) {
                    printf("Popped %d from the stack.\n", value);
                }
                break;

            case 3: 
                value = top(stack);
                if (value != -1) {
                    printf("Top of the stack is %d.\n", value);
                }
                break;

            case 4: 
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }

    return 0;
}
