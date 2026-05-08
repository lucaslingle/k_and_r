/*
Write a program that converts upper case to lower case or lower case to upper case, 
depending on the name it is invoked with, as found in argv[0].
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int c;
    while ((c = getchar()) != EOF)
        if (strncmp(argv[0], "./upper", 5) == 0)
            putchar(toupper(c));
        else if (strncmp(argv[0], "./lower", 5) == 0)
            putchar(tolower(c));
        else {
            printf("Error, unexpected invokation name.\n");
            exit(1);
        }
}
