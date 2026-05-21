/*
Write a private version of scanf analogous to minprintf 
from the previous section.
*/

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int minscanf(char *fmt, ...) {
    va_list ap;
    int n = 0;
    int v;
    int c;

    va_start(ap, fmt);
    for (; *fmt; fmt++) {
        if (*fmt == ' ' || *fmt == '\t')
            continue;
        if (*fmt != '%') {
            c = getc(stdin);
            if (c == EOF)
                return EOF;
            else if (c != *fmt) {
                ungetc(c, stdin);
                return n;
            } else
                continue;
        }
        switch (*++fmt) {
        case 'd':
            v = scanf("%d", va_arg(ap, int *));
            break;
        case 'i':
            v = scanf("%i", va_arg(ap, int *));
            break;
        case 'o':
            v = scanf("%o", va_arg(ap, int *));
            break;
        case 'x':
            v = scanf("%x", va_arg(ap, int *));
            break;
        case 'u':
            v = scanf("%u", va_arg(ap, unsigned *));
            break;
        case 'c':
            // we cant use %1s here because the terminal null byte 
            // can be written onto something else we care about...
            // on my machine it was written onto the uval passed by main().
            while (isspace(c = getc(stdin)))
                ;
            ungetc(c, stdin);
            v = scanf("%c", va_arg(ap, char *));
            break;
        case 's':
            v = scanf("%s", va_arg(ap, char *));
            break;
        case 'e':
            v = scanf("%e", va_arg(ap, float *));
            break;
        case 'f':
            v = scanf("%f", va_arg(ap, float *));
            break;
        case 'g':
            v = scanf("%g", va_arg(ap, float *));
            break;
        case '*':
            v = 2;
            break;
        case '%':
            c = getc(stdin);
            if (c == EOF)
                return EOF;
            else if (c != *fmt) {
                ungetc(c, stdin);
                return n;
            } else
                continue;
        default:
            fprintf(stderr, "minscanf got bad string format percent %c\n", *fmt);
            exit(1);
        }
        if (v == EOF)
            return EOF;
        else if (v == 0)
            return n;
        else if (v == 1)
            n++;
    }
    va_end(ap);
    return n;
}

int main() {
    int ival;
    int oval;
    int xval;
    unsigned uval;

    char cval;
    char sval[50];
    float fval;

    // int ret = scanf("abc%i  %o %x %u %c %s %f\n", &ival, &oval, &xval, &uval, &cval, sval, &fval);
    // printf("ret = %d\n", ret);
    // printf("%i\n", ival);
    // printf("%o\n", oval);
    // printf("%x\n", xval);
    // printf("%u\n", uval);
    // printf("%c\n", cval);
    // printf("%s\n", sval);
    // printf("%f\n", fval);

    int ret = minscanf("abc%i  %o\t%x %u %c %s %f %%\n", &ival, &oval, &xval, &uval, &cval, sval, &fval);
    printf("ret = %d\n", ret);
    printf("%i\n", ival);
    printf("%o\n", oval);
    printf("%x\n", xval);
    printf("%u\n", uval);
    printf("%c\n", cval);
    printf("%s\n", sval);
    printf("%f\n", fval);
}
