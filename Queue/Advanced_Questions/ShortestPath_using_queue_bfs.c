#include <stdio.h>
#include <stdlib.h>


#define ROWS 5
#define COLS 5


int rowDirections[] = {-1, 1, 0, 0};  
int colDirections[] = {0, 0, -1, 1};  


struct Node {
    int row, col;
    int distance;
    struct Node* next;
};

struct Node* front = NULL;
struct Node* rear = NULL;

struct Node* createNode(int row, int col, int distance) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->row = row;
    newNode->col = col;
    newNode->distance = distance;
    newNode->next = NULL;
    return newNode;
}

int isEmpty() {
    return front == NULL;
}

void enqueue(int row, int col, int distance) {
    struct Node* newNode = createNode(row, col, distance);
    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}


struct Node* dequeue() {
    if (isEmpty()) {
        return NULL;
    }
    struct Node* temp = front;
    front = front->next;
    if (front == NULL) {
        rear = NULL;
    }
    return temp;
}

int isValid(int maze[ROWS][COLS], int visited[ROWS][COLS], int row, int col) {
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS &&
            maze[row][col] == 0 && !visited[row][col]);
}


int shortestPath(int maze[ROWS][COLS], int startRow, int startCol, int destRow, int destCol) {
    
    int visited[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            visited[i][j] = 0;
        }
    }


    enqueue(startRow, startCol, 0);
    visited[startRow][startCol] = 1;

    while (!isEmpty()) {
        struct Node* node = dequeue();
        int row = node->row;
        int col = node->col;
        int distance = node->distance;
        free(node);

        
        if (row == destRow && col == destCol) {
            return distance;
        }

        
        for (int i = 0; i < 4; i++) {
            int newRow = row + rowDirections[i];
            int newCol = col + colDirections[i];

            
            if (isValid(maze, visited, newRow, newCol)) {
                enqueue(newRow, newCol, distance + 1);
                visited[newRow][newCol] = 1;
            }
        }
    }

    
    return -1;
}

int main() {
    
    int maze[ROWS][COLS] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0}
    };

    int startRow, startCol, destRow, destCol;
    printf("Enter the start position (row col): ");
    scanf("%d %d", &startRow, &startCol);
    printf("Enter the destination position (row col): ");
    scanf("%d %d", &destRow, &destCol);

    int result = shortestPath(maze, startRow, startCol, destRow, destCol);

    if (result == -1) {
        printf("No path exists from start to destination.\n");
    } else {
        printf("The shortest path length is: %d\n", result);
    }

    return 0;
}
