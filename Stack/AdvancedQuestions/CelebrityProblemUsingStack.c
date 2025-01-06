#include <stdio.h>
#include <stdlib.h>

int knows(int M[][4], int a, int b) {
    return M[a][b] == 1;
}

int findCelebrity(int** M, int n) {
    int* stack = (int*)malloc(n * sizeof(int));
    int top = -1;

    // Push all people to the stack
    for (int i = 0; i < n; i++) {
        stack[++top] = i;
    }

    // Find the celebrity candidate
    while (top > 0) {
        int personA = stack[top--];
        int personB = stack[top];
        if (knows(M, personA, personB)) {
            stack[top] = personB;
        } else {
            stack[top] = personA;
        }
    }

    int candidate = stack[0];
    // Verify the candidate
    for (int i = 0; i < n; i++) {
        if (i != candidate && knows(M, candidate, i)) {
            free(stack);
            return -1;
        }
        if (i != candidate && !knows(M, i, candidate)) {
            free(stack);
            return -1;
        }
    }

    free(stack);
    return candidate;
}

int main() {
    int n;
    
    // Take input for the number of people
    printf("Enter the number of people: ");
    scanf("%d", &n);

    // Dynamically allocate memory for the matrix
    int** M = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        M[i] = (int*)malloc(n * sizeof(int));
    }

    // Take input for the matrix
    printf("Enter the matrix (0 for no, 1 for yes):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &M[i][j]);
        }
    }

    int celebrity = findCelebrity(M, n);

    if (celebrity == -1) {
        printf("There is no celebrity.\n");
    } else {
        printf("Person %d is the celebrity.\n", celebrity);
    }

    // Free dynamically allocated memory
    for (int i = 0; i < n; i++) {
        free(M[i]);
    }
    free(M);

    return 0;
}
