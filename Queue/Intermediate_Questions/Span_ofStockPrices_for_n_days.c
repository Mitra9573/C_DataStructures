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


struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}


void enqueue(struct Queue* q, int data) {
    struct Node* newNode = createNode(data);
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

int dequeue(struct Queue* q) {
    if (q->front == NULL) {
        return -1; 
    }
    int data = q->front->data;
    struct Node* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return data;
}

int front(struct Queue* q) {
    if (q->front != NULL) {
        return q->front->data;
    }
    return -1;
}


void calculateSpan(int prices[], int n) {
    struct Queue* q = createQueue();


    for (int i = 0; i < n; i++) {
    
        while (q->front != NULL && prices[front(q)] <= prices[i]) {
            dequeue(q);
        }

        
        int span = (q->front == NULL) ? (i + 1) : (i - front(q));

        
        printf("%d ", span);

        
        enqueue(q, i);
    }
    printf("\n");
}

int main() {
    int n;

    
    printf("Enter the number of days: ");
    scanf("%d", &n);

    int prices[n];
    printf("Enter the stock prices for %d days:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &prices[i]);
    }

    printf("Stock spans for the given prices are:\n");
    calculateSpan(prices, n);

    return 0;
}
