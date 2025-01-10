#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLS 1000

// Function to find the largest rectangle area in a histogram
int largestRectangleArea(int* heights, int colCount) {
    int maxArea = 0;
    int stack[MAX_COLS];
    int top = -1;
    
    for (int i = 0; i < colCount; i++) {
        while (top >= 0 && heights[stack[top]] > heights[i]) {
            int h = heights[stack[top--]];  
            int w = (top == -1) ? i : i - stack[top] - 1;
            maxArea = (maxArea > h * w) ? maxArea : h * w;
        }
        stack[++top] = i;
    }
    
    // Calculate the area for remaining bars in stack
    while (top >= 0) {
        int h = heights[stack[top--]];
        int w = (top == -1) ? colCount : colCount - stack[top] - 1;
        maxArea = (maxArea > h * w) ? maxArea : h * w;
    }
    
    return maxArea;
}

// Function to calculate the maximal rectangle area in a binary matrix
int maximalRectangle(char** matrix, int rowCount, int colCount) {
    int* heights = (int*)calloc(colCount, sizeof(int));
    int maxArea = 0;
    
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            if (matrix[i][j] == '1') {
                heights[j]++;
            } else {
                heights[j] = 0;
            }
        }
        
        maxArea = (maxArea > largestRectangleArea(heights, colCount)) ? maxArea : largestRectangleArea(heights, colCount);
    }
    
    free(heights);
    return maxArea;
}

int main() {
    int rowCount, colCount;
    
    // Dynamic input for rows and columns
    printf("Enter number of rows: ");
    scanf("%d", &rowCount);
    printf("Enter number of columns: ");
    scanf("%d", &colCount);

    // Dynamically allocate memory for the matrix
    char** matrix = (char**)malloc(rowCount * sizeof(char*));
    for (int i = 0; i < rowCount; i++) {
        matrix[i] = (char*)malloc((colCount + 1) * sizeof(char)); // +1 for the null-terminator
    }
    
    // Input the binary matrix row by row
    printf("Enter the binary matrix row by row (only '0' and '1'):\n");
    for (int i = 0; i < rowCount; i++) {
        printf("Row %d: ", i + 1);
        scanf("%s", matrix[i]);
    }

    // Calculate the maximal rectangle area
    int result = maximalRectangle(matrix, rowCount, colCount);
    printf("The maximum rectangle area is: %d\n", result);

    // Free the dynamically allocated memory for the matrix
    for (int i = 0; i < rowCount; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return 0;
}
