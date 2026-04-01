#include <stdio.h>
#include <ctype.h>
#include "getfloat.h"

int getfloat(double *px) {
    double val, power;
    int c, sign;
    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) {
            ungetch(c);
            return 0;
        }
    }
    for (val = 0.0; isdigit(c); c = getch())
        val = 10.0 * val + (c - '0');
    if (c == '.')
        c = getch();
    for (power = 1.0; isdigit(c); c = getch()) {
        val = 10.0 * val + (c - '0');
        power *= 10.0;
    }
    *px = sign * val / power;
    if (c != EOF)
        ungetch(c);
    return 1;
}