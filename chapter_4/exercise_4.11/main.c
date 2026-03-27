#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "calc.h"
#define MAXOP 100 // max number of operands/operators

int eqs(char s1[], char s2[]) {
    return strcmp(s1, s2) == 0;
}

// reverse polish calculator
int main() {
    int type;
    double op2;
    double op1;
    char s[MAXOP];
    double v[26];
    double printed;

    while ((type = getop(s)) != EOF) {
        // printf("INFO: type == %d\n", type);
        switch (type) {
        case NUMBER:
            // printf("INFO: NUMBER == %s\n", s);
            // printf("INFO: NUMBER len(s) == %lu\n", strlen(s));
            push(parse_double(s));
            break;
        case SYMBOLIC_OPERATOR:
            // printf("INFO: SYMBOLIC_OPERATOR == %s\n", s);
            // printf("INFO: SYMBOLIC_OPERATOR len(s) == %lu\n", strlen(s));
            op2 = pop();
            op1 = pop();
            if (eqs(s, "+")) {
                push(op1 + op2);
            } else if (eqs(s, "-")) {
                push(op1 - op2);
            } else if (eqs(s, "*")) {
                push(op1 * op2);
            } else if (eqs(s, "/")) {
                push(op1 / op2);
            } else if (eqs(s, "%")) {
                push((int) op1 % (int) op2);
            }
            break;
        case NAMED_OPERATOR:
            // printf("INFO: NAMED_OPERATOR == %s\n", s);
            // printf("INFO: NAMED_OPERATOR len(s) == %lu\n", strlen(s));
            // unary operators
            if (eqs(s, "sin")) {
                push(sin(pop()));
            } else if (eqs(s, "cos")) {
                push(cos(pop()));
            } else if (eqs(s, "tan")) {
                push(tan(pop()));
            } else if (eqs(s, "asin")) {
                push(asin(pop()));
            } else if (eqs(s, "acos")) {
                push(acos(pop()));
            } else if (eqs(s, "atan")) {
                push(atan(pop()));
            } else if (eqs(s, "sinh")) {
                push(sinh(pop()));
            } else if (eqs(s, "cosh")) {
                push(cosh(pop()));
            } else if (eqs(s, "tanh")) {
                push(tanh(pop()));
            } else if (eqs(s, "exp")) {
                push(exp(pop()));
            } else if (eqs(s, "log")) {
                push(log(pop()));
            } else if (eqs(s, "log10")) {
                push(log10(pop()));
            } else if (eqs(s, "sqrt")) {
                push(sqrt(pop()));
            } else if (eqs(s, "ceil")) {
                push(ceil(pop()));
            } else if (eqs(s, "floor")) {
                push(floor(pop()));
            } else if (eqs(s, "fabs")) {
                push(fabs(pop()));
            } else {
                // binary operators
                op2 = pop();
                op1 = pop();
                if (eqs(s, "atan2")) {
                    push(atan2(op2, op1));
                } else if (eqs(s, "pow")) {
                    push(pow(op1, op2));
                }
            }
            break;
        case WRITE_VARIABLE:
            // printf("INFO: WRITE_VARIABLE == %s\n", s);
            // printf("INFO: WRITE_VARIABLE len(s) == %lu\n", strlen(s));
            v[s[2] - 'a'] = pop();
            break;
        case READ_VARIABLE:
            // printf("INFO: READ_VARIABLE == %s\n", s);
            // printf("INFO: READ_VARIABLE len(s) == %lu\n", strlen(s));
            push(v[s[0] - 'a']);
            break;
        case READ_PRINTED:
            // printf("INFO: READ_PRINTED == %s\n", s);
            // printf("INFO: READ_PRINTED len(s) == %lu\n", strlen(s));
            push(printed);
            break;
        case NEWLINE:
            printed = pop();
            printf("\t%.8g\n", printed);
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}
