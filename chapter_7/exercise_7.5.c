/*
Rewrite the postfix calculator of Chapter 4 to use scanf
and/or sscanf to do the input and number conversion.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define NUMBER 0
#define STACKSIZE 100 // max stack depth for calculator

void push(double);
double pop(void);
double stack[STACKSIZE];
int sp = 0;

// reverse polish calculator
int main() {
    double op1, op2;
    char symbol;
    int ret;
    char type;
    int done = 0;

    while (!done) {
        ret = scanf("%lf ", &op1);
        type = NUMBER;
        if (ret != 1) {
            ret = scanf("%c ", &symbol);
            type = symbol;
        }

        switch (type) {
            case NUMBER:
                push(op1);
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
            case '\n':
                done = 1;
                break;
            case EOF:
                done = 1;
                break;
            default:
                printf("error: parsing failed there.\n");
                exit(1);
        }
        op1 = 0.0;
        op2 = 0.0;
        symbol = EOF;
    }
    printf("Answer: \n%lf\n", pop());
    return 0;
}

void push(double f) {
    if (sp < STACKSIZE) {
        stack[sp++] = f;
    } else {
        printf("error: stack full, can't push %g.\n", f);
        exit(2);
    }
}

double pop(void) {
    if (sp > 0)
        return stack[--sp];
    else {
        printf("error: stack empty.\n");
        exit(3);
    }
}
