#include <stdio.h>
#include <stdlib.h>

void computeNextLarger(int* inputArray, int size, int* outputArray) {
    int* tempStack = (int*)malloc(size * sizeof(int));
    int stackIndex = -1; // Initialize stack index to empty

    for (int currentIndex = size - 1; currentIndex >= 0; currentIndex--) {
        // Remove elements from stack that are smaller or equal to the current element
        while (stackIndex != -1 && tempStack[stackIndex] <= inputArray[currentIndex]) {
            stackIndex--;
        }

        // Assign the next larger element or -1 if no such element exists
        if (stackIndex == -1) {
            outputArray[currentIndex] = -1;
        } else {
            outputArray[currentIndex] = tempStack[stackIndex];
        }

        // Push the current element onto the stack
        tempStack[++stackIndex] = inputArray[currentIndex];
    }

    free(tempStack); // Free allocated memory for the stack
}

int main() {
    int arraySize;
    printf("Enter the size of the array: ");
    scanf("%d", &arraySize);

    int* inputArray = (int*)malloc(arraySize * sizeof(int));
    int* outputArray = (int*)malloc(arraySize * sizeof(int));

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < arraySize; i++) {
        scanf("%d", &inputArray[i]);
    }

    computeNextLarger(inputArray, arraySize, outputArray);

    printf("Next Larger Elements:\n");
    for (int i = 0; i < arraySize; i++) {
        printf("%d -> %d\n", inputArray[i], outputArray[i]);
    }

    free(inputArray); // Free allocated memory for the input array
    free(outputArray); // Free allocated memory for the output array

    return 0;
}
