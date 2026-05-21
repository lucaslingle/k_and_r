/*
Write a program to print a set of files, starting each new one on a new page,
with a title and running page count for each file.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void paged_print(char *fname, int max_line_chars, int max_page_lines) {
    FILE *fp = fopen(fname, "r");
    char page_num_string[max_line_chars];
    int blanks;
    int page_num = 1;
    int page_line_count = 0;
    int line_char_count = 0;
    int c;
    while ((c = getc(fp)) != EOF) {
        if (page_line_count % max_page_lines == 0) {
            sprintf(page_num_string, "%d", page_num);
            blanks = max_line_chars - strlen(fname) - strlen(page_num_string);
            printf("\n%s%*s%s\n\n", fname, blanks, "", page_num_string);
            page_num++;
            page_line_count = 3;
        }
        if (line_char_count == max_line_chars - 1) {
            putc('\\', stdout);
            putc('\n', stdout);
            page_line_count++;
            line_char_count = 0;
        } else if (c == '\n') {
            putc('\n', stdout);
            page_line_count++;
            line_char_count = 0;
        } else {
            putc(c, stdout);
            line_char_count++;
        }
    }
    fclose(fp);
}

int main(int argc, char *argv[]) {
    int max_line_chars = 100;
    int max_page_lines = 40;
    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s filepath1 [filepath2] [filepath2]...\n", argv[0]);
        exit(1);
    }
    for (int i = 1; i < argc; i++)
        paged_print(argv[i], max_line_chars, max_page_lines);
}
