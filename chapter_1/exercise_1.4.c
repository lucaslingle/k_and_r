/* Write a program to print the corresponding Celsius to Fahrenheit table. */

#include <stdio.h>

main() {
    float celsius, fahr;
    float lower, upper, step;

    lower = -17.8;
    upper = 148.9;
    step = 11.1;

    printf("      C  F\n");
    celsius = lower;
    while (celsius <= upper) {
        fahr = celsius * (9.0 / 5.0) + 32.0;
        printf("%6.1f %3.0f\n", celsius, fahr);
        celsius = celsius + step;
    }
}