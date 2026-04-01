#include <stdio.h>
#include "getint.h"
#define BUFSIZE 100

static char buffer[BUFSIZE];
static int bp = 0;

int getch(void) {
    return (bp > 0) ? buffer[--bp] : getchar();
}

void ungetch(int c) {
    if (bp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buffer[bp++] = c;
}
