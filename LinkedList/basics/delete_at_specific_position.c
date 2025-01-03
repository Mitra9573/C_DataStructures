#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node
struct node {
    int data;
    struct node *link;
};

// Function to create a new node
struct node* create_node(int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    new_node->data = data;
    new_node->link = NULL;
    return new_node;
}

// Function to display the linked list
void display_list(struct node *head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    struct node *temp = head;
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->link;
    }
}

// Insert at the beginning
struct node* insert_at_beginning(struct node *head, int data) {
    struct node *new_node = create_node(data);
    new_node->link = head;
    head =new_node;
    return new_node;
}

// Insert at the end
struct node* insert_at_end(struct node *head, int data) {
    struct node *new_node = create_node(data);
    if (head == NULL) {
        return new_node;
    }
    struct node *temp = head;
    while (temp->link != NULL) {
        temp = temp->link;
    }
    temp->link = new_node;
    return head;
}

// Insert at a specific position
struct node* insert_at_position(struct node *head, int data, int position) {
    struct node *new_node = create_node(data);
    if (position == 1) {
        new_node->link = head;
        return new_node;
    }
    struct node *temp = head;
    int i;
    for (i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->link;
    }
    if (temp == NULL) {
        printf("Invalid position!\n");
        free(new_node);
        return head;
    }
    new_node->link = temp->link;
    temp->link = new_node;
    return head;
}

//delete from a specific position

struct node* delete_from_position(struct node *head, int position) {
    if (head == NULL) {
        printf("The list is empty. Nothing to delete.\n");
        return NULL;
    }
    if (position == 1) { // Delete the head node
        struct node *temp = head;
        head = head->link;
        free(temp);
        return head;
    }
    struct node *temp = head;
    struct node *prev = NULL;
	int i;
    for (i = 1; i < position && temp != NULL; i++) {
        prev = temp;
        temp = temp->link;
    }

    if (temp == NULL) { // Position is out of bounds
        printf("Invalid position!\n");
        return head;
    }

    prev->link = temp->link; // Unlink the node
    free(temp);
    return head;
}


// Main function
int main() {
struct node *head = NULL;
int choice, data, position;
while (1) {
    printf("\nMenu:\n");
    printf("1. Insert at the beginning\n");
    printf("2. Insert at the end\n");
    printf("3. Insert at a specific position\n");
    printf("4. Delete From specific position\n");
    printf("5. Display Linked List\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("Enter the value to insert at the beginning: ");
            scanf("%d", &data);
            head = insert_at_beginning(head, data);
            break;
        case 2:
            printf("Enter the value to insert at the end: ");
            scanf("%d", &data);
            head = insert_at_end(head, data);
            break;
        case 3:
            printf("Enter the value to insert: ");
            scanf("%d", &data);
            printf("Enter the position: ");
            scanf("%d", &position);
            head = insert_at_position(head, data, position);
            break;
        case 4:
            printf("Enter the position: ");
            scanf("%d", &position);
            head = delete_from_position(head,position);
            printf("Deleted From position - %d",position);
            break;
        case 5:
            display_list(head);
            break;
        case 6:
            printf("Exiting the program.\n");
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
return 0;
}
