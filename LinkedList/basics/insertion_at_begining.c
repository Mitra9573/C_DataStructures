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
    printf("\n");
}
struct node* insert_at_beginning(struct node *head, int data) {
    struct node *new_node = create_node(data);  
    new_node->link = head;  //create aina node link ni head value tho update chestam
    head = new_node;    //head  ni insert method lo unde  new node lo unde value tho update chestam
    return new_node;    //new_node la irkura value return agum
}
int main() {
    struct node *head = NULL;
    head=insert_at_beginning(head, 10);
    head=insert_at_beginning(head, 20);
    head=insert_at_beginning(head, 30);
    head=insert_at_beginning(head, 40);
    head=insert_at_beginning(head, 50);
    display_list(head);
}
