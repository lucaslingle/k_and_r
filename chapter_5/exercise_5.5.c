/*
Write versions of the library functions strncpy, strncat, strncmp, 
which operate on at most the first n characters of their argument strings.
For example, strncpy(s, t, n) copies at most n characters of t to s.
Full descriptions are in Appendix B.
*/

#include <stdio.h>

char *__strncpy(char *s, const char *t, int n) {
    char *s0 = s;
    for (int i = 0; i < n && (*s = *t) != '\0'; i++, s++, t++)
        ;
    return s0;
}

char *__strncat(char *s, const char *t, int n) {
    char *s0 = s;
    while (*s != '\0')
        s++;
    for (int i = 0; i < n && (*s = *t) != '\0'; i++, s++, t++)
        ;
    return s0;
}

int __strncmp(char *s, const char *t, int n) {
    for (int i = 0; i < n && *s == *t; i++, s++, t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}

int main() {
    char s[100] = "Hello ";
    char t[10] = "World!";
    int i = 0;

    printf("%s\n", s);
    printf("%s\n\n", t);

    __strncpy(s, t, 2);
    printf("__strncpy(s, t, 2) ------\n");
    printf("%s\n", s);
    printf("%s\n\n", t);

    __strncat(s, t, 2);
    printf("__strncat(s, t, 2) ------\n");
    printf("%s\n", s);
    printf("%s\n\n", t);

    i = __strncmp(s, t, 2);
    printf("__strncmp(s, t, 2) ------\n");
    printf("%d\n", i);
    printf("%s\n", s);
    printf("%s\n\n", t);
}
