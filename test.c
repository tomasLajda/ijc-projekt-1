#include <stdio.h>

// This is a single-line comment

/*
This is a multi-line comment.
It can span multiple lines,
and it may contain special characters like *, /, \, etc.
*/

int main() {
    // Single-line comment inside code block
    printf("Hello, world!\n");

    // Double-quote string
    char *str = "This is a double-quote string.";
    printf("%s\n", str);

    // Single-quote string
    char c = 'A';
    printf("%c\n", c);

    /* Another multi-line comment
    spanning multiple lines */

    /*
    * This is a multi-line comment with
    * asterisks at the beginning of each line.
    */

    return 0;
}
