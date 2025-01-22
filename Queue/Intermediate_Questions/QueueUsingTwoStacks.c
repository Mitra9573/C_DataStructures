#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* stack1 = NULL;
struct Node* stack2 = NULL;

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


void push(struct Node** stack, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *stack;
    *stack = newNode;
}

int pop(struct Node** stack) {
    if (*stack == NULL) {
        printf("Stack is empty!\n");
        return -1;
    }
    struct Node* temp = *stack;
    int data = temp->data;
    *stack = (*stack)->next;
    free(temp);
    return data;
}

void enqueue(int data) {
    push(&stack1, data);
}


int dequeue() {
    if (stack2 == NULL) {
        while (stack1 != NULL) {
            int data = pop(&stack1);
            push(&stack2, data);
        }
    }

    if (stack2 == NULL) {
        printf("Queue is empty!\n");
        return -1;
    }

    return pop(&stack2);
}


void displayQueue() {
    if (stack1 == NULL && stack2 == NULL) {
        printf("Queue is empty!\n");
        return;
    }

    struct Node* temp;

    printf("Queue: ");

    
    if (stack2 != NULL) {
        temp = stack2;
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
    }

    
    if (stack1 != NULL) {
        struct Node* temp1 = NULL;
        temp = stack1;
        while (temp != NULL) {
            push(&temp1, temp->data);
            temp = temp->next;
        }
        while (temp1 != NULL) {
            printf("%d ", pop(&temp1));
        }
    }

    printf("\n");
}

int main() {
    int choice, data;

    do {
        printf("\nQueue Operations using Two Stacks:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to enqueue: ");
                scanf("%d", &data);
                enqueue(data);
                break;

            case 2:
                data = dequeue();
                if (data != -1) {
                    printf("Dequeued: %d\n", data);
                }
                break;

            case 3:
                displayQueue();
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
