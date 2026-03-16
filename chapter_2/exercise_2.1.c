/*
Write a program to determine the ranges of char, short, int, and long variables, 
both signed and unsigned, by printing appropriate values from standard headers and by direct computation. 

Harder if you compute them: determine the ranges of the various floating point types.
*/

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    printf("char: %d to %d\n", CHAR_MIN, CHAR_MAX);
    printf("short: %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("int: %d to %d\n", INT_MIN, INT_MAX);
    printf("long: %ld to %ld\n", LONG_MIN, LONG_MAX);

    printf("unsigned char: %u to %u\n", 0, UCHAR_MAX);
    printf("unsigned short: %u to %u\n", 0, USHRT_MAX);
    printf("unsigned int: %u to %u\n", 0, UINT_MAX);
    printf("unsigned long: %lu to %lu\n", 0UL, ULONG_MAX);

    printf("float: %f to %f\n", -FLT_MAX, FLT_MAX);
    printf("double: %f to %f\n", -DBL_MAX, DBL_MAX);
    printf("long double: %Lf to %Lf\n", -LDBL_MAX, LDBL_MAX);
}