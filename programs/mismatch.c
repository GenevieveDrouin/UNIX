
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../fio/fio.h"

#define WORD_MAX 1024

// Comparison function for qsort and bsearch
static int cmp_str(const void *a, const void *b) {
    const char *sa = *(const char * const *)a;
    const char *sb = *(const char * const *)b;
    size_t n = strlen(sa) > strlen(sb) ? strlen(sa) : strlen(sb);
    return strncmp(sa, sb, n + 1);
}

// Load dictionary and sort it once
static char **dict = NULL;
static size_t dict_count = 0;

// Load dictionary from file
static void load_dict(const char *filename) {
    // Open dictionary file
    FILE *fp = openFile(filename);
    if (!fp) {
        perror("Failed to open unix_dict.text");
        exit(1);
    }

    // Read words into dynamic array
    size_t capacity = 128;
    dict = malloc(capacity * sizeof(char *));
    if (!dict) { perror("malloc failed"); exit(1); }

    // Read lines
    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';
        if (dict_count >= capacity) {
            capacity *= 2;
            char **tmp = realloc(dict, capacity * sizeof(char *));
            if (!tmp) { perror("realloc failed"); exit(1); }
            dict = tmp;
        }
        dict[dict_count++] = strdup(line);
    }

    // Close file
    fclose(fp);

    // Sort dictionary for binary search
    qsort(dict, dict_count, sizeof(char *), cmp_str);
}

char* mismatch(const char* text) {
    // Load dictionary if not already loaded
    if (!dict) load_dict("unix_dict.text");

    // Trim newline
    char word[1024];
    strncpy(word, text, sizeof(word) - 1);
    word[sizeof(word)-1] = '\0';
    word[strcspn(word, "\n")] = '\0';

    // Binary search dictionary
    char *key = word;
    char **found = bsearch(&key, dict, dict_count, sizeof(char *), cmp_str);

    if (!found) {
        // Word missing → return with newline
        size_t len = strlen(word);
        char *result = malloc(len + 2);
        if (!result) exit(1);
        sprintf(result, "%s\n", word);
        return result;
    } else {
        // Found → return empty string
        return strdup("");
    }
}

int main(void) {
    // Buffer for reading lines
    char buffer[1024];

    // Read from stdin and process each line
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char* mismatched = mismatch(buffer);
        fputs(mismatched, stdout);
        free(mismatched);
    }
    return 0;
}