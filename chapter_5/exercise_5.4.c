/*
Write the function strend(s,t), which returns 1 if the string t occurs
at the end of the string s, and zero otherwise. 
*/

#include <stdio.h>

int strend(char *s, char *t) {
    char *t0 = t;
    while (*s)
        s++;
    while (*t)
        t++;
    for (; t0 <= t; t--, s--)
        if (*t != *s)
            return 0;
    return 1;
}

int main() {
    char s[100] = "Hello World!";
    char t[10] = "World!";
    int ans = strend(s, t);
    printf("got %d, expected 1\n", ans);

    char s2[100] = "Hello ";
    char t2[10] = "World!";
    int ans2 = strend(s2, t2);
    printf("got %d, expected 0\n", ans2);

    char s3[100] = "Hello ";
    char t3[10] = "";
    int ans3 = strend(s3, t3);
    printf("got %d, expected 1\n", ans3);

    return 0;
}
