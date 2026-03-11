/*
Write a program to remove all comments from a C program.
Don't forget to handle quoted strings and character constants properly.
C comments do not nest. 
*/

#include <stdio.h>
#define OUTSIDE_OUTQUOTE 0
#define OUTSIDE_INQUOTE 1
#define INSIDE_INLINE 2
#define INSIDE_MULTILINE 3

int main() {
    int state, ctm2, ctm1, ct;
    state = OUTSIDE_OUTQUOTE;
    ctm2 = EOF;
    ctm1 = EOF;
    while ((ct = getchar()) != EOF) {
        if ((state == OUTSIDE_OUTQUOTE) && (ct != '"') && (ctm1 != '/' || ct != '/') && (ctm1 != '/' || ct != '*')) {
            state = OUTSIDE_OUTQUOTE;
            if (ctm2 != EOF) {
                putchar(ctm2);
            }
            ctm2 = ctm1;
            ctm1 = ct;
        } else if ((state == OUTSIDE_OUTQUOTE) && (ct == '"')) {
            state = OUTSIDE_INQUOTE;
            if (ctm2 != EOF) {
                putchar(ctm2);
            }
            ctm2 = ctm1;
            ctm1 = ct;
        } else if ((state == OUTSIDE_OUTQUOTE) && (ctm1 == '/' && ct == '/')) {
            state = INSIDE_INLINE;
            if (ctm2 != EOF) {
                putchar(ctm2);
            }
            ctm2 = EOF;
            ctm1 = EOF;
        } else if ((state == OUTSIDE_OUTQUOTE) && (ctm1 == '/' && ct == '*')) {
            state = INSIDE_MULTILINE;
            if (ctm2 != EOF) {
                putchar(ctm2);
            }
            ctm2 = EOF;
            ctm1 = EOF;
        } else if ((state == OUTSIDE_INQUOTE) && (ct != '"')) {
            state = OUTSIDE_INQUOTE;
            if (ctm2 != EOF) {
                putchar(ctm2);
            }
            ctm2 = ctm1;
            ctm1 = ct;
        } else if ((state == OUTSIDE_INQUOTE) && (ct == '"')) {
            state = OUTSIDE_OUTQUOTE;
            if (ctm2 != EOF) {
                putchar(ctm2);
            }
            ctm2 = ctm1;
            ctm1 = ct;
        } else if ((state == INSIDE_INLINE) && (ct == '\n')) {
            state = OUTSIDE_OUTQUOTE;
            ctm2 = EOF;
            ctm1 = EOF;
        } else if ((state == INSIDE_MULTILINE) && (ctm1 == '*' || ct == '/')) {
            state = OUTSIDE_OUTQUOTE;
            ctm2 = EOF;
            ctm1 = EOF;
        }
    }
    if (ctm2 != EOF) {
        putchar(ctm2);
    }
    if (ctm1 != EOF) {
        putchar(ctm1);
    }
    return 0;
}