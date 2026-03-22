/*
Write the function itob(n,s,b) that converts the integer n 
into a base b character representation in the string s. 
In particular, itob(n,s,16) formats n as a hexidecimal integer in s. 
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

void itob(int n, char s[], int b) {
    char symbols[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i = 0;
    int sign = (n < 0) ? -1 : 1;
    n = (n < 0) ? n : -n;
    do {
        s[i++] = symbols[-(n % b)];
    } while (-(n /= b) > 0);
    if (sign == -1)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main() {
    char s[1000];
    char s_prime[] = "-2147483648";
    int n = -2147483648;
    itob(n, s, 10);
    printf("%s\n", s);
    printf("%s\n", s_prime);

    char z[1000];
    char z_prime[] = "2147483647";
    int m = 2147483647;
    itob(m, z, 10);
    printf("%s\n", z);
    printf("%s\n", z_prime);

    char s2[1000];
    char s2_prime[] = "-80000000";
    int n2 = -2147483648;
    itob(n2, s2, 16);
    printf("%s\n", s2);
    printf("%s\n", s2_prime);

    char z2[1000];
    char z2_prime[] = "7FFFFFFF";
    int m2 = 2147483647;
    itob(m2, z2, 16);
    printf("%s\n", z2);
    printf("%s\n", z2_prime);
}
