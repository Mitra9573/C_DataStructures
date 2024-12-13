#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node
struct node {
    int data;
    struct node *link;
};

// Function to create a new node
struct node* create_node(int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node)); //Based on 
    // our struct size memory allocate agum in case fail achi na NULL assign agum
    // To know that memory allocated or not we are using the below condition.
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
struct node* insert_at_position(struct node *head, int data, int position) {
    struct node *new_node = create_node(data);
    if (position == 1) {
        new_node->link = head;
        return new_node;
    }
    struct node *temp = head;
    int i;
    for ( i = 1; i < position - 1 && temp != NULL; i++) {
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
int main() {
    struct node *head = NULL;
    head=insert_at_position(head,10,1);
    head=insert_at_position(head,30,2);
    head=insert_at_position(head,50,3);
    head=insert_at_position(head,40,4);
    head=insert_at_position(head,20,5);
    display_list(head);
}
