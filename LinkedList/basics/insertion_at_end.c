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
    return head;            //it will return all the nodes creted 
                            // to the variable assigned in function calling
}

int main() {
    struct node *head = NULL;
    head=insert_at_end(head, 10);
    head=insert_at_end(head, 20);
    head=insert_at_end(head, 30);
    head=insert_at_end(head, 40);
    head=insert_at_end(head, 50);
    display_list(head);
}
