/*
Implement a simple version of the #define processor (i.e., no arguments)
suitable for use with C programs, based on the routines of this section.
You may also find getch and ungetch helpful.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAXWORD 100
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


#define HASHSIZE 101
#define HASHCONST 31
struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};
static struct nlist *hashtab[HASHSIZE];
unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + HASHCONST * hashval;
    return hashval % HASHSIZE;
}
struct nlist *lookup(char *s) {
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}
char *_strdup(char *s) {
    char *p;
    p = (char *) malloc(strlen(s)+1);  // +1 for trailing '\0'
    if (p != NULL)
        strcpy(p, s);
    return p;
}
struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {  // not there
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = _strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else  // already there, must update defn
        free((void *) np->defn);
    if ((np->defn = _strdup(defn)) == NULL)
        return NULL;
    return np;
}

enum { 
    OUTSIDE, 
    WORD, 
    STRING_LITERAL, 
    INLINE_COMMENT, 
    MULTILINE_COMMENT, 
    CTRL_LINE_TYPE, 
    IMPORT_NAME
};

struct megastate {
    int consec_backslashes;
    int c_tm1;
    int c_t;
    int state;
    int ctrl_line;
};

void print_megastate(struct megastate *p) {
    printf("\tconsec_backslashes : %d\n", p->consec_backslashes);
    printf("\tc_tm1 : %c\n", p->c_tm1);
    printf("\tc_t : %c\n", p->c_t);
    printf("\tstate : %d\n", p->state);
    printf("\tctrl_line : %d\n", p->ctrl_line);
}

void state_transition(struct megastate *p) {
    int consec_backslashes = p->consec_backslashes;
    int c_tm1 = p->c_tm1;
    int c_t = p->c_t;
    int state = p->state;
    int ctrl_line = p->ctrl_line;

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
    else if (state == WORD && (c_t == ' ' || c_t == '\t'))
        state = OUTSIDE;
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
    else if ((state == OUTSIDE || state == WORD) && ctrl_line && c_tm1 != '\\' && c_t == '\n') {
        state = OUTSIDE;
        ctrl_line = 0;
    }

    if (c_t == '\\')
        consec_backslashes++;
    else
        consec_backslashes = 0;

    p->consec_backslashes = consec_backslashes;
    p->c_tm1 = c_tm1;
    p->c_t = c_t;
    p->state = state;
    p->ctrl_line = ctrl_line;

    // printf("State transitioned to...\n");
    // print_megastate(p);
}

int get_kv(char *key, char *value, int lim) {
    char *key0 = key;
    char *value0 = value;
    int getch(void);
    void ungetch(int);
    static struct megastate s = {
        .consec_backslashes = 0,
        .c_tm1 = EOF - 1,
        .c_t = EOF - 1,
        .state = OUTSIDE,
        .ctrl_line = 0
    };
    // print_megastate(&s);

    // til ctrl line is true and state is outside, 
    // i.e., after #define
    while (!(s.ctrl_line && s.state == OUTSIDE) && s.c_t != EOF)
        state_transition(&s);

    // skip blank space
    while (s.ctrl_line && s.state == OUTSIDE && s.c_t != EOF)
        state_transition(&s);

    // get key
    int state_key = s.state;
    while (s.ctrl_line && s.state == state_key && s.c_t != EOF) {
        *key++ = s.c_t;
        state_transition(&s);
    }
    *key = '\0';

    // skip blank space
    while (s.ctrl_line && s.state == OUTSIDE && s.c_t != EOF)
        state_transition(&s);

    // get value
    int state_value = s.state;
    while (s.ctrl_line && s.state == state_value && s.c_t != EOF) {
        *value++ = s.c_t;
        state_transition(&s);
    }
    // state tracker counts state as OUTSIDE for second double quote, must add manually.
    // fixing the state tracker creates further complications
    // omitting s.state == state_value creates further complications. 
    if (s.state == OUTSIDE && state_value == STRING_LITERAL)
        *value++ = '"';
    *value = '\0';

    if (strlen(key0) > 0 && strlen(value0) > 0) {
        install(key0, value0);
        printf("Installed key: %s, value: %s\n", key0, value0);
        printf("\tstrlen(key): %lu, strlen(value): %lu\n", strlen(key0), strlen(value0));
    }
    return (s.c_t == EOF) ? -1 : 0;
}

int main(int argc, char *argv[]) {
    char key[MAXWORD];
    char value[MAXWORD];

    while (get_kv(key, value, MAXWORD) != -1)
        ;
    return 0;
}
