/*
Write a function rightrot(x,n) that returns the value of the integer 
x rotated to the right by n bit positions. 
*/

#include <stdio.h>
#include <limits.h>

unsigned rightrot(unsigned x, int n) {
    int bitwidth = CHAR_BIT * sizeof(x);
    unsigned shifted = (x >> n);
    unsigned wrapped = (x << (bitwidth - n));
    return wrapped | shifted;
}


int main() {
    int bitwidth = CHAR_BIT * sizeof(0U);
    printf("got: %d\n", rightrot(~0U, 1));
    printf("expected: %d\n", ~0U);
    printf("\n");

    printf("got: %d\n", rightrot(1U, 1));
    printf("expected: %d\n", 1 << (bitwidth - 1));
    printf("\n");

    printf("got: %d\n", rightrot(1U, 5));
    printf("expected: %d\n", 1 << (bitwidth - 5));
    printf("\n");
}