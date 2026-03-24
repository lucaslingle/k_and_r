/*
Add commands for handling variables. 
(It's easy to provide twenty-six variables with single-letter names.)
Add a variable for the most recently printed value. 
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
#define NEWLINE 6

#define MAXOP 100 // max number of operands/operators
#define STACKSIZE 100 // max stack depth for calculator
#define BUFSIZE 100

double parse_double(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
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


int getop(char s[]) {
    int i = 0;
    int c, type;
    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '_') {
        type = READ_PRINTED;
    } else if (c == '-' || isdigit(c)) {
        s[0] = c;
        while (isdigit(c = getch()))
            s[++i] = c;
        if (c == '.') {
            s[++i] = '.';
            while (isdigit(c = getch()))
                s[++i] = c;
        }
        if (c != EOF)
            ungetch(c);
        type = NUMBER;
    } else if ((c == '=') && (getch() == ':') && isalpha(c = getch())) {
        s[0] = '=';
        s[++i] = ':';
        s[++i] = c;
        type = WRITE_VARIABLE;
    } else if (isalpha(c)) {
        s[0] = c;
        while (isalpha(c = getch()))
            s[++i] = c;
        if (c != EOF)
            ungetch(c);
        if (i == 0) {
            type = READ_VARIABLE;
        } else {
            type = NAMED_OPERATOR;
        }
    } else if (!isspace(c)) {
        s[0] = c;
        type = SYMBOLIC_OPERATOR;
    } else if (c == '\n') {
        type = NEWLINE;
    } else {
        type = EOF;
    }
    s[++i] = '\0';
    return type;
}

int getch(void) {
    return (bp > 0) ? buffer[--bp] : getchar();
}

void ungetch(int c) {
    if (bp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buffer[bp++] = c;
}
