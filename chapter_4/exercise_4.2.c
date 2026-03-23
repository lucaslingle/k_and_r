/*
Extend atof to handle scientific notation of the form 123.45e-6 where a floating point number 
may be followed by e or E and an optionally signed integer exponent. 
*/

#include <stdio.h>
#include <ctype.h>
#define MAXLINE 100

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
    val = sign * val / power;

    int e_sign, e_val;
    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        e_sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
            i++;
        for (e_val = 0; isdigit(s[i]); i++)
            e_val = 10 * e_val + (s[i] - '0');
        for (int j = 0; j < e_val; j++) {
            if (e_sign == -1)
                val /= 10.0;
            else
                val *= 10;
        }
    }
    return val;
}

int mygetline(char s[], int lim) {
    int c, i;
    i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

int main() {
    double sum;
    char line[MAXLINE];
    int mygetline(char line[], int max);
    sum = 0;
    while (mygetline(line, MAXLINE) > 0) 
        printf("\t%g\n", sum += myatof(line));
    return 0;
}
