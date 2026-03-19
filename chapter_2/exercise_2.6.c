/*
Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p 
set to the rightmost n bits of y, leaving the other bits unchanged.
*/

#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    unsigned m1 = ~0U << (p+1);    // for p = 2, have something like 1111_1000
    unsigned m2 = ~0U << (p+1-n);  // for p = 2, n = 1, have something like 1111_1100
    unsigned m3 = m1 ^ m2;         // for p = 2, n = 1, have something like 0000_0100
    unsigned y_prime = y & m3;    // for p = 2, n = 1, have something like 0000_0y00
    unsigned x_prime = x & ~m3;    // for p = 2, n = 1, have something like xxxx_x0xx
    return x_prime | y_prime;      // for p = 2, n = 1, have something like xxxx_xyxx
}

int main() {
    printf("got: %d\n", setbits(255U, 2, 1, 0U));
    printf("expected: %d\n", 251U);
    printf("\n");

    printf("got: %d\n", setbits(255U, 3, 2, 0U));
    printf("expected: %d\n", 243U);
    printf("\n");

    printf("got: %d\n", setbits(255U, 3, 2, 255U));
    printf("expected: %d\n", 255U);
    printf("\n");

    printf("got: %d\n", setbits(255U, 3, 2, 243U));
    printf("expected: %d\n", 243U);
    printf("\n");

    printf("got: %d\n", setbits(255U, 7, 8, 243U));
    printf("expected: %d\n", 243U);
    printf("\n");
}