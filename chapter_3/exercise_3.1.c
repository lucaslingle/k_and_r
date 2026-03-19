/*
Our binary search makes two tests inside the loop, when one would suffice (at the price of more tests outside).
Write a version with only one test inside the loop, and measure the difference in run-time.
*/

#include <stdio.h>
#include <time.h>

// original version of binsearch shown below:
int binsearch_v1(int x, int v[], int n) {
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

// my version 
int binsearch_v2(int x, int v[], int n) {
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low < high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid;
    }
    if ((low == high) && (v[low] == x))
        return low;
    else
        return -1;
}

// time both versions
int main() {
    int n = 1000000;
    int v[n];
    for (int i = 0; i<n; i++) {
        v[i] = i;
    }
    int x = 1234;

    int trials = 1000000;
    clock_t v1_start = clock();
    for (long t1=0; t1<trials; t1++) {
        binsearch_v1(x, v, n);
    }
    clock_t v1_end = clock();
    double delta1 = (double) (v1_end - v1_start);
    printf("%f\n", delta1);

    clock_t v2_start = clock();
    for (long t2=0; t2<trials; t2++) {
        binsearch_v2(x, v, n);
    }
    clock_t v2_end = clock();
    double delta2 = (double) (v2_end - v2_start);
    printf("%f\n", delta2);
}