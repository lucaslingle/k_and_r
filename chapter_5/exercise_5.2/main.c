/*
Write getfloat, the floating-point analog of getint. 
What type does getfloat return as its function value?
*/

#include <stdio.h>
#include "getfloat.h"

int main(void) {
    double x;
    if (getfloat(&x))
        printf("%lf\n", x);
}
