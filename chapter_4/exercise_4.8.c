/*
Suppose that there will never be more than one character of pushback.
Modify getch and ungetch accordingly.
*/

// they're fine as is, just need to use BUFSIZE == 1.
#include <stdio.h>
#define BUFSIZE 1

char buffer[BUFSIZE];
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
    int c1 = getch();
    ungetch(c1);
    int c2 = getch();
    printf("c1: %c, c2: %c\n", c1, c2);

    ungetch(c2);
    int c3 = getch();
    printf("c1: %c, c2: %c, c3: %c\n", c1, c2, c3);
}
