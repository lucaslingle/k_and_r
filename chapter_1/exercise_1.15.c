/*
Rewrite the termperature conversion program of 
Section 1.2 to use a function for conversion. 
*/

#include <stdio.h>

float f2c(float f);

main() {
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("  F      C\n");
    fahr = lower; // implicit conversion of int to float
    while (fahr <= upper) {
        celsius = f2c(fahr);  // implicit conversion of int to float
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }

    return 0;
}

float f2c(float f) {
    return (5.0 / 9.0) * (f - 32.0);
}