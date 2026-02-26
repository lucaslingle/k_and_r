/*
Experiment to find out what happens when printf's argument string 
contains \c where c is some character other than n, t, b and \.
*/

#include <stdio.h>

main() {
    printf("hello, world\c");
}