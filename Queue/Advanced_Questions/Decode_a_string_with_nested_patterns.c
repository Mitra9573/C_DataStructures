// Decode a string with nested patterns (e.g., "3[a2[c]]" -> "accaccacc") using a queue.
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Node structure for the queue
struct Node {
    char data;
    struct Node *next;
} *head = NULL;

// Append function to add elements to the queue
void append(char val) {
    struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
    newnode->data = val;
    newnode->next = NULL;

    if (head == NULL) {
        head = newnode;
    } else {
        struct Node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newnode;
    }
}

// Function to display the queue
void display() {
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%c", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to process the queue and decode the string
void decode_string() {
    char stack[1000]; // Stack for decoding
    int top = -1;     // Stack top pointer
    char result[1000]; // Final decoded string
    int res_index = 0; // Result string index

    struct Node *temp = head;

    while (temp != NULL) {
        char ch = temp->data;

        if (ch != ']') {
            // Push characters to the stack until ']'
            stack[++top] = ch;
        } else {
            // Decode the substring
            char decoded[1000];
            int dec_index = 0;

            // Pop until '[' is found
            while (stack[top] != '[') {
                decoded[dec_index++] = stack[top--];
            }
            decoded[dec_index] = '\0';
            top--; // Pop the '['

            // Reverse the substring
            for (int i = 0; i < dec_index / 2; i++) {
                char temp = decoded[i];
                decoded[i] = decoded[dec_index - i - 1];
                decoded[dec_index - i - 1] = temp;
            }

            // Get the number before '['
            char num_str[10];
            int num_index = 0;

            while (top >= 0 && isdigit(stack[top])) {
                num_str[num_index++] = stack[top--];
            }
            num_str[num_index] = '\0';

            // Reverse the number string
            for (int i = 0; i < num_index / 2; i++) {
                char temp = num_str[i];
                num_str[i] = num_str[num_index - i - 1];
                num_str[num_index - i - 1] = temp;
            }

            int repeat = atoi(num_str);

            // Repeat the substring
            for (int i = 0; i < repeat; i++) {
                for (int j = 0; j < dec_index; j++) {
                    stack[++top] = decoded[j];
                }
            }
        }

        temp = temp->next;
    }

    // Build the result string
    while (top >= 0) {
        result[res_index++] = stack[top--];
    }
    result[res_index] = '\0';

    // Reverse the result
    for (int i = 0; i < res_index / 2; i++) {
        char temp = result[i];
        result[i] = result[res_index - i - 1];
        result[res_index - i - 1] = temp;
    }

    printf("Decoded String: %s\n", result);
}

int main() {
    char str[1000];
    printf("Enter the encoded string (e.g., 3[a2[c]]): ");
    scanf("%s", str);

    // Add the string to the queue
    for (int i = 0; i < strlen(str); i++) {
        append(str[i]);
    }

    // Display the queue
    printf("Input Queue: ");
    display();

    // Decode the string
    decode_string();

    return 0;
}
