#include <stdio.h>
#include "calc.h"
#define STACKSIZE 100 // max stack depth for calculator

static double stack[STACKSIZE];
static int sp = 0;

void push(double f) {
    // printf("INFO: pre-push sp == %d\n", sp);
    if (sp < STACKSIZE) {
        stack[sp++] = f;
    } else {
        printf("error: stack full, can't push %g\n", f);
    }
}

double pop(void) {
    // printf("INFO: pre-pop sp == %d\n", sp);
    if (sp > 0)
        return stack[--sp];
    else {
        printf("error: stack empty\n");
        return 0xEEEEEEEE;
    }
}
