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


int isEmpty() {
    return front == NULL;
}

void enqueue(int data) {
    struct Node* newNode = createNode(data);
    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

int dequeue() {
    if (isEmpty()) {
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

int getFront() {
    if (isEmpty()) {
        return -1;
    }
    return front->data;
}

void slidingWindowMaximum(int* nums, int numsSize, int k) {
    if (numsSize == 0 || k == 0) {
        return;
    }

    int* result = (int*)malloc((numsSize - k + 1) * sizeof(int));
    int resultIndex = 0;

    for (int i = 0; i < numsSize; i++) {
    
        while (!isEmpty() && nums[getFront()] <= nums[i]) {
            dequeue();
        }
        enqueue(i);
        if (getFront() <= i - k) {
            dequeue();
        }
        if (i >= k - 1) {
            result[resultIndex++] = nums[getFront()];
        }
    }
    printf("Sliding window maximums are: ");
    for (int i = 0; i < resultIndex; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
}

int main() {
    int n, k;
    

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int* nums = (int*)malloc(n * sizeof(int));
    
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    printf("Enter the window size: ");
    scanf("%d", &k);
    slidingWindowMaximum(nums, n, k);


    free(nums);

    return 0;
}
