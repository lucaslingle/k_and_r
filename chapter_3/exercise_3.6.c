/*
Write a version of itoa that accepts three arguments instead of two. 
The third argument is a minimum field width; the converted number 
must be padded with blanks on the left if necessary to make it wide enough. 
*/

#include <stdio.h>
#include <string.h>

void reverse(char s[]) {
    int i, len, temp;
    len = strlen(s);

    for (i = 0; i <= (len-1) / 2; i++) {
        temp = s[i];
        s[i] = s[len-1-i];
        s[len-1-i] = temp;
    }
    s[len] = '\0';
    return;
}

void itoa(int n, char s[], int w) {
    int i = 0;
    int sign = (n < 0) ? -1 : 1;
    n = (n < 0) ? n : -n;
    do {
        s[i++] = -(n % 10) + '0';
    } while (-(n /= 10) > 0);
    for (; i < w ;)
        s[i++] = ' ';
    if (sign == -1)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main() {
    char s[1000];
    char s_prime[] = "-2147483648";
    int n = -2147483648;
    itoa(n, s, 10);
    printf("%s\n", s);
    printf("%s\n", s_prime);

    char z[1000];
    char z_prime[] = "2147483647";
    int m = 2147483647;
    itoa(m, z, 10);
    printf("%s\n", z);
    printf("%s\n", z_prime);

    char s2[1000];
    char s2_prime[] = "   1";
    int n2 = 1;
    itoa(n2, s2, 4);
    printf("%s\n", s2);
    printf("%s\n", s2_prime);

    char z2[1000];
    char z2_prime[] = "9999";
    int m2 = 9999;
    itoa(m2, z2, 4);
    printf("%s\n", z2);
    printf("%s\n", z2_prime);
}
