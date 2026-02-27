/*
Verify that the expression getchar() != EOF is 0 or 1.
*/

#include <stdio.h>
#define NEWLINE '\n'

main() {
    int c;
    int b1;
    int b2;
    
    c = getchar();
    b1 = (c != EOF);
    b2 = (c != NEWLINE);

    while (b1) {
        printf("%d\n", b1);
        printf("%d\n", b2);
        c = getchar();
        b1 = (c != EOF);
        b2 = (c != NEWLINE);
    }

    printf("%d\n", b1);
    printf("%d\n", b2);
}