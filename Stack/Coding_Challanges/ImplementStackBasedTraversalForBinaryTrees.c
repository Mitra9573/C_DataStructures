#include <stdio.h>
#include <stdlib.h>

// Define a binary tree node structure
typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

// Create a new tree node with dynamic input
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Define a stack structure
typedef struct Stack {
    Node** nodes;
    int top;
    int capacity;
} Stack;

// Create a stack with dynamic memory allocation
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->nodes = (Node**)malloc(capacity * sizeof(Node*));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

// Push an element onto the stack
void push(Stack* stack, Node* node) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack overflow.\n");
        return;
    }
    stack->nodes[++stack->top] = node;
}

// Pop an element from the stack
Node* pop(Stack* stack) {
    if (stack->top == -1) {
        return NULL;
    }
    return stack->nodes[stack->top--];
}

// Check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Free the stack
void freeStack(Stack* stack) {
    free(stack->nodes);
    free(stack);
}

// Preorder traversal (root -> left -> right) using a stack
void preorderTraversal(Node* root) {
    if (!root) return;

    Stack* stack = createStack(100);
    push(stack, root);

    while (!isEmpty(stack)) {
        Node* currentNode = pop(stack);
        printf("%d ", currentNode->value);

        // Push right child first so left child is processed first
        if (currentNode->right) push(stack, currentNode->right);
        if (currentNode->left) push(stack, currentNode->left);
    }

    freeStack(stack);
}

// Inorder traversal (left -> root -> right) using a stack
void inorderTraversal(Node* root) {
    if (!root) return;

    Stack* stack = createStack(100);
    Node* currentNode = root;

    while (!isEmpty(stack) || currentNode != NULL) {
        // Reach the leftmost node of the current node
        while (currentNode != NULL) {
            push(stack, currentNode);
            currentNode = currentNode->left;
        }

        // Current must be NULL at this point
        currentNode = pop(stack);
        printf("%d ", currentNode->value);

        // Visit the right subtree
        currentNode = currentNode->right;
    }

    freeStack(stack);
}

// Postorder traversal (left -> right -> root) using a stack
void postorderTraversal(Node* root) {
    if (!root) return;

    Stack* stack1 = createStack(100);
    Stack* stack2 = createStack(100);

    push(stack1, root);

    // Push nodes into the first stack and process them into the second stack
    while (!isEmpty(stack1)) {
        Node* currentNode = pop(stack1);
        push(stack2, currentNode);

        if (currentNode->left) push(stack1, currentNode->left);
        if (currentNode->right) push(stack1, currentNode->right);
    }

    // Pop all nodes from the second stack to get postorder traversal
    while (!isEmpty(stack2)) {
        printf("%d ", pop(stack2)->value);
    }

    freeStack(stack1);
    freeStack(stack2);
}

// Function to insert a node in the binary tree dynamically
Node* insertNode(Node* root, int value) {
    Node* newNode = createNode(value);
    if (!root) {
        return newNode;
    }

    Node* currentNode = root;
    Node* parentNode = NULL;

    while (currentNode != NULL) {
        parentNode = currentNode;
        if (value < currentNode->value) {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }
    }

    if (value < parentNode->value) {
        parentNode->left = newNode;
    } else {
        parentNode->right = newNode;
    }

    return root;
}

int main() {
    Node* root = NULL;
    int nodeValue, numNodes;

    printf("Enter the number of nodes you want to insert into the binary tree: ");
    scanf("%d", &numNodes);

    for (int i = 0; i < numNodes; i++) {
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &nodeValue);
        root = insertNode(root, nodeValue);
    }

    printf("\nPreorder Traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorderTraversal(root);
    printf("\n");

    return 0;
}
