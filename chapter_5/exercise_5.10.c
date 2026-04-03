/*
Write the program expr, which evaluates a reverse Polish expression
from the command line, where each operator or operand is a separate argument.
For example,
    expr 2 3 4 + *
evaluates to 2 * (3 + 4). 

Stenographer's note: the times character is auto-expanded in shells to give 
all files in current directory, which means it must be escaped, which is ugly :(
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define STACKSIZE 100
static double stack[STACKSIZE];
static int sp = 0;
void push(double f) {
    if (sp < STACKSIZE) {
        stack[sp++] = f;
    } else {
        printf("error: stack full, can't push %g\n", f);
    }
}
double pop(void) {
    if (sp > 0)
        return stack[--sp];
    else {
        printf("error: stack empty\n");
        return 0xEEEEEEEE;
    }
}

#define NUMBER 0
int getop(char *src, char *dest) {
    char c = *src;
    if (isdigit(c)) {
        *dest++ = c;
        while (isdigit(c = *src++))
            *dest++ = c;
        if (c == '.') {
            *dest++ = '.';
            while (isdigit(c = *src++))
                *dest++ = c;
        }
        *dest = '\0';
        return NUMBER;
    } else {
        *dest++ = c;
        *dest = '\0';
        return c;
    }
}

double my_atof(char *s) {
    double val, power;
    int sign;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    for (val = 0.0; isdigit(*s); s++)
        val = 10.0 * val + (*s - '0');
    if (*s == '.')
        s++;
    for (power = 1.0; isdigit(*s); s++) {
        val = 10.0 * val + (*s - '0');
        power *= 10.0;
    }
    return sign * val / power;
}

#define MAXCHARS 100
int main(int argc, char *argv[]) {
    int t;
    char dest[MAXCHARS];
    double op1, op2;
    while (--argc > 0) {
        ++argv;
        t = getop(*argv, dest);
        switch (t) {
        case NUMBER:
            push(my_atof(argv[0]));
            break;
        case '+':
            op2 = pop();
            op1 = pop();
            push(op1 + op2);
            break;
        case '-':
            op2 = pop();
            op1 = pop();
            push(op1 - op2);
            break;
        case '*':
            op2 = pop();
            op1 = pop();
            push(op1 * op2);
            break;
        case '/':
            op2 = pop();
            op1 = pop();
            push(op1 / op2);
            break;
        default:
            printf("error: unrecognized op: %c\n", t);
            break;
        }
    }
    printf("%lf\n", pop());
    return 0;
}
