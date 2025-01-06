#include <stdio.h>
#include <stdlib.h>

// Function to calculate the maximum area of a rectangle in the histogram
int maxRectangleArea(int *heights, int barCount) {
    // Dynamically allocated stack
    int *stack = (int *)malloc(barCount * sizeof(int));
    int top = -1;
    int maxArea = 0;
    int area, i;

    // Iterate through each bar
    for (i = 0; i < barCount;) {
        // If the stack is empty or the current bar is taller than the bar at the top of the stack
        if (top == -1 || heights[stack[top]] <= heights[i]) {
            stack[++top] = i++; // Push the current bar index to the stack
        } else {
            // Pop the top bar and calculate the area with the popped bar as the shortest bar
            int tp = stack[top--];
            area = heights[tp] * (top == -1 ? i : i - stack[top] - 1);
            if (area > maxArea) {
                maxArea = area; // Update max area if a larger area is found
            }
        }
    }

    // Process any remaining bars in the stack
    while (top != -1) {
        int tp = stack[top--];
        area = heights[tp] * (top == -1 ? i : i - stack[top] - 1);
        if (area > maxArea) {
            maxArea = area; // Update max area
        }
    }

    free(stack); // Free dynamically allocated memory for the stack
    return maxArea;
}

int main() {
    int barCount;

    // Get dynamic input for the number of bars
    printf("Enter the number of bars in the histogram: ");
    scanf("%d", &barCount);

    // Dynamically allocate memory for histogram heights
    int *heights = (int *)malloc(barCount * sizeof(int));

    // Get dynamic input for the heights of the histogram bars
    printf("Enter the heights of the histogram bars:\n");
    for (int i = 0; i < barCount; i++) {
        scanf("%d", &heights[i]);
    }

    // Call the function to calculate the largest rectangle area
    int largestArea = maxRectangleArea(heights, barCount);
    printf("The largest rectangular area is: %d\n", largestArea);

    // Free the dynamically allocated memory for heights
    free(heights);

    return 0;
}
