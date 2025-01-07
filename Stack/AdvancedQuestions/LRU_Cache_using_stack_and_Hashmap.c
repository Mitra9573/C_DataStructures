#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    int value;
} CacheItem;

typedef struct {
    CacheItem **cacheStack;  // Dynamic array for the stack (cache items)
    int *hashTable;          // Hash table for quick lookup
    int capacity;            // Maximum capacity of the cache
    int currentSize;         // Current size of the cache
    int topIndex;            // Index of the top item in the stack
} LRUCache;

void initializeCache(LRUCache *cache, int capacity) {
    cache->capacity = capacity;
    cache->currentSize = 0;
    cache->topIndex = -1;
    
    // Dynamically allocate memory for the cache stack (array of CacheItem pointers)
    cache->cacheStack = (CacheItem **)malloc(capacity * sizeof(CacheItem *));
    
    // Dynamically allocate memory for the hash table (for key lookup)
    cache->hashTable = (int *)malloc(capacity * sizeof(int));
    memset(cache->hashTable, -1, capacity * sizeof(int)); // Initialize with -1 (indicating empty)
}

int hashFunction(int key, int capacity) {
    return key % capacity;
}

int findItemInCacheStack(LRUCache *cache, int key) {
    for (int i = 0; i <= cache->topIndex; i++) {
        if (cache->cacheStack[i]->key == key) {
            return i;
        }
    }
    return -1;
}

void moveToTop(LRUCache *cache, int index) {
    CacheItem *temp = cache->cacheStack[index];
    for (int i = index; i < cache->topIndex; i++) {
        cache->cacheStack[i] = cache->cacheStack[i + 1];
    }
    cache->cacheStack[cache->topIndex] = temp;
}

void put(LRUCache *cache, int key, int value) {
    int hashIndex = hashFunction(key, cache->capacity);
    
    if (cache->hashTable[hashIndex] != -1 && cache->cacheStack[cache->hashTable[hashIndex]]->key == key) {
        cache->cacheStack[cache->hashTable[hashIndex]]->value = value;
        int stackIndex = findItemInCacheStack(cache, key);
        moveToTop(cache, stackIndex);
        return;
    }
    
    if (cache->currentSize == cache->capacity) {
        CacheItem *lruItem = cache->cacheStack[0];
        int lruHashIndex = hashFunction(lruItem->key, cache->capacity);
        cache->hashTable[lruHashIndex] = -1;

        for (int i = 0; i < cache->topIndex; i++) {
            cache->cacheStack[i] = cache->cacheStack[i + 1];
        }
        cache->topIndex--;
        cache->currentSize--;
    }

    CacheItem *newItem = (CacheItem *)malloc(sizeof(CacheItem));
    newItem->key = key;
    newItem->value = value;

    cache->topIndex++;
    cache->cacheStack[cache->topIndex] = newItem;
    cache->hashTable[hashIndex] = cache->topIndex;
    cache->currentSize++;
}

int get(LRUCache *cache, int key) {
    int hashIndex = hashFunction(key, cache->capacity);
    if (cache->hashTable[hashIndex] != -1 && cache->cacheStack[cache->hashTable[hashIndex]]->key == key) {
        int stackIndex = findItemInCacheStack(cache, key);
        moveToTop(cache, stackIndex);
        return cache->cacheStack[cache->hashTable[hashIndex]]->value;
    }
    return -1;
}

void printCache(LRUCache *cache) {
    printf("Cache state (top to bottom):\n");
    for (int i = cache->topIndex; i >= 0; i--) {
        printf("Key: %d, Value: %d\n", cache->cacheStack[i]->key, cache->cacheStack[i]->value);
    }
    printf("\n");
}

void freeCache(LRUCache *cache) {
    for (int i = 0; i <= cache->topIndex; i++) {
        free(cache->cacheStack[i]);
    }
    free(cache->cacheStack);
    free(cache->hashTable);
}

int main() {
    LRUCache cache;
    int capacity;
    printf("Enter the capacity of the LRU cache: ");
    scanf("%d", &capacity);

    initializeCache(&cache, capacity);

    int choice, key, value;
    while (1) {
        printf("\n1. Put\n2. Get\n3. Print Cache\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter key and value: ");
            scanf("%d %d", &key, &value);
            put(&cache, key, value);
            break;
        case 2:
            printf("Enter key: ");
            scanf("%d", &key);
            value = get(&cache, key);
            if (value != -1) {
                printf("Value: %d\n", value);
            } else {
                printf("Key not found in cache.\n");
            }
            break;
        case 3:
            printCache(&cache);
            break;
        case 4:
            freeCache(&cache);
            exit(0);
        default:
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
