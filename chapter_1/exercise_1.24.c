/*
Write a program to check a C program for rudimentary syntax errors 
like unbalanced parentheses, brackets, and braces. 

Don't forget about quotes, both single and double, escape sequences, and comments. 
(This program is hard if you do it in full generality.)
*/

#include <stdio.h>
#define OUTCOMM_OUTQUOTE 0
#define OUTCOMM_INSINGLEQUOTE 1
#define OUTCOMM_INDOUBLEQUOTE 2
#define INCOMM_INLINE 3
#define INCOMM_MULTILINE 4

int main() {
    int state_tm1, backslashes_tm1, c_tm1, c_t;
    int l_parens, r_parens, l_brackets, r_brackets, l_braces, r_braces;

    state_tm1 = OUTCOMM_OUTQUOTE;
    backslashes_tm1 = 0;
    c_tm1 = EOF;
    l_parens = r_parens = l_brackets = r_brackets = l_braces = r_braces = 0;

    while ((c_t = getchar()) != EOF) {
        putchar('0' + state_tm1);
        if (c_t == '\n') {
            putchar('\n');
        }

        if ((state_tm1 == OUTCOMM_OUTQUOTE) && (c_t != '\'') && (c_t != '"') && (c_tm1 != '/' || c_t != '/') && (c_tm1 != '/' || c_t != '*')) {
            // state 0 -> state 0
            state_tm1 = OUTCOMM_OUTQUOTE;
            if (c_t == '(') {
                l_parens++;
            } else if (c_t == ')') {
                r_parens++;
            } else if (c_t == '[') {
                l_brackets++;
            } else if (c_t == ']') {
                r_brackets++;
            } else if (c_t == '{') {
                l_braces++;
            } else if (c_t == '}') {
                r_braces++;
            }
        } else if ((state_tm1 == OUTCOMM_OUTQUOTE) && (c_t == '\'')) {
            // state 0 -> state 1
            state_tm1 = OUTCOMM_INSINGLEQUOTE;
        } else if ((state_tm1 == OUTCOMM_OUTQUOTE) && (c_t == '"')) {
            // state 0 -> state 2
            state_tm1 = OUTCOMM_INDOUBLEQUOTE;
        } else if ((state_tm1 == OUTCOMM_OUTQUOTE) && (c_tm1 == '/' && c_t == '/')) {
            // state 0 -> state 3
            state_tm1 = INCOMM_INLINE;
        } else if ((state_tm1 == OUTCOMM_OUTQUOTE) && (c_tm1 == '/' && c_t == '*')) {
            // state 0 -> state 4
            state_tm1 = INCOMM_MULTILINE;
        } else if ((state_tm1 == OUTCOMM_INSINGLEQUOTE) && (backslashes_tm1 % 2 == 0 && c_t == '\'')) {
            // state 1 -> state 0
            state_tm1 = OUTCOMM_OUTQUOTE;
        } else if ((state_tm1 == OUTCOMM_INSINGLEQUOTE) && (backslashes_tm1 % 2 != 0 || c_t != '\'')) {
            // state 1 -> state 1
            state_tm1 = OUTCOMM_INSINGLEQUOTE;
        } else if ((state_tm1 == OUTCOMM_INDOUBLEQUOTE) && (backslashes_tm1 % 2 == 0 && c_t == '"')) {
            // state 2 -> state 0
            state_tm1 = OUTCOMM_OUTQUOTE;
        } else if ((state_tm1 == OUTCOMM_INDOUBLEQUOTE) && (backslashes_tm1 % 2 != 0 || c_t != '"')) {
            // state 2 -> state 2
            state_tm1 = OUTCOMM_INDOUBLEQUOTE;
        } else if ((state_tm1 == INCOMM_INLINE) && (c_t == '\n')) {
            // state 3 -> state 0
            state_tm1 = OUTCOMM_OUTQUOTE;
        } else if ((state_tm1 == INCOMM_INLINE) && (c_t != '\n')) {
            // state 3 -> state 3
            state_tm1 = INCOMM_INLINE;
        } else if ((state_tm1 == INCOMM_MULTILINE) && (c_tm1 == '*' && c_t == '/')) {
            // state 4 -> state 0
            state_tm1 = OUTCOMM_OUTQUOTE;
        } else if ((state_tm1 == INCOMM_MULTILINE) && (c_tm1 != '*' || c_t != '/')) {
            // state 4 -> state 4
            state_tm1 = INCOMM_MULTILINE;
        }
        c_tm1 = c_t;

        if (c_t == '\'') {
            backslashes_tm1++;
        } else {
            backslashes_tm1 = 0;
        }
    }

    if (l_parens != r_parens) {
        return -1;
    } else if (l_brackets != r_brackets) {
        return -2;
    } else if (l_braces != r_braces) {
        return -3;
    } else {
        return 0;
    }
}