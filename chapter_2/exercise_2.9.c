/*
In a two's complement number system, x & (x-1) deletes the rightmost 1-bit in x. 
(Stenographer's clarification: it does not merely zero out the ones place!) Explain why.

Use this observation to write a faster version of bitcount. 
Original version of `bitcount` shown below:

int bitcount(unsigned x) {
    int b;
    for (b = 0; x != 0; x >>= 1)
        if (x & 01)
            b++;
    return b;
}
*/

// the explanation:
//
// suppose x is an unsigned integer with at least one nonzero bit. 
// x-1 has the same bitwise representation for all bits to the left of the rightmost nonzero bit of x,
// but has a zero in the bit position where x's rightmost nonzero bit appears, 
// and finally it has ones in all the bits to the right of that. 
//
// anding keeps the bits to the left the same because they were unchanged in the repr of x-1.
// anding keeps the bits to the right the same because they're anded with ones appearing in the repr of x-1.
// anding changes the bit of the rightmost nonzero bit of x to be a zero, because it is anded with zero. 

#include <stdio.h>

int fast_bitcount(unsigned x) {
    // stops after all nonzero bits are counted.
    // each iteration removes the rightmost nonzero bit, instead of just the ones place, 
    // so there are fewer iterations total. 
    int b;
    for (b = 0; x != 0; b++)
        x &= x-1;
    return b;
}

int main() {
    unsigned x;
    unsigned b;
    unsigned bprime;

    x = 0;
    b = fast_bitcount(x);
    bprime = 0;
    printf("fast_bitcount(%d)\n\tactual: %d\n\texpected: %d\n", x, b, bprime);

    x = 1;
    b = fast_bitcount(x);
    bprime = 1;
    printf("fast_bitcount(%d)\n\tactual: %d\n\texpected: %d\n", x, b, bprime);

    x = 2;
    b = fast_bitcount(x);
    bprime = 1;
    printf("fast_bitcount(%d)\n\tactual: %d\n\texpected: %d\n", x, b, bprime);

    x = 3;
    b = fast_bitcount(x);
    bprime = 2;
    printf("fast_bitcount(%d)\n\tactual: %d\n\texpected: %d\n", x, b, bprime);

    x = 255;
    b = fast_bitcount(x);
    bprime = 8;
    printf("fast_bitcount(%d)\n\tactual: %d\n\texpected: %d\n", x, b, bprime);

    x = 128;
    b = fast_bitcount(x);
    bprime = 1;
    printf("fast_bitcount(%d)\n\tactual: %d\n\texpected: %d\n", x, b, bprime);

    return 0;
}