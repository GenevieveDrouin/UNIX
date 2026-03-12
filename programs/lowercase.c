#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <stdio.h>
#include <ctype.h>

int main(void) {
    // Read characters from standard input until EOF and convert to lowercase
    int c;
    while ((c = getchar()) != EOF) {
        putchar(tolower(c));
    }
    return 0;
}

