/* 
Add the -d ("directory order") option, which makes comparisons only on 
letters, numbers, and blanks. Make sure it works in conjunction with -f.

(Starting point is code from exercise 5.15.)
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXLEN 100
#define MAXLINES 5000    // max lines to be sorted
char *lineptr[MAXLINES];  // pointers to text lines

int my_readlines(char *lineptr[], int nlines);
void my_writelines(char *lineptr[], int nlines);
int my_numcmp(char *, char *);
double my_atof(char *);
void my_qsort(
    void *lineptr[], int left, int right, 
    int (*comp)(void *, void *), 
    int (*maybe_reverse)(int),
    void (*maybe_fold)(char *, char *),
    void (*maybe_dir)(char *, char *)
);
int yes_reverse(int);
int no_reverse(int);
void yes_fold(char *, char *);
void no_fold(char *, char *);
void yes_dir(char *, char *);
void no_dir(char *, char *);

// sort input lines
int main(int argc, char *argv[]) {
    int nlines;       // num input lines read
    int numeric = 0;  // 1 if numeric sort
    int reverse = 0;  // 1 if sort in decreasing order
    int fold = 0;     // 1 if fold case distinctions
    int dir = 0;      // 1 if compare on alphanumeric and space only ("directory order")
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-n") == 0)
                numeric = 1;
            if (strcmp(argv[i], "-r") == 0)
                reverse = 1;
            if (strcmp(argv[i], "-f") == 0)
                fold = 1;
            if (strcmp(argv[i], "-d") == 0)
                dir = 1;
        }
    }
    if ((nlines = my_readlines(lineptr, MAXLINES)) >= 0) {
        my_qsort(
            (void **) lineptr, 0, nlines-1, 
            (int (*)(void *, void *))(numeric ? my_numcmp : strcmp),
            (int (*)(int))(reverse ? yes_reverse : no_reverse),
            (void (*)(char *, char *))(fold ? yes_fold : no_fold),
            (void (*)(char *, char *))(dir ? yes_dir : no_dir)
        );
        my_writelines(lineptr, nlines);
        return 0;
    }
    printf("Input too big to sort\n");
    return 1;
}

int my_getline(char *s, int lim) {
    char *s0 = s;
    int c;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return (s - s0);
}

#define ALLOCSIZE 100000
int my_readlines(char *lineptr[], int maxlines) {
    static char allocbuf[ALLOCSIZE];
    static char *allocp = allocbuf;
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = my_getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || allocp - allocbuf + len > ALLOCSIZE)
            return -1;
        else {
            p = allocp;
            allocp += len;
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

void my_writelines(char *lineptr[], int nlines) {
    for (int i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

int my_numcmp(char *s1, char *s2) {
    double v1, v2;
    v1 = my_atof(s1);
    v2 = my_atof(s2);
    return (v1 < v2) ? -1 : (v1 > v2) ? 1 : 0;
}

void my_qsort(
    void *v[], int left, int right, 
    int (*comp)(void *, void *),
    int (*maybe_reverse)(int),
    void (*maybe_fold)(char *, char *),
    void (*maybe_dir)(char *, char *)
) {
    int i, last;
    void my_swap(void *v[], int, int);   
    if (left >= right)
        return;
    my_swap(v, left, (left + right) / 2);
    last = left;

    char tv_1[MAXLEN];
    char tv_2[MAXLEN];
    int compare_val;
    for (i = left+1; i <= right; i++) {
        (*maybe_fold)(tv_1, v[i]);
        (*maybe_fold)(tv_2, v[left]);
        (*maybe_dir)(tv_1, tv_1);
        (*maybe_dir)(tv_2, tv_2);
        compare_val = (*comp)(tv_1, tv_2);
        compare_val = (*maybe_reverse)(compare_val);
        if (compare_val < 0)
            my_swap(v, ++last, i);
    }
    my_swap(v, left, last);
    my_qsort(v, left, last-1, comp, maybe_reverse, maybe_fold, maybe_dir);
    my_qsort(v, last+1, right, comp, maybe_reverse, maybe_fold, maybe_dir);
}

void my_swap(void *v[], int i, int j) {
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

double my_atof(char *s) {
    double val, power;
    int sign;
    for (; isspace(*s); s++)  // skip whitespace
        ;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    for (val = 0.0; isdigit(*s); s++)
        val = 10.0 * val + (*s - '0');
    if (*s == '.')
        s++;
    for (power = 1.0; isdigit(*s); s++) {
        val = 10.0 * val + (*s - '0');
        power *= 10.0;
    }
    return sign * val / power;
}

int yes_reverse(int n) {
    return -n;
}

int no_reverse(int n) {
    return n;
}

void yes_fold(char *dest, char *src) {
    while (*src != '\0')
        *dest++ = tolower(*src++);
    *dest = '\0';
}

void no_fold(char *dest, char *src) {
    while (*src != '\0')
        *dest++ = *src++;
    *dest = '\0';
}

void yes_dir(char *dest, char *src) {
    char *s0 = src;
    while (*src != '\0') {
        if (isspace(*src) || isalnum(*src))
            *dest++ = *src;
        src++;
    }
    *dest = '\0';
}

void no_dir(char *dest, char *src) {
    while (*src != '\0')
        *dest++ = *src++;
    *dest = '\0';
}
