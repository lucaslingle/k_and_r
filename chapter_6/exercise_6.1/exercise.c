/*
Our version of getword does not properly handle underscores, 
string constants, comments, or preprocessor control lines. 
Write a better version.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXWORD 100

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
int getword(char *, int);
int binsearch(char *, struct key *, int);

enum { 
    OUTSIDE, 
    WORD, 
    STRING_LITERAL, 
    INLINE_COMMENT, 
    MULTILINE_COMMENT, 
    CTRL_LINE_TYPE, 
    IMPORT_NAME
};

int main() {
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    return 0;
}

int binsearch(char *word, struct key tab[], int n) {
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
