/*
Write a function any(s1, s2) which returns the first location in the string s1 where any character from
the string s2 occurs, or -1 if s1 contains no characters from s2. 

(The standard library function strpbrk does the same job but returns a pointer to the location.)
*/

#include <stdio.h>

int any(char s1[], char s2[]) {
    int i, k;
    for (i = 0; s1[i] != '\0'; i++) {
        for (k = 0; s2[k] != '\0'; k++) {
            if (s1[i] == s2[k]) {
                return i;
            }
        }
    }
    return -1;
}

int main() {
    char s1[] = "Hello World!";
    char s2[] = "aeiouAEIOU";
    int idx = any(s1, s2);
    printf("%d\n", idx);

    char s3[] = "Hello World!";
    char s4[] = "!";
    int idxx = any(s3, s4);
    printf("%d\n", idxx);
}