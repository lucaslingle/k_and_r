/*
Rewrite readlines to store lines in an array supplied by main,
rather than calling alloc to maintain storage. How much faster is the program?
*/

#include <stdio.h>
#include <string.h>
#define MAXLINES 1000
#define MAXLEN 100
#define ALLOCSIZE 100000

char *lineptr[MAXLINES];
int book_getline(char *s, int lim);
int readlines(char *lineptr[], char *, char **, int maxlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

int main() {
    char allocbuf[ALLOCSIZE];
    char *allocp = allocbuf;
    int nlines;
    if ((nlines = readlines(lineptr, allocbuf, &allocp, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

int readlines(char *lineptr[], char *allocbuf, char **allocp, int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = book_getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || allocbuf + ALLOCSIZE - *allocp < len)
            return -1;
        else {
            p = *allocp;
            *allocp += len;
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines) {
    int i;
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

void qsort(char *v[], int left, int right) {
    int i, last;
    void swap(char *v[], int i, int j);
    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

void swap(char *v[], int i, int j) {
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int book_getline(char s[], int lim) {
    int c, i;
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}
