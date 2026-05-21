/*
Write a program to compare two files, printing the first line
where the differ.
*/

#include <stdio.h>
#include <string.h>
#define MAXLEN 1000

int main(int argc, char *argv[]) {
    if (argc != 3)
        printf("usage: %s filepath1 filepath2\n", argv[0]);
    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "r");
    char line1[MAXLEN] = {};
    char line2[MAXLEN] = {};
    char *ret1, *ret2;
    while (1) {
        ret1 = fgets(line1, MAXLEN, fp1);
        ret2 = fgets(line2, MAXLEN, fp2);
        if (ret1 == NULL && ret2 == NULL) {
            break;
        } else if (ret1 == NULL && ret2 != NULL) {
            printf("EOF\n"); 
            printf("%s", line2);
            break;
        } else if (ret1 != NULL && ret2 == NULL) {
            printf("%s", line1);
            printf("EOF\n"); 
            break;
        } else if (strcmp(line1, line2) != 0) {
            printf("%s", line1);
            printf("%s", line2);
            break;
        }
    }
}
