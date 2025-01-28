#include <stdio.h>
#include <stdlib.h>

// Structure for tree node
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Structure for queue node
struct QueueNode {
    struct TreeNode *node;
    struct QueueNode *next;
};

struct QueueNode *front = NULL, *rear = NULL;

// Enqueue a tree node
void enqueue(struct TreeNode *node) {
    struct QueueNode *newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    newNode->node = node;
    newNode->next = NULL;

    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

// Dequeue a tree node
struct TreeNode *dequeue() {
    if (front == NULL) return NULL;

    struct QueueNode *temp = front;
    front = front->next;
    if (front == NULL) rear = NULL;

    struct TreeNode *node = temp->node;
    free(temp);
    return node;
}

// Create a new tree node
struct TreeNode *createTreeNode(int data) {
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Build the binary tree from level order input
struct TreeNode *buildTreeFromLevelOrder() {
    int data;
    printf("Enter the root node value (-1 for NULL): ");
    scanf("%d", &data);

    if (data == -1) return NULL;

    struct TreeNode *root = createTreeNode(data);
    enqueue(root);

    while (front != NULL) {
        struct TreeNode *parent = dequeue();

        printf("Enter the left child of %d (-1 for NULL): ", parent->data);
        scanf("%d", &data);
        if (data == -1) {
            parent->left = NULL;
        } else {
            parent->left = createTreeNode(data);
            enqueue(parent->left);
        }

        printf("Enter the right child of %d (-1 for NULL): ", parent->data);
        scanf("%d", &data);
        if (data == -1) {
            parent->right = NULL;
        } else {
            parent->right = createTreeNode(data);
            enqueue(parent->right);
        }
    }

    return root;
}

// Calculate the maximum width of the binary tree
int maxWidth(struct TreeNode *root) {
    if (root == NULL) return 0;

    int maxWidth = 0;
    enqueue(root);
    int currentLevelNodes = 1;
    int nextLevelNodes = 0;

    while (front != NULL) {
        maxWidth = (maxWidth > currentLevelNodes) ? maxWidth : currentLevelNodes;

        struct TreeNode *node = dequeue();
        currentLevelNodes--;

        if (node->left) {
            enqueue(node->left);
            nextLevelNodes++;
        }

        if (node->right) {
            enqueue(node->right);
            nextLevelNodes++;
        }

        if (currentLevelNodes == 0) {
            currentLevelNodes = nextLevelNodes;
            nextLevelNodes = 0;
        }
    }

    return maxWidth;
}

int main() {
    printf("Build the binary tree using level-order input.\n");
    struct TreeNode *root = buildTreeFromLevelOrder();

    int width = maxWidth(root);
    printf("Maximum width of the binary tree: %d\n", width);

    return 0;
}
