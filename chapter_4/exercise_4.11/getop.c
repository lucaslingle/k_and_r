#include <stdio.h>
#include <ctype.h>
#include "calc.h"

int getop(char s[]) {
    int i = 0;
    int type;
    static int c;
    
    while ((c = getchar()) == ' ' || c == '\t')
        ;
    if (c == '_') {
        type = READ_PRINTED;
    } else if (c == '-' || isdigit(c)) {
        s[0] = c;
        while (isdigit(c = getchar()))
            s[++i] = c;
        if (c == '.') {
            s[++i] = '.';
            while (isdigit(c = getchar()))
                s[++i] = c;
        }
        type = NUMBER;
    } else if ((c == '=') && (getchar() == ':') && isalpha(c = getchar())) {
        s[0] = '=';
        s[++i] = ':';
        s[++i] = c;
        type = WRITE_VARIABLE;
    } else if (isalpha(c)) {
        s[0] = c;
        while (isalpha(c = getchar()))
            s[++i] = c;
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
