#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Merge function
static void merge(char **arr, size_t left, size_t mid, size_t right) {
    // Sizes of two subarrays
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;

    // Create temp arrays
    char **L = malloc(n1 * sizeof(char*));
    char **R = malloc(n2 * sizeof(char*));

    // Copy data to temp arrays
    for (size_t i = 0; i < n1; i++) L[i] = arr[left + i];
    for (size_t i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    // Merge the temp arrays back into arr[left..right]
    size_t i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        size_t n = strlen(L[i]) > strlen(R[j]) ? strlen(L[i]) : strlen(R[j]);
        if (strncmp(L[i], R[j], n + 1) <= 0) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    // Copy remaining elements
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    // Free temp arrays
    free(L);
    free(R);
}

// Merge sort function
static void mergeSort(char **arr, size_t left, size_t right) {
    // Base case
    if (left < right) {
        // Find the middle point
        size_t mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Sort function
char* sort(const char* text) {
    // Duplicate input text
    char *copy = strdup(text);
    if (!copy) return NULL;

    // Split into line pointers
    size_t capacity = 16, count = 0;
    char **lines = malloc(capacity * sizeof(char*));
    if (!lines) { free(copy); return NULL; }

    // Tokenize lines
    char *ptr = copy;
    while (*ptr) {
        if (count >= capacity) {
            capacity *= 2;
            char **tmp = realloc(lines, capacity * sizeof(char*));
            if (!tmp) { free(lines); free(copy); return NULL; }
            lines = tmp;
        }
        lines[count++] = ptr;
        char *newline = strchr(ptr, '\n');
        if (!newline) break;
        *newline = '\0';
        ptr = newline + 1;
    }

    // Sort pointers
    if (count > 1) mergeSort(lines, 0, count - 1);

    // Build output string
    size_t outSize = 1;
    for (size_t i = 0; i < count; i++) outSize += strlen(lines[i]) + 1;

    // Allocate output buffer
    char *result = malloc(outSize);
    if (!result) { free(lines); free(copy); return NULL; }

    // Concatenate sorted lines
    size_t pos = 0;
    for (size_t i = 0; i < count; i++) {
        size_t len = strlen(lines[i]);
        memcpy(result + pos, lines[i], len);
        pos += len;
        result[pos++] = '\n';
    }

    // Null-terminate the result
    result[pos] = '\0';

    // Free temporary resources
    free(lines);
    free(copy);
    return result;
}

int main(void) {
    // Read entire input
    size_t bufSize = 1024, inputLen = 0;
    char *input = malloc(bufSize);
    if (!input) return 1;

    // Read input until EOF
    int c;
    while ((c = getchar()) != EOF) {
        if (inputLen + 1 >= bufSize) {
            bufSize *= 2;
            char *tmp = realloc(input, bufSize);
            if (!tmp) { free(input); return 1; }
            input = tmp;
        }
        input[inputLen++] = c;
    }
    input[inputLen] = '\0';

    // Sort and print
    char *out = sort(input);
    if (out) {
        fputs(out, stdout);
        free(out);
    }

    // Free input buffer
    free(input);
    return 0;
}