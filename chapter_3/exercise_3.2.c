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
        // putchar(s[j]);
        // printf("\n");
        if (s[j] == '\\') {
            s_jm1 = s[j];
            j += 1;
        } else if (s_jm1 == '\\') {
            // putchar(s[j]);
            switch (s[j]) {
                case 'n': 
                    // printf("we here in case n!\n");
                    t[i] = '\n';
                    // putchar(t[i]);
                    // putchar('\n');
                    s_jm1 = EOF;
                    i += 1;
                    j += 1;
                    break;
                case 't': 
                    // printf("we here in case t!\n");
                    t[i] = '\t';
                    // putchar(t[i]);
                    // putchar('\n');
                    s_jm1 = EOF;
                    i += 1;
                    j += 1;
                    break;
                default: 
                    printf("we here in case default!\n");
            }
        } else {
            t[i] = s[j];
            // putchar(t[i]);
            // putchar('\n');
            s_jm1 = s[j];
            i += 1;
            j += 1;
        }
        // putchar(s_jm1);
        // printf("\n");
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
