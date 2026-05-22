/*
Functions like isupper can be implemented to save space or to save time.
Explore both possibilities.
*/

#include <stdio.h>
#include <time.h>

int isupper_slim(char c) {
    return c >= 65 && c <= 90;
}

int isupper_fast(char c, int table[256]) {
    return table[c];
}

int main() {
    int table[256] = {};
    for (int c = 65; c <= 90; c++)
        table[c] = 1;

    clock_t start0 = clock();  // Record start tick
    for (int i=0; i<1000000; i++)
        isupper_slim('L');
    clock_t end0 = clock();    // Record end tick
    double time_spent0 = (double)(end0 - start0) / CLOCKS_PER_SEC;
    printf("isupper_slim - time taken: %f seconds\n", time_spent0);

    clock_t start = clock();  // Record start tick
    for (int i=0; i<1000000; i++)
        isupper_fast('L', table);
    clock_t end = clock();    // Record end tick
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("isupper_fast - time taken: %f seconds\n", time_spent);

    return 0;
}