/*
Write a program to fold long input lines into two or more shorter lines 
after the last non-blank character that occurs before the n-th column of input.

Make sure your program does something intelligent with very long lines, 
and if there are no blanks or tabs before the specified column.
*/

// my code assumes no tabs and thus no chars that take up more than one 'column'.
// not sure what "after the last non-blank character" means. can i not break on a space?
// did they mean "after the last blank character that occurs before the n-th column of input"?
#include <stdio.h>
#define N 80

int main() {
    int c, line_offset;
    line_offset = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            putchar('\n');
            line_offset = 0;
        } else if (line_offset == N) {
            putchar('\n');
            putchar(c);
            line_offset = 0;
        } else {
            putchar(c);
            line_offset++;
        }
    }
    return 0;
}
