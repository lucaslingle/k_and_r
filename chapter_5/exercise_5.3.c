/*
Write a pointer version of the function strcat that we showed in Chapter 2:
strcat(s,t) copies the string t to the end of s. 

// original
void strcat(char s[], char t[]) {
    int i, j;
    i = j = 0;
    while (s[i] != '\0')
        i++;
    while ((s[i++] = t[j++]) != '\0')
        ;
}
*/

#include <stdio.h>

void mystrcat(char *s, char *t) {
    while (*s)
        s++;
    while ((*s++ = *t++))
        ;
}

int main() {
    char s[100] = "Hello ";
    char t[10] = "World!";
    mystrcat(s, t);
    printf("%s\n", s);
    return 0;
}
