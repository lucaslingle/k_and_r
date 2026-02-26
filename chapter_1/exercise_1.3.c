/* Modify the temperature conversion program to print a heading above the table. */

#include <stdio.h>

main() {
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("  F      C\n");
    fahr = lower; // implicit conversion of int to float
    while (fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);  // implicit conversion of int to float
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}