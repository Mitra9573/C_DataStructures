#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 1000

// Function to decode the string based on the pattern
char* decodeString(char* inputStr) {
    // Dynamically allocate memory for the stack to hold characters and integers
    char* stack = (char*)malloc(MAX_SIZE * sizeof(char));
    int stackIndex = -1; 
    int inputLength = strlen(inputStr);
    int num = 0; // To store the number of repetitions

    // Traverse the input string
    for (int i = 0; i < inputLength; i++) {
        if (isdigit(inputStr[i])) {
            // Build the number for the number of repetitions
            num = num * 10 + (inputStr[i] - '0');
        } else if (inputStr[i] == '[') {
            // Push the number and '[' onto the stack
            stack[++stackIndex] = num;
            num = 0; 
            stack[++stackIndex] = '['; 
        } else if (inputStr[i] == ']') {
            // Process the content within the brackets
            char temp[MAX_SIZE];
            int tempIndex = 0;
            while (stack[stackIndex] != '[') {
                temp[tempIndex++] = stack[stackIndex--];
            }
            stackIndex--;  // Discard the '[' character
            temp[tempIndex] = '\0'; // Null-terminate the string

            // Reverse the content inside the temp array
            for (int k = 0; k < tempIndex / 2; k++) {
                char tempChar = temp[k];
                temp[k] = temp[tempIndex - k - 1];
                temp[tempIndex - k - 1] = tempChar;
            }

            // Get the number of repetitions
            int repeatCount = stack[stackIndex--];
            
            // Push the decoded substring back onto the stack repeated 'repeatCount' times
            for (int k = 0; k < repeatCount; k++) {
                for (int m = 0; m < tempIndex; m++) {
                    stack[++stackIndex] = temp[m];
                }
            }
        } else {
            // If it's a letter, push it onto the stack
            stack[++stackIndex] = inputStr[i];
        }
    }

    // Allocate memory for the final decoded string
    char* decodedStr = (char*)malloc((stackIndex + 2) * sizeof(char));
    for (int i = 0; i <= stackIndex; i++) {
        decodedStr[i] = stack[i];
    }
    decodedStr[stackIndex + 1] = '\0'; // Null-terminate the result string

    // Free the memory used by the stack
    free(stack);

    return decodedStr;
}

int main() {
    char* encodedStr = (char*)malloc(MAX_SIZE * sizeof(char));  // Dynamically allocate memory for the input string

    printf("Enter the encoded string: ");
    fgets(encodedStr, MAX_SIZE, stdin);  // Use fgets to handle dynamic input
    encodedStr[strcspn(encodedStr, "\n")] = '\0';  // Remove the newline character at the end of the input

    char* decodedStr = decodeString(encodedStr);
    printf("Decoded string: %s\n", decodedStr);

    // Free the dynamically allocated memory
    free(encodedStr);
    free(decodedStr);

    return 0;
}
