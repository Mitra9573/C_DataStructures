#include <stdio.h>
#include <stdlib.h>

void computeStockSpan(int* priceArray, int size) {
    int* spanArray = (int*)malloc(size * sizeof(int)); // Array to store span values
    int* indexStack = (int*)malloc(size * sizeof(int)); // Stack to hold indices
    int stackTop = -1; // Initialize the stack top

    for (int currentIndex = 0; currentIndex < size; currentIndex++) {
        // Remove elements from the stack while the current price is higher
        // than the price at the index stored on top of the stack
        while (stackTop >= 0 && priceArray[indexStack[stackTop]] <= priceArray[currentIndex]) {
            stackTop--;
        }

        // Compute span for the current index
        if (stackTop == -1) {
            spanArray[currentIndex] = currentIndex + 1;
        } else {
            spanArray[currentIndex] = currentIndex - indexStack[stackTop];
        }

        // Push the current index onto the stack
        indexStack[++stackTop] = currentIndex;
    }

    // Print the computed stock span values
    printf("Stock span values:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", spanArray[i]);
    }
    printf("\n");

    // Free allocated memory
    free(spanArray);
    free(indexStack);
}

int main() {
    int size;

    printf("Enter the number of stock prices: ");
    scanf("%d", &size);

    int* stockPrices = (int*)malloc(size * sizeof(int));

    if (stockPrices == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter the stock prices:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &stockPrices[i]);
    }

    computeStockSpan(stockPrices, size);

    // Free allocated memory
    free(stockPrices);

    return 0;
}
