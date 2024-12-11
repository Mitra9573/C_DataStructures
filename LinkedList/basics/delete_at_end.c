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
void display(struct node *head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    struct node *temp = head;
    printf("Linked List: ");
    while (temp != NULL) {          //we have to get the data till last node
        printf("%d ", temp->data);  //so that we are not comparing with the link
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
    while (temp->link != NULL) {    //to find the last node
        temp = temp->link;          //will upadte the new node address in last node link
    }
    temp->link = new_node;
    return head;            //it will return all the nodes created
}

//delete from the end

struct node* delete_from_end(struct node *head) {
    if (head == NULL) {
        printf("The list is empty. Nothing to delete.\n");
        return NULL;
    }
    if (head->link == NULL) { // Only one node in the list
        free(head);     //removes the value stored in the variable
        return NULL;
    }
    struct node *temp = head;
    struct node *prev = NULL;
    while (temp->link != NULL) { // Traverse to the last node
        prev = temp;
        temp = temp->link;
    }
    prev->link = NULL; // Disconnect the last node
    free(temp);
    return head;
}


// Main function
int main() {
struct node *head = NULL;
head = insert_at_end(head,10);
head = insert_at_end(head,20);
head = insert_at_end(head,30);  
head = insert_at_end(head,40);
display(head);
head=delete_from_end(head);
printf("\n");
display(head);
return 0;
}
