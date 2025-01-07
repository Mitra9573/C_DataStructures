#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CACHE_CAPACITY 5 // Define the capacity of the cache

// Node of the doubly linked list
struct Node {
    int key;
    int value;
    struct Node* prev;
    struct Node* next;
};

// Structure to represent the LRU Cache
struct LRUCache {
    int capacity;
    int size;
    struct Node* head;
    struct Node* tail;
    struct Node** hashTable;
};

// Function to create a new doubly linked list node
struct Node* createNode(int key, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize an LRU Cache
struct LRUCache* createLRUCache(int capacity) {
    struct LRUCache* cache = (struct LRUCache*)malloc(sizeof(struct LRUCache));
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = NULL;
    cache->tail = NULL;

    // Allocate memory for the hash table
    cache->hashTable = (struct Node**)calloc(capacity, sizeof(struct Node*));

    return cache;
}

// Function to move a node to the front of the doubly linked list (most recently used)
void moveToHead(struct LRUCache* cache, struct Node* node) {
    if (cache->head == node) {
        return; // Node is already at the head
    }

    // Detach the node from its current position
    if (node->prev) {
        node->prev->next = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }

    // If the node is the tail, update the tail
    if (cache->tail == node) {
        cache->tail = node->prev;
    }

    // Move the node to the head
    node->next = cache->head;
    node->prev = NULL;
    if (cache->head) {
        cache->head->prev = node;
    }
    cache->head = node;

    // Update the tail if the list had only one node
    if (cache->tail == NULL) {
        cache->tail = node;
    }
}

// Function to remove the least recently used node (from the tail)
void removeTail(struct LRUCache* cache) {
    if (cache->tail == NULL) {
        return;
    }

    struct Node* nodeToRemove = cache->tail;

    // Remove the tail node
    if (cache->tail->prev) {
        cache->tail->prev->next = NULL;
    }
    cache->tail = cache->tail->prev;

    // Update the hash table
    cache->hashTable[nodeToRemove->key % cache->capacity] = NULL;

    free(nodeToRemove);
    cache->size--;
}

// Function to put a key-value pair into the cache
void put(struct LRUCache* cache, int key, int value) {
    int hashIndex = key % cache->capacity;
    struct Node* node = cache->hashTable[hashIndex];

    // Check if the key already exists in the cache
    if (node != NULL && node->key == key) {
        // Update the value and move the node to the head
        node->value = value;
        moveToHead(cache, node);
        return;
    }

    // If the key does not exist, create a new node
    struct Node* newNode = createNode(key, value);

    // Add the new node to the hash table
    cache->hashTable[hashIndex] = newNode;

    // Add the node to the head of the doubly linked list
    newNode->next = cache->head;
    if (cache->head) {
        cache->head->prev = newNode;
    }
    cache->head = newNode;

    // Update the tail if the list was empty
    if (cache->tail == NULL) {
        cache->tail = newNode;
    }

    cache->size++;

    // If the cache is full, remove the least recently used node
    if (cache->size > cache->capacity) {
        removeTail(cache);
    }
}

// Function to get a value from the cache
int get(struct LRUCache* cache, int key) {
    int hashIndex = key % cache->capacity;
    struct Node* node = cache->hashTable[hashIndex];

    if (node != NULL && node->key == key) {
        // Move the node to the head and return the value
        moveToHead(cache, node);
        return node->value;
    }

    return -1; // Key not found
}

// Function to display the current state of the cache
void displayCache(struct LRUCache* cache) {
    struct Node* current = cache->head;
    printf("Cache contents (most to least recently used): ");
    while (current) {
        printf("[%d: %d] ", current->key, current->value);
        current = current->next;
    }
    printf("\n");
}

// Main function
int main() {
    struct LRUCache* cache = createLRUCache(CACHE_CAPACITY);

    int choice, userKey, userValue;
    while (1) {
        printf("\nLRU Cache Operations:\n");
        printf("1. Put (Insert/Update)\n");
        printf("2. Get\n");
        printf("3. Display Cache\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key: ");
                scanf("%d", &userKey);
                printf("Enter value: ");
                scanf("%d", &userValue);
                put(cache, userKey, userValue);
                break;
            case 2:
                printf("Enter key to retrieve: ");
                scanf("%d", &userKey);
                userValue = get(cache, userKey);
                if (userValue != -1) {
                    printf("Value for key %d: %d\n", userKey, userValue);
                } else {
                    printf("Key %d not found in cache.\n", userKey);
                }
                break;
            case 3:
                displayCache(cache);
                break;
            case 4:
                printf("Exiting...\n");
                free(cache->hashTable);  // Free hash table memory
                free(cache);  // Free cache memory
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
