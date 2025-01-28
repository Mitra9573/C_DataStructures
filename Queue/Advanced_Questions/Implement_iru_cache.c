#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a doubly linked list node
typedef struct Node {
    int key, value;
    struct Node* prev;
    struct Node* next;
} Node;

// Define the hash map structure
typedef struct HashMap {
    Node** table;
    int capacity;
} HashMap;

// Define the LRU Cache structure
typedef struct LRUCache {
    int capacity;
    int size;
    HashMap* hashMap;
    Node* head;
    Node* tail;
} LRUCache;

// Function to create a new node
Node* createNode(int key, int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->prev = node->next = NULL;
    return node;
}

// Function to create a hash map
HashMap* createHashMap(int capacity) {
    HashMap* hashMap = (HashMap*)malloc(sizeof(HashMap));
    hashMap->table = (Node**)calloc(capacity, sizeof(Node*));
    hashMap->capacity = capacity;
    return hashMap;
}

// Hash function for the hash map
int hashFunction(int key, int capacity) {
    return key % capacity;
}

// Function to insert a node into the hash map
void hashMapInsert(HashMap* hashMap, int key, Node* node) {
    int index = hashFunction(key, hashMap->capacity);
    hashMap->table[index] = node;
}

// Function to retrieve a node from the hash map
Node* hashMapGet(HashMap* hashMap, int key) {
    int index = hashFunction(key, hashMap->capacity);
    return hashMap->table[index];
}

// Function to remove a node from the hash map
void hashMapRemove(HashMap* hashMap, int key) {
    int index = hashFunction(key, hashMap->capacity);
    hashMap->table[index] = NULL;
}

// Function to create an LRU Cache
LRUCache* createLRUCache(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->size = 0;
    cache->hashMap = createHashMap(capacity);
    cache->head = createNode(0, 0);  // Dummy head
    cache->tail = createNode(0, 0);  // Dummy tail
    cache->head->next = cache->tail;
    cache->tail->prev = cache->head;
    return cache;
}

// Function to remove a node from the doubly linked list
void removeNode(Node* node) {
    Node* prev = node->prev;
    Node* next = node->next;
    prev->next = next;
    next->prev = prev;
}

// Function to add a node to the end of the doubly linked list
void addNodeToEnd(LRUCache* cache, Node* node) {
    Node* prev = cache->tail->prev;
    prev->next = node;
    node->prev = prev;
    node->next = cache->tail;
    cache->tail->prev = node;
}

// Function to move a node to the end of the doubly linked list
void moveToTail(LRUCache* cache, Node* node) {
    removeNode(node);
    addNodeToEnd(cache, node);
}

// Function to get a value from the LRU Cache
int get(LRUCache* cache, int key) {
    Node* node = hashMapGet(cache->hashMap, key);
    if (!node) {
        return -1; // Key not found
    }
    moveToTail(cache, node); // Mark as recently used
    return node->value;
}

// Function to put a key-value pair into the LRU Cache
void put(LRUCache* cache, int key, int value) {
    Node* node = hashMapGet(cache->hashMap, key);

    if (node) {
        // Key exists, update the value and mark as recently used
        node->value = value;
        moveToTail(cache, node);
    } else {
        // Key does not exist
        if (cache->size == cache->capacity) {
            // Cache is full, evict the least recently used item
            Node* lru = cache->head->next;
            hashMapRemove(cache->hashMap, lru->key);
            removeNode(lru);
            free(lru);
            cache->size--;
        }
        // Insert the new key-value pair
        Node* newNode = createNode(key, value);
        hashMapInsert(cache->hashMap, key, newNode);
        addNodeToEnd(cache, newNode);
        cache->size++;
    }
}

// Function to free the LRU Cache
void freeLRUCache(LRUCache* cache) {
    Node* current = cache->head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(cache->hashMap->table);
    free(cache->hashMap);
    free(cache);
}

// Main function to test the LRU Cache
int main() {
    int capacity;
    printf("Enter the capacity of the LRU Cache: ");
    scanf("%d", &capacity);

    LRUCache* cache = createLRUCache(capacity);
    
    while (1) {
        int choice, key, value;
        printf("\n1. Put (key, value)\n2. Get (key)\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key and value: ");
                scanf("%d %d", &key, &value);
                put(cache, key, value);
                printf("Inserted (key=%d, value=%d) into the cache.\n", key, value);
                break;
            case 2:
                printf("Enter key: ");
                scanf("%d", &key);
                value = get(cache, key);
                if (value == -1) {
                    printf("Key %d not found in the cache.\n", key);
                } else {
                    printf("Value for key %d: %d\n", key, value);
                }
                break;
            case 3:
                freeLRUCache(cache);
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
