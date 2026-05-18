/*
Write a private version of scanf analogous to minprintf 
from the previous section.
*/

#include <stdarg.h>
#include <stdio.h>

int minscanf(char *fmt, ...) {
    va_list ap;
    int n = 0;
    int v;
    int c;

    va_start(ap, fmt);
    for (; *fmt; fmt++) {
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
            if (v == EOF)
                return EOF;
            else if (v == 0)
                return n;
            else
                n++;
            break;
        case 'i':
            v = scanf("%i", va_arg(ap, int *));
            if (v == EOF)
                return EOF;
            else if (v == 0)
                return n;
            else
                n++;
            break;
        case 'o':
            v = scanf("%o", va_arg(ap, int *));
            if (v == EOF)
                return EOF;
            else if (v == 0)
                return n;
            else
                n++;
            break;
        case 'x':
            v = scanf("%x", va_arg(ap, int *));
            if (v == EOF)
                return EOF;
            else if (v == 0)
                return n;
            else
                n++;
            break;
        case 'u':
            v = scanf("%u", va_arg(ap, unsigned *));
            if (v == EOF)
                return EOF;
            else if (v == 0)
                return n;
            else
                n++;
            break;
        case 'c':
            v = scanf("%c", va_arg(ap, char *));
            if (v == EOF)
                return EOF;
            else if (v == 0)
                return n;
            else
                n++;
            break;
        case 's':
            v = scanf("%s", va_arg(ap, char *));
            if (v == EOF)
                return EOF;
            else if (v == 0)
                return n;
            else
                n++;
            break;
        case 'e':
            v = scanf("%e", va_arg(ap, float *));
            if (v == EOF)
                return EOF;
            else if (v == 0)
                return n;
            else
                n++;
            break;
        case 'f':
            v = scanf("%f", va_arg(ap, float *));
            if (v == EOF)
                return EOF;
            else if (v == 0)
                return n;
            else
                n++;
            break;
        case 'g':
            v = scanf("%g", va_arg(ap, float *));
            if (v == EOF)
                return EOF;
            else if (v == 0)
                return n;
            else
                n++;
            break;
        default:
            break;
        }
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

    // scanf("%i %o %x %u %c %s %f\n", &ival, &oval, &xval, &uval, &cval, sval, &fval);
    // printf("%i\n", ival);
    // printf("%o\n", oval);
    // printf("%x\n", xval);
    // printf("%u\n", uval);
    // printf("%c\n", cval);
    // printf("%s\n", sval);
    // printf("%f\n", fval);

    int ret = minscanf("%i %o %x %u %c %s %f %%\n", &ival, &oval, &xval, &uval, &cval, sval, &fval);
    printf("ret = %d\n", ret);
    printf("%i\n", ival);
    printf("%o\n", oval);
    printf("%x\n", xval);
    printf("%u\n", uval);
    printf("%c\n", cval);
    printf("%s\n", sval);
    printf("%f\n", fval);
}
