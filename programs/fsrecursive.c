#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>


// Recursive function to traverse directories
void list_dirs(const char *path, FILE *out) {
    // Open directory
    DIR *dir = opendir(path);
    if (!dir) return;  // skip if cannot open

    // Read entries
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".."
        if (strncmp(entry->d_name, ".", 1) == 0 || strncmp(entry->d_name, "..", 2) == 0){
            continue;
        }
        
        // Build full path
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(fullpath, &st) == 0 && S_ISDIR(st.st_mode)) {
            // Print folder name
            fprintf(out, "%s\n", fullpath);
            printf("%s\n", fullpath);

            // Recurse into subdirectory
            list_dirs(fullpath, out);
        }
    }
    closedir(dir);
}

int main(void) {
    char startdir[1024];

    // Open input file (fsrecursion_start.text)
    FILE *in = fopen("fsrecursion_start.text", "r");
    if (!in) {
        perror("Could not open fsrecursion_start.text");
        return 1;
    }
    if (!fgets(startdir, sizeof(startdir), in)) {
        fprintf(stderr, "Failed to read start directory\n");
        fclose(in);
        return 1;
    }
    fclose(in);

    // Trim newline
    startdir[strcspn(startdir, "\r\n")] = '\0';

    // Open output file (fsrecursion_output.text)
    FILE *out = fopen("fsrecursion_output.text", "w");
    if (!out) {
        perror("Could not open fsrecursion_output.text");
        return 1;
    }

    // Print starting directory itself
    fprintf(out, "%s\n", startdir);
    printf("%s\n", startdir);

    // Recurse into subdirectories
    list_dirs(startdir, out);

    fclose(out);
    return 0;
}