/*
Revise minprintf to handle more of the other facilities of printf.

#include <stdarg.h>
#include <stdio.h>
void minprintf(char *fmt, ...) {
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;

    va_start(ap, fmt);
    for (p = fmt, *p; p++) {
        if (*p != '%') {
            putchar(c);
            continue;
        }
        switch (*++p) {
        case 'd':
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
        case 's':
            for (sval = va_arg(ap, char *); *sval; sval++)
                putchar(*sval);
            break;
        default:
            putchar(*p);
            break;
        }
    }
    va_end(ap);
}
*/

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
void minprintf(char *fmt, ...) {
    va_list ap;

    int dval;
    unsigned uval;
    char *sval;
    double fval;
    void *pv_val;
    int *pn_val;
    int n;

    va_start(ap, fmt);
    for (; *fmt; fmt++) {
        if (*fmt != '%') {
            n += printf("%c", *fmt);
            continue;
        }
        switch (*++fmt) {
        case 'd':
            dval = va_arg(ap, int);
            n += printf("%d", dval);
            break;
        case 'i':
            dval = va_arg(ap, int);
            n += printf("%i", dval);
            break;
        case 'o':
            dval = va_arg(ap, int);
            n += printf("%o", dval);
            break;
        case 'x':
            dval = va_arg(ap, int);
            n += printf("%x", dval);
            break;
        case 'X':
            dval = va_arg(ap, int);
            n += printf("%X", dval);
            break;
        case 'u':
            uval = va_arg(ap, unsigned);
            n += printf("%u", uval);
            break;
        case 'c':
            dval = va_arg(ap, int);
            n += printf("%c", dval);
            break;
        case 's':
            sval = va_arg(ap, char *);
            n += printf("%s", sval);
            break;
        case 'f':
            fval = va_arg(ap, double);
            n += printf("%f", fval);
            break;
        case 'e':
            fval = va_arg(ap, double);
            n += printf("%e", fval);
            break;
        case 'E':
            fval = va_arg(ap, double);
            n += printf("%E", fval);
            break;
        case 'g':
            fval = va_arg(ap, double);
            n += printf("%g", fval);
            break;
        case 'G':
            fval = va_arg(ap, double);
            n += printf("%G", fval);
            break;
        case 'p':
            pv_val = va_arg(ap, void *);
            n += printf("%p", pv_val);
            break;
        case 'n':
            pn_val = va_arg(ap, int *);
            *pn_val = n;
            break;
        default:
            n += printf("%c", *fmt);
            break;
        }
    }
    va_end(ap);
}

int main() {
    int dval = 1337;
    unsigned uval = 42;
    char cval = 'c';
    char sval[] = "cow";
    double fval = 0.99;

    int v_val = 777;
    int n_val = 0;
    void *pv_val = (void *) &v_val;
    int *pn_val = &n_val;

    minprintf("%d %i %o %x %X %u %c %s %f %e %E %g %G %p %n %%\n", dval, dval, uval, uval, uval, uval, cval, sval, fval, fval, fval, fval, fval, pv_val, pn_val);
    minprintf("%d\n", n_val);
    char got[] = "1337 1337 52 2a 2A 42 c cow 0.990000 9.900000e-01 9.900000E-01 0.99 0.99 0x16dd06ed4  %";
    minprintf("%d\n", strlen(got) - 2);  // minus 2 for blank and final percent symbol
}
