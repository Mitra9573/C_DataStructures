#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};


struct Deque {
    struct Node* front;
    struct Node* rear;
};


void initializeDeque(struct Deque* dq) {
    dq->front = NULL;
    dq->rear = NULL;
}

int isEmpty(struct Deque* dq) {
    return dq->front == NULL;
}

void insertFront(struct Deque* dq, int element) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed! Cannot insert %d at the front.\n", element);
        return;
    }
    newNode->data = element;
    newNode->next = dq->front;
    newNode->prev = NULL;

    if (isEmpty(dq)) {
        dq->rear = newNode; 
    } else {
        dq->front->prev = newNode;
    }
    dq->front = newNode;
    printf("Inserted %d at the front.\n", element);
}

void insertRear(struct Deque* dq, int element) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed! Cannot insert %d at the rear.\n", element);
        return;
    }
    newNode->data = element;
    newNode->prev = dq->rear;
    newNode->next = NULL;

    if (isEmpty(dq)) {
        dq->front = newNode; 
    } else {
        dq->rear->next = newNode;
    }
    dq->rear = newNode;
    printf("Inserted %d at the rear.\n", element);
}

int deleteFront(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque Underflow! Cannot delete from the front.\n");
        return -1;
    }

    struct Node* temp = dq->front;
    int deletedElement = temp->data;
    dq->front = dq->front->next;

    if (dq->front == NULL) {
        dq->rear = NULL; 
    } else {
        dq->front->prev = NULL;
    }

    free(temp);
    return deletedElement;
}


int deleteRear(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque Underflow! Cannot delete from the rear.\n");
        return -1;
    }

    struct Node* temp = dq->rear;
    int deletedElement = temp->data;
    dq->rear = dq->rear->prev;

    if (dq->rear == NULL) {
        dq->front = NULL;
    } else {
        dq->rear->next = NULL;
    }

    free(temp);
    return deletedElement;
}

void display(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty!\n");
        return;
    }

    printf("Deque: ");
    struct Node* current = dq->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct Deque dq;
    initializeDeque(&dq);

    int choice, element;

    while (1) {
        printf("\nDeque Operations:\n");
        printf("1. Insert Front\n");
        printf("2. Insert Rear\n");
        printf("3. Delete Front\n");
        printf("4. Delete Rear\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to insert at the front: ");
                scanf("%d", &element);
                insertFront(&dq, element);
                break;
            case 2:
                printf("Enter the element to insert at the rear: ");
                scanf("%d", &element);
                insertRear(&dq, element);
                break;
            case 3:
                element = deleteFront(&dq);
                if (element != -1) {
                    printf("Deleted from front: %d\n", element);
                }
                break;
            case 4:
                element = deleteRear(&dq);
                if (element != -1) {
                    printf("Deleted from rear: %d\n", element);
                }
                break;
            case 5:
                display(&dq);
                break;
            case 6:
                printf("Exiting The Program\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
