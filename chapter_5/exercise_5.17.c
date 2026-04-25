/*
Add a field handling capability, so sorting may be done on fields within lines, 
each field sorted according to an independent set of options.

(The index for this book was sorted with -df for index category 
and -n for the page numbers.)

Usage: 
Single field mode is ./program.o [-nrfd]
Multi-field mode is ./program.o -c 0 [nrfd] -c 2 [nrfd], etc.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXLEN 100
#define MAXFIELDS 100
#define MAXLINES 5000
char *lineptr[MAXLINES];                 // array of ptrs to text lines w/ mem alloc'd from block
char *sep_lineptr[MAXLINES][MAXFIELDS];  // array of ptrs to the separate fields in each line
int indices[MAXLINES];                   // used for sorting lineptr and sep_lineptr jointly.

int my_readlines(char *lineptr[MAXLINES]);
void my_sep_lines(
    char *lineptr[MAXLINES], 
    char *sep_lineptr[MAXLINES][MAXFIELDS], 
    int nlines,
    int nfields,
    int sep
);
void my_indices(int indices[MAXLINES]);
int my_numcmp(char *, char *);
int my_atoi(char *s);
double my_atof(char *);
void my_qsort(
    char *keys[MAXLINES][MAXFIELDS], 
    int indices[MAXLINES], 
    int left, 
    int right, 
    int sort_spec[MAXFIELDS],
    int numeric_spec[MAXFIELDS],
    int reverse_spec[MAXFIELDS], 
    int fold_spec[MAXFIELDS], 
    int dir_spec[MAXFIELDS],
    int nfields
);
int my_complex_compare(
    char *key1[MAXFIELDS], 
    char *key2[MAXFIELDS], 
    int sort_spec[MAXFIELDS],
    int numeric_spec[MAXFIELDS],
    int reverse_spec[MAXFIELDS], 
    int fold_spec[MAXFIELDS], 
    int dir_spec[MAXFIELDS],
    int nfields
);
int yes_reverse(int);
int no_reverse(int);
void yes_fold(char *, char *);
void no_fold(char *, char *);
void yes_dir(char *, char *);
void no_dir(char *, char *);

// sort input lines
int main(int argc, char *argv[]) {
    int sort_spec[MAXFIELDS] = {};     // 1 for sort on column, init'd at zero
    int numeric_spec[MAXFIELDS] = {};  // 1 for numeric sort, init'd at zero
    int reverse_spec[MAXFIELDS] = {};  // 1 for decreasing order, init'd at zero
    int fold_spec[MAXFIELDS] = {};     // 1 for folded case distinctions, init'd at zero
    int dir_spec[MAXFIELDS] = {};      // 1 for directory order, init'd at zero

    int nlines;
    int nfields = 1;
    int sep = EOF;
    int field_idx;

    // single-field mode: sort on text.
    if (argc <= 2)
        sort_spec[0] = 1;

    // single-field mode: parse any flags of ./program.o [-nrfd]
    if (argc == 2)
        if (argv[1][0] == '-') {
            numeric_spec[0] = (strchr(argv[1], 'n') != 0);
            reverse_spec[0] = (strchr(argv[1], 'r') != 0);
            fold_spec[0] = (strchr(argv[1], 'f') != 0);
            dir_spec[0] = (strchr(argv[1], 'd') != 0);
        }

    // multi-field mode: parse ./program.o -c 0 [nrfd] -c 2 [nrfd], etc.
    if (argc > 2) {
        for (int i = 1; i < argc; i++) {
            if ((i-1) % 3 == 0) {
                if (strchr(argv[1], 'c') == 0) {
                    printf("ERROR: bad arg format.");
                    return -1;
                }   
            } else if ((i-1) % 3 == 1) {
                field_idx = my_atoi(argv[i]);
            } else {
                sort_spec[field_idx] = 1;
                numeric_spec[field_idx] = (strchr(argv[i], 'n') != 0);
                reverse_spec[field_idx] = (strchr(argv[i], 'r') != 0);
                fold_spec[field_idx] = (strchr(argv[i], 'f') != 0);
                dir_spec[field_idx] = (strchr(argv[i], 'd') != 0);
            }
        }
    }

    if ((nlines = my_readlines(lineptr)) >= 0) {
        my_sep_lines(lineptr, sep_lineptr, nlines, nfields, sep);
        my_indices(indices);
        my_qsort(
            sep_lineptr,
            indices,
            0,
            nlines-1,
            sort_spec,
            numeric_spec,
            reverse_spec,
            fold_spec,
            dir_spec,
            nfields
        );
        for (int j = 0; j < 80; j++)
            putchar('-');
        putchar('\n');
        for (int j = 0; j < nlines; j++)
            printf("%s\n", lineptr[indices[j]]);
        return 0;
    }
    printf("Input too big to sort\n");
    return 1;
}


void my_sep_lines(
    char *v[MAXLINES], 
    char *sv[MAXLINES][MAXFIELDS], 
    int nlines, 
    int nfields, 
    int sep
) {
    char *src_ptr;
    for (int line_idx = 0; line_idx < nlines; line_idx++) {
        int field_idx = 0;
        int prev = sep;
        src_ptr = v[line_idx];
        while (*src_ptr != '\0' && field_idx < nfields) {
            if (prev == sep)
                sv[line_idx][field_idx++] = src_ptr;
            prev = *src_ptr++;
        }
    }
}

void my_indices(int indices[MAXLINES]) {
    for (int i = 0; i < MAXLINES; i++)
        indices[i] = i;
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
int my_readlines(char *lineptr[MAXLINES]) {
    static char allocbuf[ALLOCSIZE];
    static char *allocp = allocbuf;
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = my_getline(line, MAXLEN)) > 0) {
        if (nlines >= MAXLINES || allocp - allocbuf + len > ALLOCSIZE)
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

int my_numcmp(char *s1, char *s2) {
    double v1, v2;
    v1 = my_atof(s1);
    v2 = my_atof(s2);
    return (v1 < v2) ? -1 : (v1 > v2) ? 1 : 0;
}

void my_qsort(
    char *keys[MAXLINES][MAXFIELDS], 
    int indices[MAXLINES],
    int left, 
    int right, 
    int sort_spec[MAXFIELDS],
    int numeric_spec[MAXFIELDS],
    int reverse_spec[MAXFIELDS], 
    int fold_spec[MAXFIELDS], 
    int dir_spec[MAXFIELDS],
    int nfields
) {
    void my_swap(int indices[MAXLINES], int, int); 
    if (left >= right)
        return;
    my_swap(indices, left, (left + right) / 2);
    int last = left;

    int val;
    for (int i = left+1; i <= right; i++) {
        val = my_complex_compare(
            keys[indices[i]], 
            keys[indices[left]], 
            sort_spec,
            numeric_spec,
            reverse_spec,
            fold_spec,
            dir_spec,
            nfields
        );
        if (val < 0) {
            ++last;
            my_swap(indices, last, i);
        }
    }
    my_swap(indices, left, last);
    my_qsort(keys, indices, left, last-1, sort_spec, numeric_spec, reverse_spec, fold_spec, dir_spec, nfields);
    my_qsort(keys, indices, last+1, right, sort_spec, numeric_spec, reverse_spec, fold_spec, dir_spec, nfields);
}

int my_complex_compare(
    char *sv1[MAXFIELDS], 
    char *sv2[MAXFIELDS], 
    int sort_spec[MAXFIELDS],
    int numeric_spec[MAXFIELDS],
    int reverse_spec[MAXFIELDS], 
    int fold_spec[MAXFIELDS], 
    int dir_spec[MAXFIELDS],
    int nfields
) {
    char tv1[MAXLEN];
    char tv2[MAXLEN];
    int val;

    for (int f = 0; f < nfields; f++) {
        if (fold_spec[f]) {
            yes_fold(tv1, sv1[f]);
            yes_fold(tv2, sv2[f]);
        } else {
            no_fold(tv1, sv1[f]);
            no_fold(tv2, sv2[f]);
        }

        if (dir_spec[f]) {
            yes_dir(tv1, tv1);
            yes_dir(tv2, tv2);
        } else {
            no_dir(tv1, tv1);
            no_dir(tv2, tv2);
        }

        if (numeric_spec[f])
            val = my_numcmp(tv1, tv2);
        else
            val = strcmp(tv1, tv2);

        if (reverse_spec[f])
            val = yes_reverse(val);
        else
            val = no_reverse(val);

        if (sort_spec[f])
            if (val > 0)
                return 1;
            if (val < 0)
                return -1;
    }
    return 0;
}

void my_swap(int indices[], int i, int j) {
    int temp = indices[i];
    indices[i] = indices[j];
    indices[j] = temp;
}

int my_atoi(char *s) {
    double val;
    int sign;
    for (; isspace(*s); s++)  // skip whitespace
        ;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    for (val = 0; isdigit(*s); s++)
        val = 10 * val + (*s - '0');
    return sign * val;
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
