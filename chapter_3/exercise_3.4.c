/*
In a two's complement number representation, our version of itoa does not handle 
the largest negative number, that is the value of n equal to -(2^[wordsize - 1]). 
Explain why not. Modify it to print that value correctly, 
regardless of the machine it runs on. 

// original version
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

void itoa(int n, char s[]) {
    int i, sign;

    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}
*/

// The largest-magnitude negative number representable in two's complement 
// is one greater in magnitude than the largest positive number. 
// When computing n = -n in the initial code, we flip the sign of n to be positive, 
// which produces the wrong result when starting with n == -INT_MIN. 
//
// The stored n should be negative at all times; 
// fixing the sign flip can be handled when the number is smaller in magnitude. 

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

void itoa(int n, char s[]) {
    int i = 0;
    int sign = (n < 0) ? -1 : 1;
    n = (n < 0) ? n : -n;
    do {
        s[i++] = -(n % 10) + '0';
    } while (-(n /= 10) > 0);
    if (sign == -1)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main() {
    char s[1000];
    char s_prime[] = "-2147483648";
    int n = -2147483648;
    itoa(n, s);
    printf("%s\n", s);
    printf("%s\n", s_prime);

    char z[1000];
    char z_prime[] = "2147483647";
    int m = 2147483647;
    itoa(m, z);
    printf("%s\n", z);
    printf("%s\n", z_prime);
}
