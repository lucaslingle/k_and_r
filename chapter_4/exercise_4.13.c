/*
Write a recursive version of the function reverse(s), 
which reverses the string s in place.
*/

#include <stdio.h>
#include <string.h>

void reverse(char s[]) {
    static int n = -1;
    static int i = 0;
    char temp;
    if (n == -1)
        n = strlen(s);
    if (i < n / 2) {
        temp = s[i];
        s[i] = s[n-1-i];
        s[n-1-i] = temp;
        i++;
        reverse(s);
    } else {
        n = -1;
        i = 0;
    }
}

int main() {
    char s[] = "abcdef";
    printf("pre: %s\n", s);
    reverse(s);
    printf("post: %s\n", s);

    char z[] = "xyz";
    printf("pre: %s\n", z);
    reverse(z);
    printf("post: %s\n", z);
}
