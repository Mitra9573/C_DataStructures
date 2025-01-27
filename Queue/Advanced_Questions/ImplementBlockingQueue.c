#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Define the structure for the blocking queue
typedef struct BlockingQueue {
    int* buffer;         // Buffer to hold the queue elements
    int capacity;        // Maximum size of the queue
    int front;           // Index of the front element
    int rear;            // Index of the rear element
    int count;           // Number of elements in the queue
    pthread_mutex_t lock;        // Mutex for synchronization
    pthread_cond_t not_full;     // Condition variable to check if the queue is not full
    pthread_cond_t not_empty;    // Condition variable to check if the queue is not empty
} BlockingQueue;

// Function to create a blocking queue
BlockingQueue* createBlockingQueue(int capacity) {
    BlockingQueue* queue = (BlockingQueue*)malloc(sizeof(BlockingQueue));
    queue->buffer = (int*)malloc(capacity * sizeof(int));
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = 0;
    queue->count = 0;
    pthread_mutex_init(&queue->lock, NULL);
    pthread_cond_init(&queue->not_full, NULL);
    pthread_cond_init(&queue->not_empty, NULL);
    return queue;
}

// Function to add an element to the queue (blocking if full)
void enqueue(BlockingQueue* queue, int value) {
    pthread_mutex_lock(&queue->lock);

    // Wait until the queue is not full
    while (queue->count == queue->capacity) {
        pthread_cond_wait(&queue->not_full, &queue->lock);
    }

    // Add the element to the queue
    queue->buffer[queue->rear] = value;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->count++;

    // Signal that the queue is not empty
    pthread_cond_signal(&queue->not_empty);

    pthread_mutex_unlock(&queue->lock);
}

// Function to remove an element from the queue (blocking if empty)
int dequeue(BlockingQueue* queue) {
    pthread_mutex_lock(&queue->lock);

    // Wait until the queue is not empty
    while (queue->count == 0) {
        pthread_cond_wait(&queue->not_empty, &queue->lock);
    }

    // Remove the element from the queue
    int value = queue->buffer[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->count--;

    // Signal that the queue is not full
    pthread_cond_signal(&queue->not_full);

    pthread_mutex_unlock(&queue->lock);

    return value;
}

// Function to free the blocking queue
void freeBlockingQueue(BlockingQueue* queue) {
    free(queue->buffer);
    pthread_mutex_destroy(&queue->lock);
    pthread_cond_destroy(&queue->not_full);
    pthread_cond_destroy(&queue->not_empty);
    free(queue);
}

// Producer thread function
void* producer(void* arg) {
    BlockingQueue* queue = (BlockingQueue*)arg;
    int value;
    while (1) {
        printf("Enter value to enqueue (-1 to stop): ");
        scanf("%d", &value);
        if (value == -1) {
            break;
        }
        enqueue(queue, value);
        printf("Producer: Enqueued %d\n", value);
    }
    return NULL;
}

// Consumer thread function
void* consumer(void* arg) {
    BlockingQueue* queue = (BlockingQueue*)arg;
    int stop = 0;
    while (!stop) {
        int value = dequeue(queue);
        if (value == -1) {
            stop = 1;
        } else {
            printf("Consumer: Dequeued %d\n", value);
        }
        sleep(1); // Simulate work
    }
    return NULL;
}

// Main function
int main() {
    int capacity;
    printf("Enter the capacity of the queue: ");
    scanf("%d", &capacity);

    // Create a blocking queue
    BlockingQueue* queue = createBlockingQueue(capacity);

    // Create producer and consumer threads
    pthread_t producerThread, consumerThread;
    pthread_create(&producerThread, NULL, producer, queue);
    pthread_create(&consumerThread, NULL, consumer, queue);

    // Wait for threads to finish
    pthread_join(producerThread, NULL);

    // Enqueue -1 to signal consumer to stop
    enqueue(queue, -1);
    pthread_join(consumerThread, NULL);
    // Free the queue
    freeBlockingQueue(queue);

    return 0;
}
