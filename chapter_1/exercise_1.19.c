/*
Write a function reverse(s) that takes reverses the character string s.
Use it to write a program that reverses its input a line at a time.
*/

#include <stdio.h>
#define MAXLINE 1000

int mygetline(char line[], int maxline);
int mygetlen(char line[], int maxline);
void reverse(char s[]);

int main() {
    int len, i;
    char line[MAXLINE];
    while ((len = mygetline(line, MAXLINE)) > 0) {
        reverse(line);
        for (i = 0; i < len; i++) {
            putchar(line[i]);
        }
        putchar('\n');
    }
    return 0;
}

int mygetline(char s[], int lim) {
    int i, c;
    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    s[i] = '\0';
    return i;
}

int mygetlen(char s[], int lim) {
    int i;
    for (i = 0; i <= lim-1 && s[i] != '\0'; i++) {
        ;
    }
    return i;
}

void reverse(char s[]) {
    int i, len, temp;
    len = mygetlen(s, MAXLINE);

    for (i = 0; i <= (len-1) / 2; i++) {
        temp = s[i];
        s[i] = s[len-1-i];
        s[len-1-i] = temp;
    }
    s[len] = '\0';
    return;
}
