/*
Write a function escape(s,t) that converts characters like newline and tab into visible escape sequences 
like \n and \t as it copies the string t to s. Use a switch statement. 

Write a function for the other direction as well, copying escape sequences into the real characters. 
*/

#include <stdio.h>

void escape(char s[], const char t[]) {
    int i = 0;
    int j = 0;
    for (; t[i] != '\0'; i++) {
        switch (t[i]) {
            case '\n': {
                s[j] = '\\';
                s[j+1] = 'n';
                j += 2;
                break;
            }
            case '\t': {
                s[j] = '\\';
                s[j+1] = 't';
                j += 2;
                break; 
            }
            default: {
                s[j] = t[i];
                j += 1;
                break;
            }
        }
    }
    s[j] = '\0';
}

void unescape(const char s[], char t[]) {
    int i = 0;
    int j = 0;
    int s_jm1 = EOF;
    while (s[j] != '\0') {
        if (s[j] == '\\') {
            s_jm1 = s[j];
            j += 1;
        } else if (s_jm1 == '\\') {
            switch (s[j]) {
                case 'n': 
                    t[i] = '\n';
                    s_jm1 = EOF;
                    i += 1;
                    j += 1;
                    break;
                case 't': 
                    t[i] = '\t';
                    s_jm1 = EOF;
                    i += 1;
                    j += 1;
                    break;
            }
        } else {
            t[i] = s[j];
            s_jm1 = s[j];
            i += 1;
            j += 1;
        }
    }
    t[i] = s_jm1;
    t[i+1] = '\0';
}

int main() {
    char s[1000];
    char t[] = "did\tu\tsay\textra\tcrispy\trecipe\n";

    escape(s, t);
    printf("%s\n", s);

    char z[] = "did\\tu\\tsay\\textra\\tcrispy\\trecipe\\n";
    char x[1000];

    unescape(z, x);
    printf("%s\n", x);
}
