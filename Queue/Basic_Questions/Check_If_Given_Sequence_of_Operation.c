#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to check if the sequence of operations is valid
int isValidOperationSequence(const char* operations) {
    int queueSize = 0; // To track the current size of the queue

    // Traverse the sequence of operations
    for (int i = 0; i < strlen(operations); i++) {
        if (operations[i] == 'E') { // Enqueue operation
            queueSize++;
        } else if (operations[i] == 'D') { // Dequeue operation
            if (queueSize == 0) { // Dequeue not possible if queue is empty
                return 0;
            }
            queueSize--;
        } else {
            // Invalid character in the sequence
            return 0;
        }
    }
    return 1; // Sequence is valid if all conditions are satisfied
}

// Main function
int main() {
    char* operations = NULL;
    size_t bufferSize = 0;

    printf("Enter the sequence of operations (E for Enqueue, D for Dequeue): ");
    getline(&operations, &bufferSize, stdin);

    // Remove the newline character if present
    operations[strcspn(operations, "\n")] = '\0';

    if (isValidOperationSequence(operations)) {
        printf("The sequence of operations is valid for a queue.\n");
    } else {
        printf("The sequence of operations is not valid for a queue.\n");
    }

    // Free dynamically allocated memory
    free(operations);

    return 0;
}
