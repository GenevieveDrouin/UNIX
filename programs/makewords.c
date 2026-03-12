#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to replace spaces with newlines
char* makewords(const char* input) {
    // Allocate memory for the output string
    size_t len = strlen(input);
    char* result = malloc(len + 1);
    if (!result) { perror("malloc failed"); exit(1); }

    // Replace spaces with newlines
    for (size_t i = 0; i < len; i++) {
        result[i] = (input[i] == ' ') ? '\n' : input[i];
    }

    // Null-terminate the output string
    result[len] = '\0';
    return result;
}

int main(void) {
    // Buffer to hold each line of input
    char buffer[1024];

    // Read from stdin and process each line
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Enter newline where there was a space and print the result
        char* result = makewords(buffer);
        fputs(result, stdout);
        free(result);
    }
    return 0;
}