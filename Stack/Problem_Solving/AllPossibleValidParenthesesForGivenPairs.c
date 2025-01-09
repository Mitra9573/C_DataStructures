#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to generate valid parentheses combinations
void generateParenthesesCombinations(int pairs, int openCount, int closeCount, char* currentCombination, int position, char** allCombinations, int* resultCount) {
    // Base case: If we've used all pairs of parentheses
    if (openCount == pairs && closeCount == pairs) {
        allCombinations[*resultCount] = (char*)malloc((2 * pairs + 1) * sizeof(char));
        strcpy(allCombinations[*resultCount], currentCombination);
        (*resultCount)++;
        return;
    }

    // Add an open parenthesis if we haven't used all of them
    if (openCount < pairs) {
        currentCombination[position] = '(';
        generateParenthesesCombinations(pairs, openCount + 1, closeCount, currentCombination, position + 1, allCombinations, resultCount);
    }

    // Add a close parenthesis if it won't make the combination invalid
    if (closeCount < openCount) {
        currentCombination[position] = ')';
        generateParenthesesCombinations(pairs, openCount, closeCount + 1, currentCombination, position + 1, allCombinations, resultCount);
    }
}

// Function to generate all valid parentheses combinations
char** generateAllValidParentheses(int pairs, int* combinationsCount) {
    // Allocate memory for storing combinations
    int maxCombinations = 1 << (2 * pairs);  // Maximum possible combinations
    char** allCombinations = (char**)malloc(maxCombinations * sizeof(char*));
    char* currentCombination = (char*)malloc((2 * pairs + 1) * sizeof(char));
    currentCombination[2 * pairs] = '\0';  // Null-terminate the string

    *combinationsCount = 0;
    generateParenthesesCombinations(pairs, 0, 0, currentCombination, 0, allCombinations, combinationsCount);

    free(currentCombination); // Free memory used for currentCombination
    return allCombinations;
}

// Main function to test the implementation
int main() {
    int pairs;  // Number of pairs of parentheses
    printf("Enter the number of pairs of parentheses: ");
    scanf("%d", &pairs);

    int combinationsCount;
    char** validParenthesesCombinations = generateAllValidParentheses(pairs, &combinationsCount);

    printf("Valid Parentheses combinations for %d pairs:\n", pairs);
    for (int i = 0; i < combinationsCount; i++) {
        printf("%s\n", validParenthesesCombinations[i]);
        free(validParenthesesCombinations[i]); // Free memory for each combination
    }
    free(validParenthesesCombinations); // Free memory for the array of combinations

    return 0;
}
