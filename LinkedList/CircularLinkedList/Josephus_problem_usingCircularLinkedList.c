/*
Problem Description
Imagine there are N people standing in a circle, numbered from 1 to N. Starting from a given position (e.g., person 1), you count off k people, and the k-th person is eliminated from the circle. The counting then resumes from the next person, and the process continues until only one person remains. The goal is to determine the position of the last survivor.

Example
Input:

Number of people, N = 5
Step rate, k = 2
Process:

People: 1 -> 2 -> 3 -> 4 -> 5 (in a circle)
Start counting from 1:
Eliminate person 2
Remaining: 1 -> 3 -> 4 -> 5
Eliminate person 5
Remaining: 1 -> 3 -> 4
Eliminate person 1
Remaining: 3 -> 4
Eliminate person 3
Remaining: 4
Output:

Survivor: 4

*/
#include <stdio.h>
#include <stdlib.h>

struct Person {
    int id;
    struct Person* next;
};

// Function to create a new person node
struct Person* createPerson(int id) {
    struct Person* newPerson = (struct Person*)malloc(sizeof(struct Person));
    if (newPerson == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newPerson->id = id;
    newPerson->next = NULL;
    return newPerson;
}

// Function to create the circular linked list representing people
struct Person* createCircle(int N) {
    struct Person* firstPerson = NULL;
    struct Person* lastPerson = NULL;

    for (int i = 1; i <= N; i++) {
        struct Person* newPerson = createPerson(i);
        if (firstPerson == NULL) {
            firstPerson = newPerson;
            firstPerson->next = firstPerson; // Points to itself to form a circle
        } else {
            lastPerson->next = newPerson;
            newPerson->next = firstPerson; // Connects back to the first person
        }
        lastPerson = newPerson;
    }
    return firstPerson;
}

// Function to solve the Josephus problem
int josephusCircle(struct Person** circle, int k) {
    struct Person* current = *circle;
    struct Person* previous = NULL;

    // Loop until only one person remains
    while (current->next != current) {
        // Count k people and eliminate the k-th person
        for (int i = 1; i < k; i++) {
            previous = current;
            current = current->next;
        }
        previous->next = current->next; // Skip over the eliminated person
        printf("Eliminated: %d\n", current->id);
        free(current);
        current = previous->next; // Move to the next person
    }

    *circle = current; // The last remaining person
    return current->id;
}

int main() {
    int N, k;

    // Get the number of people and step rate from the user
    printf("Enter the number of people (N): ");
    scanf("%d", &N);
    printf("Enter the step rate (k): ");
    scanf("%d", &k);

    // Create the circular linked list
    struct Person* circle = createCircle(N);

    // Solve the Josephus problem and print the survivor
    int survivor = josephusCircle(&circle, k);
    printf("The last survivor is: %d\n", survivor);

    // Free the remaining person (although it's just one person left)
    free(circle);

    return 0;
}
