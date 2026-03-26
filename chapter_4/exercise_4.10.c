/*
An alternate organization would be to use getline to read an entire input line. 
This makes getch and ungetch unnecessary. Revise the calculator to use this approach. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define NUMBER 0
#define SYMBOLIC_OPERATOR 1
#define NAMED_OPERATOR 2
#define WRITE_VARIABLE 3
#define READ_VARIABLE 4
#define READ_PRINTED 5
#define SPACE 6

#define MAXLINE 1000 // max num chars per line
#define MAXOP 100 // max length of an operator/operand
#define STACKSIZE 100 // max stack depth for calculator
#define BUFSIZE 100

double parse_double(char []);
void push(double);
double pop(void);
int _getline(char [], int);
int getop(char []);
double stack[STACKSIZE];
int sp = 0;
char buffer[BUFSIZE];
int bp = 0;

int eqs(char s1[], char s2[]) {
    return strcmp(s1, s2) == 0;
}

// reverse polish calculator
int main() {
    int type, offset, i;
    double op1, op2;
    char line[MAXLINE];
    char s[MAXOP];
    double v[26];
    double printed;

    while (1) {
        _getline(line, MAXLINE);
        offset = 0;
        while (offset < strlen(line)) {
            // printf("INFO: offset == %d\n", offset);
            if (isspace(line[offset])) {
                // printf("INFO: isspace(line[offset]) == 1\n");
                for (i=0; offset+i < strlen(line) && isspace(line[offset+i]); i++) {
                    s[i] = line[offset+i];
                }
                s[i] = '\0';
                offset += i;
            } else {
                // printf("INFO: isspace(line[offset]) == 0\n");
                for (i=0; offset+i < strlen(line) && !isspace(line[offset+i]); i++) {
                    s[i] = line[offset+i];
                }
                s[i] = '\0';
                offset += i;
            }
            // printf("INFO: s == %s\n", s);
            // printf("INFO strlen(s) == %lu\n", strlen(s));
            type = getop(s);

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
            case SPACE:
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
            }
        }
        if (sp > 0) {
            printed = pop();
            printf("\t%.8g\n", printed);
        }
    }
    return 0;
}

double parse_double(char s[]) {
    double val, power;
    int i, sign;
    for (i = 0; isspace(s[i]); i++)  // skip whitespace
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    return sign * val / power;
}

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

int _getline(char s[], int lim) {
    int i, c;
    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}

int getop(char s[]) {
    if (strlen(s) == 1 && s[0] == '_')
        return READ_PRINTED;
    if ((strlen(s) >= 1 && isdigit(s[0])) || (strlen(s) >= 2 && s[0] == '-'))
        return NUMBER;
    if (strlen(s) == 3 && s[0] == '=' && s[1] == ':' && isalpha(s[2]))
        return WRITE_VARIABLE;
    if (strlen(s) == 1 && isalpha(s[0]))
        return READ_VARIABLE;
    if (strlen(s) > 1 && isalpha(s[0]))
        return NAMED_OPERATOR;
    if (strlen(s) == 1 && !isspace(s[0]))
        return SYMBOLIC_OPERATOR;
    return SPACE;
}
