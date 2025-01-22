#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* front = NULL;
struct Node* rear = NULL;

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void enqueue(int data) {
    struct Node* newNode = createNode(data);
    if (rear == NULL) {
        front = rear = newNode;
        return;
    }
    rear->next = newNode;
    rear = newNode;
}

int dequeue() {
    if (front == NULL) {
        return -1;  
    }
    struct Node* temp = front;
    int data = temp->data;
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

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int leftArr[n1], rightArr[n2];

    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSortQueue() {
    if (front == NULL || front->next == NULL) {
        return;  
    }


    struct Node* tempNode = front;
    int size = 0;

    
    while (tempNode != NULL) {
        size++;
        tempNode = tempNode->next;
    }


    int arr[size];
    tempNode = front;
    for (int i = 0; i < size; i++) {
        arr[i] = dequeue();
    }

    
    mergeSort(arr, 0, size - 1);

    
    for (int i = 0; i < size; i++) {
        enqueue(arr[i]);
    }
}

void printQueue() {
    struct Node* temp = front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int n;
    
    
    printf("Enter the number of elements in the queue: ");
    scanf("%d", &n);

    
    printf("Enter the elements of the queue (space-separated):\n");
    for (int i = 0; i < n; i++) {
        int temp;
        scanf("%d", &temp);
        enqueue(temp);  
    }

    
    printf("Original queue: ");
    printQueue();

    
    mergeSortQueue();


    printf("Sorted queue: ");
    printQueue();

    return 0;
}
