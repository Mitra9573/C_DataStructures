#include <stdio.h>
#include <stdlib.h>

// Structure for a stack node
struct StackNode {
    int x, y;
    struct StackNode* next;
};

// Function to create a new stack node
struct StackNode* createNode(int x, int y) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->x = x;
    newNode->y = y;
    newNode->next = NULL;
    return newNode;
}

// Push an element to the stack
void push(struct StackNode** top, int x, int y) {
    struct StackNode* newNode = createNode(x, y);
    newNode->next = *top;
    *top = newNode;
    
}

// Pop an element from the stack
void pop(struct StackNode** top) {
    if (*top == NULL) return;
    struct StackNode* temp = *top;
    *top = (*top)->next;
    free(temp);
}

// Check if the stack is empty
int isEmpty(struct StackNode* top) {
    return top == NULL;
}

// Get the top element of the stack
struct StackNode* top(struct StackNode* stack) {
    return stack;
}

// Function to check if a cell is valid and part of the island
int isValid(int** grid, int** visited, int x, int y, int rows, int cols) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 1 && !visited[x][y]);
}

// Perform DFS using a stack
int dfs(int** grid, int** visited, int startX, int startY, int rows, int cols) {
    int area = 0;
    int rowOffsets[] = {-1, 1, 0, 0};
    int colOffsets[] = {0, 0, -1, 1};

    struct StackNode* stack = NULL;
    push(&stack, startX, startY);

    while (!isEmpty(stack)) {
        struct StackNode* current = top(stack);
        int x = current->x;
        int y = current->y;
        pop(&stack);

        if (!visited[x][y]) {
            visited[x][y] = 1;
            area++;

            // Explore neighbors
            for (int i = 0; i < 4; i++) {
                int newX = x + rowOffsets[i];
                int newY = y + colOffsets[i];
                if (isValid(grid, visited, newX, newY, rows, cols)) {
                    push(&stack, newX, newY);
                }
            }
        }
    }

    return area;
}

// Find the maximum area of an island
int maxAreaOfIsland(int** grid, int rows, int cols) {
    int** visited = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        visited[i] = (int*)malloc(cols * sizeof(int));
    }

    // Initialize the visited array to 0
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            visited[i][j] = 0;
        }
    }

    int maxArea = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1 && !visited[i][j]) {
                int area = dfs(grid, visited, i, j, rows, cols);
                if (area > maxArea) {
                    maxArea = area;
                }
            }
        }
    }

    // Free visited array
    for (int i = 0; i < rows; i++) {
        free(visited[i]);
    }
    free(visited);

    return maxArea;
}

int main() {
    int rows, cols;

    // Input for the grid dimensions
    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    printf("Enter the number of columns: ");
    scanf("%d", &cols);

    // Dynamically allocate memory for the grid
    int** grid = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        grid[i] = (int*)malloc(cols * sizeof(int));
    }

    // Input for the grid values (0 or 1)
    printf("Enter the grid values (0 for water, 1 for land):\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    // Call the function to find the maximum area of an island
    printf("Maximum area of an island: %d\n", maxAreaOfIsland(grid, rows, cols));

    // Free dynamically allocated memory
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}
