#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node* nextNode;
};

struct Queue {
    struct Node* head;
    struct Node* tail;
};

void initializeQueue(struct Queue* queue) {
    queue->head = NULL;
    queue->tail = NULL;
}

int isQueueEmpty(struct Queue* queue) {
    return queue->head == NULL;
}

void addToQueue(struct Queue* queue, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed! Cannot add %d to queue.\n", value);
        return;
    }
    newNode->value = value;
    newNode->nextNode = NULL;

    if (isQueueEmpty(queue)) {
        queue->head = newNode;
    } else {
        queue->tail->nextNode = newNode;
    }
    queue->tail = newNode;
    printf("Added: %d\n", value);
}

int removeFromQueue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty! Cannot remove any elements.\n");
        return -1;
    }

    struct Node* tempNode = queue->head;
    int removedValue = tempNode->value;
    queue->head = queue->head->nextNode;

    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    free(tempNode);
    return removedValue;
}

int peekQueue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty! Cannot peek.\n");
        return -1;
    }
    return queue->head->value;
}

void displayQueue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Queue: ");
    struct Node* currentNode = queue->head;
    while (currentNode != NULL) {
        printf("%d ", currentNode->value);
        currentNode = currentNode->nextNode;
    }
    printf("\n");
}

int main() {
    struct Queue queue;
    initializeQueue(&queue);

    int option, inputValue;
    int numElements;

    while (1) {
        printf("\nQueue Operations Menu:\n");
        printf("1. Add to Queue\n");
        printf("2. Remove from Queue\n");
        printf("3. Peek at the Front\n");
        printf("4. Display the Queue\n");
        printf("5. Exit\n");
        printf("Select an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter the number of elements to add: ");
                scanf("%d", &numElements);
                for (int i = 0; i < numElements; i++) {
                    printf("Enter value for element %d: ", i + 1);
                    scanf("%d", &inputValue);
                    addToQueue(&queue, inputValue);
                }
                break;
            case 2:
                inputValue = removeFromQueue(&queue);
                if (inputValue != -1) {
                    printf("Removed: %d\n", inputValue);
                }
                break;
            case 3:
                inputValue = peekQueue(&queue);
                if (inputValue != -1) {
                    printf("Front element: %d\n", inputValue);
                }
                break;
            case 4:
                displayQueue(&queue);
                break;
            case 5:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice! Please select a valid option.\n");
        }
    }

    return 0;
}
