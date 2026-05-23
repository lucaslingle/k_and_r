/*
Rewrite the program cat from Chapter 7 using read, write, open, and close
instead of their standard library equivalents. Perform experiments to
determine the relative speeds of the two versions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

void original_fileprint(FILE *fp) {
    int c;
    while ((c = getc(fp)) != EOF)
        putc(c, stdout);
}

void original_cat(int argc, char *argv[]) {
    FILE *fp;
    if (argc == 1)
        original_fileprint(stdin);
    else
        while (--argc > 0)
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "original_cat: can't open %s\n", *argv);
                exit(1);
            } else {
                original_fileprint(fp);
                fclose(fp);
            }
}

void syscall_fileprint(int fd) {
    char buf[BUFSIZ];
    int n;
    while ((n = read(fd, buf, BUFSIZ)) > 0)
        write(1, buf, n);
}

void syscall_cat(int argc, char *argv[]) {
    int fd;
    if (argc == 1)
        syscall_fileprint(0);
    else
        while (--argc > 0)
            if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
                fprintf(stderr, "syscall_cat: can't open %s\n", *argv);
                exit(1);
            } else {
                syscall_fileprint(fd);
                close(fd);
            }
}

int main(int argc, char *argv[]) {
    clock_t start0 = clock();
    for (int i=0; i<100; i++)
        original_cat(argc, argv);
    clock_t end0 = clock();
    double time_spent0 = (double)(end0 - start0) / CLOCKS_PER_SEC;
    printf("original_cat - time taken: %f seconds\n", time_spent0);

    clock_t start = clock();
    for (int i=0; i<100; i++)
        syscall_cat(argc, argv);
    clock_t end = clock(); 
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("syscall_cat - time taken: %f seconds\n", time_spent);

    return 0;
}
