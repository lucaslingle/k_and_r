/*
Add commands to print top element of the stack without popping, 
to duplicate it, and to swap the top two positions. 
Add a command to clear the stack. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100 // max number of operands/operators
#define NUMBER '0' // indicates encountered a number

double myatof(char []);

void push(double);
double pop(void);
void peek(void);
void dupe(void);
void swap(void);
void clear(void);

int getch(void);
void ungetch(int);
int getop(char []);

#define STACKSIZE 100 // max stack depth for calculator
double stack[STACKSIZE];
int sp = 0;

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

// reverse polish calculator
int main() {
    int type;
    double op2;
    double op1;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(myatof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '%':
            op2 = pop();
            op1 = pop();
            if ((op2 != 0.0) && (op2 == (int) op2) && (op1 == (int) op1))
                push((int) op1 % (int) op2);
            else if (op2 == 0)
                printf("error: zero modulus\n");
            else 
                printf("error: modulus operator requires integer operands\n");
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

double myatof(char s[]) {
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
        return 0.0;
    }
}

void peek(void) {
    if (sp > 0)
        printf("%f", stack[sp - 1]);
    else
        printf("error: stack empty\n");
}

void dupe(void) {
    if (sp > 0) {
        push(stack[sp - 1]);
    } else {
       printf("error: stack empty\n");
    }
}

void swap(void) {
    double v1, v2;
    if (sp > 1) {
        v2 = pop();
        v1 = pop();
        push(v2);
        push(v1);
    } else {
       printf("error: stack empty\n");
    }
}

void clear(void) {
    sp = 0;
}

int getop(char s[]) {
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-')
        return c;
    i = 0;
    if (c == '-' || isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
           ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
