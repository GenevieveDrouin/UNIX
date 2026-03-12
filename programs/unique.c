#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function that checks uniqueness against previous line
// Returns 1 if the line should be printed, 0 otherwise
int unique_line(const char *line, const char *prev) {
    if (!prev) return 1;
    size_t n = strlen(line) > strlen(prev) ? strlen(line) : strlen(prev);
    return strncmp(prev, line, n + 1) != 0;
}

int main(void) {
    // Variables for reading lines
    char *line = NULL;
    size_t len = 0;
    size_t read;
    char *prev = NULL;

    // Read lines from stdin and print unique lines to stdout
    while ((read = getline(&line, &len, stdin)) != -1) {
        // Remove trailing newline
        if (read > 0 && line[read-1] == '\n') {
            line[read-1] = '\0';
        }

        // Check if the line is unique and print if so
        if (unique_line(line, prev)) {
            printf("%s\n", line);
            free(prev);
            prev = strdup(line);  // remember last line
            if (!prev) { perror("strdup"); exit(1); }
        }
    }

    // Free allocated memory
    free(line);
    free(prev);
    return 0;
}