#include <stdio.h>
#include <stdlib.h>

// Definition of a linked list node
struct ListNode {
    int value;
    struct ListNode* next;
};

// Definition of a binary tree node
struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new linked list node
struct ListNode* createListNode(int value) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new binary tree node
struct TreeNode* createTreeNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to find the middle node of the linked list
struct ListNode* findMiddle(struct ListNode* head, struct ListNode** prev) {
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    *prev = NULL;

    while (fast != NULL && fast->next != NULL) {
        *prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// Function to convert a sorted linked list into a balanced binary search tree
struct TreeNode* sortedListToBST(struct ListNode* head) {
    if (head == NULL) {
        return NULL;
    }

    struct ListNode* prev = NULL;
    struct ListNode* mid = findMiddle(head, &prev);

    // Create the root node with the middle element
    struct TreeNode* root = createTreeNode(mid->value);

    // If the middle element is the head, there is no left subtree
    if (mid == head) {
        root->left = NULL;
    } else {
        prev->next = NULL; // Break the list into two halves
        root->left = sortedListToBST(head); // Recursively construct the left subtree
    }

    root->right = sortedListToBST(mid->next); // Recursively construct the right subtree

    return root;
}

// Function to print the inorder traversal of the tree
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    printf("%d ", root->value);
    inorderTraversal(root->right);
}

// Function to print the preorder traversal of the tree
void preorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->value);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// Function to print the postorder traversal of the tree
void postorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->value);
}

// Function to get user input for a sorted linked list
struct ListNode* createUserList() {
    int n, value;
    struct ListNode *head = NULL, *tail = NULL;

    printf("Enter the number of elements in the sorted linked list: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &value);

        struct ListNode* newNode = createListNode(value);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    return head;
}

// Main function
int main() {
    // Create a sorted linked list dynamically
    printf("Create a sorted linked list:\n");
    struct ListNode* listHead = createUserList();

    // Convert the sorted linked list into a balanced binary search tree
    struct TreeNode* bstRoot = sortedListToBST(listHead);

    // Print the traversals of the binary search tree
    printf("\nInorder traversal of the constructed BST: ");
    inorderTraversal(bstRoot);
    printf("\n");

    printf("Preorder traversal of the constructed BST: ");
    preorderTraversal(bstRoot);
    printf("\n");

    printf("Postorder traversal of the constructed BST: ");
    postorderTraversal(bstRoot);
    printf("\n");

    return 0;
}
