/*
Write a loop equivalent to the for loop above without using && or ||.

for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
    s[i] = c;

*/

#include <stdio.h>
#define MAXLINE 1000

int main() {
    int i, c;
    char s[MAXLINE];

    for (i = 0; i < MAXLINE - 1; ++i) {
        c = getchar();
        if (c == '\n' || c == EOF) {
            break;
        } else {
            s[i] = c;
        }
    }
    s[i] = '\0';
    printf("%s\n", s);
    return 0;
}