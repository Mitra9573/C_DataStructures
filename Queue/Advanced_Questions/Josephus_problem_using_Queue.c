// Use a queue to solve the Josephus problem.
#include <stdio.h>
#include <stdlib.h>

// Node structure for the queue
struct Node {
    int data;
    struct Node *next;
} *head = NULL, *tail = NULL;

// Append function to add elements to the queue
void append(int val) {
    struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
    newnode->data = val;
    newnode->next = NULL;

    if (head == NULL) {
        head = tail = newnode;
        tail->next = head; // Circular connection
    } else {
        tail->next = newnode;
        tail = newnode;
        tail->next = head; // Maintain circular nature
    }
}

// Function to display the elements in the queue
void display() {
    if (head == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    struct Node *temp = head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

// Function to solve the Josephus problem
int josephus(int k) {
    struct Node *current = head;
    struct Node *prev = NULL;

    while (current->next != current) {
        // Traverse k-1 nodes to find the node to remove
        for (int i = 1; i < k; i++) {
            prev = current;
            current = current->next;
        }

        // Remove the k-th node
        prev->next = current->next;
        printf("Eliminated: %d\n", current->data);
        free(current);
        current = prev->next;
    }

    head = current; // The last remaining node is the safe position
    return current->data;
}

int main() {
    int n, k, val;

    // Input for the number of people
    printf("Enter the number of people in the circle (n): ");
    scanf("%d", &n);

    // Input for the step count
    printf("Enter the step count (k): ");
    scanf("%d", &k);

    // Input for the people in the circle
    printf("Enter the identifiers of the people (enter -1 to stop):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        if (val == -1)
            break;
        append(val);
    }

    // Display the initial queue
    printf("Initial Circle:\n");
    display();

    // Solve the Josephus problem
    int safe_position = josephus(k);
    printf("The safe position is: %d\n", safe_position);

    return 0;
}
