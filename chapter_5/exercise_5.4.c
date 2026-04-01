/*
Write the function strend(s,t), which returns 1 if the string t occurs
at the end of the string s, and zero otherwise. 
*/

#include <stdio.h>

int strend(char *s, char *t) {
    char *t2 = t;
    while (*s != '\0')
        s++;
    while (*t != '\0')
        t++;
    while (*s == *t) {
        s--;
        t--;
    }
    t++;
    if (t == t2)
        return 1;
    return 0;
}

int main() {
    char s[100] = "Hello World!";
    char t[10] = "World!";
    int ans = strend(s, t);
    printf("%d\n", ans);
    return 0;
}
