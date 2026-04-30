/*
Write a program that reads a C program and prints in alphabetical order
each group of variable names that are identical in the first 6 characters,
but different somewhere thereafter. Don't count words within strings and comments.
Make 6 a parameter that can be set from the command line.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct key {
    char *word;
    int count;
};

struct key keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "do", 0,
    "double", 0,
    "else", 0,
    "enum", 0,
    "extern", 0,
    "float", 0,
    "for", 0,
    "goto", 0,
    "if", 0,
    "int", 0,
    "long", 0,
    "register", 0,
    "return", 0,
    "short", 0,
    "signed", 0,
    "sizeof", 0,
    "static", 0,
    "struct", 0,
    "switch", 0,
    "typedef", 0,
    "union", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0,
};
#define NKEYS (sizeof keytab / sizeof keytab[0])
#define MAXWORD 100

int getword(char *, int);
int keyword_binsearch(char *, struct key *, int);
int getch(void);
void ungetch(int);
int my_atoi(char *s);

enum { 
    OUTSIDE, 
    WORD, 
    STRING_LITERAL, 
    INLINE_COMMENT, 
    MULTILINE_COMMENT, 
    CTRL_LINE_TYPE, 
    IMPORT_NAME
};

int keyword_binsearch(char *word, struct key tab[], int n) {
    int cond;
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int getword(char *word, int lim) {
    int getch(void);
    void ungetch(int);
    char *w = word;
    static int consec_backslashes = 0;
    static int c_tm1 = EOF - 1;
    static int c_t = EOF - 1;
    static int state = OUTSIDE;
    static int ctrl_line = 0;
    while (state != WORD && c_t != EOF) {
        c_tm1 = c_t;
        c_t = getch();

        if (state == OUTSIDE && (isalnum(c_t) || c_t == '_'))
            state = WORD;
        else if (state == OUTSIDE && c_t == '"')
            state = STRING_LITERAL;
        else if (state == OUTSIDE && c_tm1 == '/' && c_t == '/')
            state = INLINE_COMMENT;
        else if (state == OUTSIDE && c_tm1 == '/' && c_t == '*')
            state = MULTILINE_COMMENT;
        else if (state == OUTSIDE && c_t == '#') {
            state = CTRL_LINE_TYPE;
            ctrl_line = 1;
        } else if (state == OUTSIDE && ctrl_line && c_t == '<')
            state = IMPORT_NAME;
        else if (state == STRING_LITERAL && consec_backslashes % 2 == 0 && c_t == '"')
            state = OUTSIDE;
        else if (state == INLINE_COMMENT && c_t == '\n')
            state = OUTSIDE;
        else if (state == MULTILINE_COMMENT && c_tm1 == '*' && c_t == '/')
            state = OUTSIDE;
        else if (state == CTRL_LINE_TYPE && c_t == ' ')
            state = OUTSIDE;
        else if (state == IMPORT_NAME && c_t == '>')
            state = OUTSIDE;
        else if (state == OUTSIDE && ctrl_line && c_tm1 != '\\' && c_t == '\n')
            ctrl_line = 0;

        if (c_t == '\\')
            consec_backslashes++;
        else
            consec_backslashes = 0;
    }
    if (c_t == EOF)
        return EOF;
    *w++ = c_t;
    while (--lim > 0) {
        c_tm1 = c_t;
        c_t = getch();
        if (!isalnum(c_t) && c_t != '_') {
            ungetch(c_t);
            break;
        }
        *w++ = c_t;
    }
    *w = '\0';
    state = OUTSIDE;
    return word[0];
}

#define BUFSIZE 100
static char buffer[BUFSIZE];
static int bp = 0;
int getch(void) {
    return (bp > 0) ? buffer[--bp] : getchar();
}
void ungetch(int c) {
    if (bp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buffer[bp++] = c;
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

struct bonsai {
    char *full;
    int count;
    struct bonsai *left;
    struct bonsai *right;
};
struct tree {
    char *pre;
    int count;
    struct bonsai *fulls;
    struct tree *left;
    struct tree *right;
};
struct bonsai *balloc(void);
struct tree *talloc(void);
char *my_strdup(char *);
char *my_strndup(char *, int);

struct bonsai *add_bonsai(struct bonsai *p, char *w) {
    int cond;
    if (p == NULL) {
        p = balloc();
        p->full = my_strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
        return p;
    } else if ((cond = strcmp(w, p->full)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = add_bonsai(p->left, w);
    else
        p->right = add_bonsai(p->right, w);
    return p;
}

struct tree *add_tree(struct tree *p, char *w, int n) {
    int cond;
    if (p == NULL) {
        p = talloc();
        p->pre = my_strndup(w, n);
        p->count = 1;
        p->fulls = add_bonsai(NULL, w);
        p->left = p->right = NULL;
        return p;
    } else if ((cond = strncmp(w, p->pre, n)) == 0) {
        p->count++;
        p->fulls = add_bonsai(p->fulls, w);
    }
    else if (cond < 0)
        p->left = add_tree(p->left, w, n);
    else
        p->right = add_tree(p->right, w, n);
    return p;
}

void print_bonsai(struct bonsai *p) {
    if (p != NULL) {
        print_bonsai(p->left);
        printf("\t%s : %d\n", p->full, p->count);
        print_bonsai(p->right);
    }
}

void print_tree(struct tree *p, int k) {
    if (p != NULL && p->count > k) {
        print_tree(p->left, k);
        printf("%s : %d\n", p->pre, p->count);
        print_bonsai(p->fulls);
        print_tree(p->right, k);
    }
}

struct bonsai *balloc(void) {
    return (struct bonsai *) malloc(sizeof(struct bonsai));
}

struct tree *talloc(void) {
    return (struct tree *) malloc(sizeof(struct tree));
}

char *my_strdup(char *s) {
    char *p;
    p = (char *) malloc(strlen(s)+1);  // +1 for trailing '\0'
    if (p != NULL)
        strcpy(p, s);
    return p;
}

char *my_strndup(char *s, int n) {
    char *p;
    p = (char *) malloc(n+1);  // +1 for trailing '\0'
    if (p != NULL)
        strncpy(p, s, n);
    return p;
}

void print_line(int ell) {
    for (int i = 0; i < ell; i++)
        putchar('-');
    putchar('\n');
}

int main(int argc, char *argv[]) {
    int n;
    if (argc != 2) {
        printf("Usage:\n\t./program.o N\nwhere N is the prefix length.\n");
        exit(1);
    } else 
        n = my_atoi(argv[1]);

    struct tree *root = NULL;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((keyword_binsearch(word, keytab, NKEYS)) == -1) // wanna find varnames only
                root = add_tree(root, word, n);
    print_line(80);
    print_tree(root, 1);
    return 0;
}
