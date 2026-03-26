/*
Our getch and ungetch do not handle a pushed-back EOF correctly.
Decide what their properties ought to be if an EOF is pushed back,
then implement your design. 
*/

// if we assume the user is juggling characters intelligently,
// we can treat EOF like any other character for implementation purposes.
// the only change is that EOF is not a char, but is an int, so buffer must be int type.
//
// an alternative would be to flush the buffer once an EOF is encountered, 
// but if user is juggling characters correctly they will encounter chars in original order 
// during getch calls, so the buffer should already be empty after getching the EOF from it. 

#include <stdio.h>
#define BUFSIZE 100

int buffer[BUFSIZE];
int bp = 0;

int getch(void) {
    return (bp > 0) ? buffer[--bp] : getchar();
}

void ungetch(int c) {
    if (bp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buffer[bp++] = c;
}

int main() {
    int c1 = EOF;
    ungetch(c1);
    int c2 = getch();
    printf("c1: %d, c2: %d\n", c1, c2);
}
