/*
How would you test the word count program?

Ideas:
\EOF -> 0,0,0
A\EOF -> 0,1,1
AA\EOF -> 0,1,2
AAA\EOF -> 0,1,3
ABC\EOF -> 0,1,3
ABC DEF\EOF -> 0,2,7
ABC DEF GHIJKL\EOF -> 0,3,14
aBc deF ghiJkl -> 0,3,14
*/

#include <stdio.h>

#define IN  0  // inside a word
#define OUT 1  // outside a word

main() {
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    printf("\n%d %d %d\n", nl, nw, nc);
}
