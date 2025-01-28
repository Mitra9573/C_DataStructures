// Solve the "Rotten Oranges" problem using BFS with a queue.
#include<stdio.h>
#include<stdlib.h>

#define ROW 10
#define COL 10

struct QueueNode {
    int x, y, time;
    struct QueueNode *next;
} *head = NULL;

// Function to append a node to the queue
void enqueue(int x, int y, int time) {
    struct QueueNode *newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    newNode->x = x;
    newNode->y = y;
    newNode->time = time;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        struct QueueNode *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to dequeue a node from the queue
struct QueueNode* dequeue() {
    if (head == NULL) return NULL;
    struct QueueNode *temp = head;
    head = head->next;
    return temp;
}

// Check if the position is valid and fresh orange
int isValid(int x, int y, int grid[ROW][COL], int r, int c) {
    return (x >= 0 && y >= 0 && x < r && y < c && grid[x][y] == 1);
}

// BFS to find the minimum time to rot all oranges
int rottenOranges(int grid[ROW][COL], int r, int c) {
    int time = 0;
    int freshCount = 0;

    // Enqueue all initially rotten oranges
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == 2) {
                enqueue(i, j, 0);
            } else if (grid[i][j] == 1) {
                freshCount++;
            }
        }
    }

    // Directions for moving up, down, left, right
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    // Process the queue
    while (head != NULL) {
        struct QueueNode *node = dequeue();
        int x = node->x;
        int y = node->y;
        time = node->time;

        // Visit all adjacent cells
        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isValid(newX, newY, grid, r, c)) {
                grid[newX][newY] = 2; // Rot the fresh orange
                freshCount--;         // Decrease fresh orange count
                enqueue(newX, newY, time + 1);
            }
        }

        free(node);
    }

    // If there are still fresh oranges, return -1
    if (freshCount > 0) return -1;

    return time;
}

int main() {
    int grid[ROW][COL];
    int r, c;

    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &r, &c);

    printf("Enter the grid values (0 for empty, 1 for fresh orange, 2 for rotten orange):\n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int result = rottenOranges(grid, r, c);

    if (result == -1) {
        printf("Not all oranges can rot.\n");
    } else {
        printf("Minimum time required to rot all oranges: %d\n", result);
    }

    return 0;
}
