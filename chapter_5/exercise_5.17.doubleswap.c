/*
Add a field handling capability, so sorting may be done on fields within lines, 
each field sorted according to an independent set of options.

(The index for this book was sorted with -df for index category 
and -n for the page numbers.)

(Starting point is code from exercise 5.16.)

WORK IN PROGRESS!

MY NOTES:
we shall take invocations of the form ./program.o -nrfd, 
as well as ./program.o -c0 nrfd -c1 nrfd ...
in the former case we shall gather all text per line as field 0, ignoring the separator if it appears.
in the latter case we shall gather a subset of the text per line for each field;
    if there are not enough fields we shall produce an error.
internally, we shall use arrays to keep track of the sorting specification per field,
    and if the invocation does not specify fields, 
    we shall use index zero of each array to store the sorting spec. 

SOLUTION STRATEGY:
- initially let's assume correctly formatted input with exactly MAXFIELDS fields.
- have qsort copy the fields into a static variable, char *sv[MAXLINES][MAXFIELDS].
- define a complex_compare function that takes sv as an arg, and
    takes the bit arrays for numeric, reverse, fold, and directory order,
    and returns a variable based on the compare value of each field.
    upon reaching the first field with a definitive not equals compare, 
    we shall return its sign. if all fields compare equal, return 0.
- use this complex_compare function to make swaps on original pointer array v.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SEP '\t'
#define MAXLEN 100
#define MAXFIELDS 1
#define MAXLINES 5000                    // max lines to be sorted
char *lineptr[MAXLINES];                 // array of pointers to text lines
char *sep_lineptr[MAXLINES][MAXFIELDS];  // array of pointers to the separated values

int my_readlines(char *lineptr[MAXLINES]);
void my_sep_lines(char *lineptr[MAXLINES], char *sep_lineptr[MAXLINES][MAXFIELDS], int nlines);
int my_numcmp(char *, char *);
int my_atoi(char *s);
double my_atof(char *);
void my_qsort(
    char *keys[MAXLINES][MAXFIELDS], 
    char *values[MAXLINES], 
    int left, 
    int right, 
    int numeric_spec[MAXFIELDS],
    int reverse_spec[MAXFIELDS], 
    int fold_spec[MAXFIELDS], 
    int dir_spec[MAXFIELDS]
);
int my_complex_compare(
    char *key1[MAXFIELDS], 
    char *key2[MAXFIELDS], 
    int numeric_spec[MAXFIELDS],
    int reverse_spec[MAXFIELDS], 
    int fold_spec[MAXFIELDS], 
    int dir_spec[MAXFIELDS]
);
int yes_reverse(int);
int no_reverse(int);
void yes_fold(char *, char *);
void no_fold(char *, char *);
void yes_dir(char *, char *);
void no_dir(char *, char *);

// sort input lines
int main(int argc, char *argv[]) {
    int nlines;                    // num input lines read
    int numeric_spec[MAXFIELDS];  // 1 for numeric sort
    int reverse_spec[MAXFIELDS];  // 1 for decreasing order
    int fold_spec[MAXFIELDS];     // 1 for folded case distinctions
    int dir_spec[MAXFIELDS];      // 1 for directory order
    int field_id = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            field_id = my_atoi(argv[++i]);
            i++;
        }
        if (argv[i][0] == '-') {  // arg starts with "-"
            numeric_spec[field_id] = (strchr(argv[i], 'n') != 0);
            reverse_spec[field_id] = (strchr(argv[i], 'r') != 0);
            fold_spec[field_id] = (strchr(argv[i], 'f') != 0);
            dir_spec[field_id] = (strchr(argv[i], 'd') != 0);
            i++;
        }
    }
    if ((nlines = my_readlines(lineptr)) >= 0) {
        my_sep_lines(lineptr, sep_lineptr, nlines);
        my_qsort(
            sep_lineptr,
            lineptr,
            0, 
            nlines-1, 
            numeric_spec,
            reverse_spec,
            fold_spec,
            dir_spec
        );
        for (int j = 0; j < nlines; j++)
            printf("%s\n", lineptr[j]);
        return 0;
    }
    printf("Input too big to sort\n");
    return 1;
}

void my_sep_lines(char *v[MAXLINES], char *sv[MAXLINES][MAXFIELDS], int nlines) {
    char *src_ptr;
    for (int line_idx = 0; line_idx < nlines; line_idx++) {
        int field_idx = 0;
        int prev = SEP;
        src_ptr = v[line_idx];
        while (*src_ptr != '\0') {
            if (prev == SEP)
                sv[line_idx][field_idx++] = src_ptr;
            prev = *src_ptr++;
        }
    }
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
    char *values[MAXLINES],
    int left, 
    int right, 
    int numeric_spec[MAXFIELDS],
    int reverse_spec[MAXFIELDS], 
    int fold_spec[MAXFIELDS], 
    int dir_spec[MAXFIELDS]
) {
    void my_key_swap(char *keys[MAXLINES][MAXFIELDS], int, int); 
    void my_value_swap(char *values[MAXLINES], int, int); 
    if (left >= right)
        return;
    my_key_swap(keys, left, (left + right) / 2);
    my_value_swap(values, left, (left + right) / 2);
    int last = left;

    int cmp_val;
    for (int i = left+1; i <= right; i++) {
        cmp_val = my_complex_compare(
            keys[i],
            keys[left],
            numeric_spec,
            reverse_spec,
            fold_spec,
            dir_spec
        );
        if (cmp_val < 0) {
            ++last;
            my_key_swap(keys, last, i);
            my_value_swap(values, last, i);
        }
    }
    my_key_swap(keys, left, last);
    my_value_swap(values, left, last);
    my_qsort(keys, values, left, last-1, numeric_spec, reverse_spec, fold_spec, dir_spec);
    my_qsort(keys, values, last+1, right, numeric_spec, reverse_spec, fold_spec, dir_spec);
}

int my_complex_compare(
    char *key1[MAXFIELDS], 
    char *key2[MAXFIELDS], 
    int numeric_spec[MAXFIELDS],
    int reverse_spec[MAXFIELDS], 
    int fold_spec[MAXFIELDS], 
    int dir_spec[MAXFIELDS]
) {
    char tk1[MAXLEN];
    char tk2[MAXLEN];
    int val;

    for (int f = 0; f < MAXFIELDS; f++) {
        if (fold_spec[f]) {
            yes_fold(tk1, key1[f]);
            yes_fold(tk2, key2[f]);
        } else {
            no_fold(tk1, key1[f]);
            no_fold(tk2, key2[f]);
        }

        if (dir_spec[f]) {
            yes_dir(tk1, tk1);
            yes_dir(tk2, tk2);
        } else {
            no_dir(tk1, tk1);
            no_dir(tk2, tk2);
        }

        if (numeric_spec[f])
            val = my_numcmp(tk1, tk2);
        else
            val = strcmp(tk1, tk2);

        if (reverse_spec[f])
            val = yes_reverse(val);
        else
            val = no_reverse(val);

        if (val > 0)
            return 1;
        if (val < 0)
            return -1;
    }
    return 0;
}

void my_key_swap(char *keys[MAXLINES][MAXFIELDS], int i, int j) {
    char *temp[MAXFIELDS];
    for (int offset=0; offset<MAXFIELDS; offset++)
        temp[offset] = keys[i][offset];
    for (int offset=0; offset<MAXFIELDS; offset++)
        keys[i][offset] = keys[j][offset];
    for (int offset=0; offset<MAXFIELDS; offset++)
        keys[j][offset] = temp[offset];
}

void my_value_swap(char *values[MAXLINES], int i, int j) {
    char *temp;
    temp = values[i];
    values[i] = values[j];
    values[j] = temp;
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
