/*
Modify the pattern finding program of Chapter 5 to take its input
from a set of named files, or if no files are named as arguments,
from the standard input. 

Should the file name be printed when a matching file is found? 

// original
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getline(char *line, int max);

int main(int argc, char *argv[]) {
    char line[MAXLINE];
    int found = 0;

    if (argc != 2)
        printf("Usage: find pattern\n");
    else
        while (getline(line, MAXLINE) > 0)
            if (strstr(line, argv[1]) != NULL) {
                printf("%s", line);
                found++;
            }
    return found;
}
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 1000

void search_loop(char *fname, FILE *fp, char *query) {
    char line[MAXLINE] = {};
    long lineno = 0;
    while (fgets(line, MAXLINE, fp) != NULL) {
        if (strstr(line, query) != NULL)
            printf("%s:%ld %s", fname, lineno, line);
        lineno++;
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Usage: find pattern [file1] [file2] [file3]...\n");
        exit(1);
    } else if (argc == 2)
        search_loop("stdin", stdin, argv[1]);
    else
        for (int i = 2; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            search_loop(argv[i], fp, argv[1]);
            fclose(fp);
        }
}