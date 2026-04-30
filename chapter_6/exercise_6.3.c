/*
Write a cross-referencer that prints a list of all words in a document,
and for each word a list of the line numbers on which it occurs.
Remove words like the, and so on.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXWORD 100

int getword(char *, int, int);
int getch(void);
void ungetch(int);

const char *stopwords[] = {
    "i",
    "me",
    "my",
    "myself",
    "we",
    "our",
    "ours",
    "ourselves",
    "you",
    "your",
    "yours",
    "yourself",
    "yourselves",
    "he",
    "him",
    "his",
    "himself",
    "she",
    "her",
    "hers",
    "herself",
    "it",
    "its",
    "itself",
    "they",
    "them",
    "their",
    "theirs",
    "themselves",
    "what",
    "which",
    "who",
    "whom",
    "this",
    "that",
    "these",
    "those",
    "am",
    "is",
    "are",
    "was",
    "were",
    "be",
    "been",
    "being",
    "have",
    "has",
    "had",
    "having",
    "do",
    "does",
    "did",
    "doing",
    "a",
    "an",
    "the",
    "and",
    "but",
    "if",
    "or",
    "because",
    "as",
    "until",
    "while",
    "of",
    "at",
    "by",
    "for",
    "with",
    "about",
    "against",
    "between",
    "into",
    "through",
    "during",
    "before",
    "after",
    "above",
    "below",
    "to",
    "from",
    "up",
    "down",
    "in",
    "out",
    "on",
    "off",
    "over",
    "under",
    "again",
    "further",
    "then",
    "once",
    "here",
    "there",
    "when",
    "where",
    "why",
    "how",
    "all",
    "any",
    "both",
    "each",
    "few",
    "more",
    "most",
    "other",
    "some",
    "such",
    "no",
    "nor",
    "not",
    "only",
    "own",
    "same",
    "so",
    "than",
    "too",
    "very",
    "can",
    "will",
    "just",
    "don't",
    "should",
    "now",
};
int NKEYS = sizeof(stopwords) / sizeof(stopwords[0]);

int getword(char *word, int lim, int line_nr) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;
    while (isspace(c = getch()))
        if (c == '\n')
            line_nr++;
    if (c == EOF)
        return -1;
    *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return line_nr;
    }
    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return line_nr;
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

struct list {
    int val;
    struct list *next;
};
struct tree {
    char *word;
    struct list *head;
    struct list *tail;
    struct tree *left;
    struct tree *right;
};
struct list *lalloc(void);
struct tree *talloc(void);
char *my_strdup(char *);

struct list *add_list(struct list *p, int val) {
    struct list *q = lalloc();
    q->val = val;
    q->next = NULL;
    if (p != NULL) {
        p->next = q;
    }
    return q;
}

struct tree *add_tree(struct tree *p, char *w, int line_nr) {
    int cond;
    if (p == NULL) {
        p = talloc();
        p->word = my_strdup(w);
        p->head = add_list(NULL, line_nr);
        p->tail = p->head;
        p->left = p->right = NULL;
        return p;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->tail = add_list(p->tail, line_nr);
    else if (cond < 0)
        p->left = add_tree(p->left, w, line_nr);
    else
        p->right = add_tree(p->right, w, line_nr);
    return p;
}

void print_list(struct list *p) {
    putchar('\t');
    while (p != NULL) {
        printf("%d, ", p->val);
        p = p->next;
    }
    putchar('\n');
}

void print_tree(struct tree *p) {
    if (p != NULL) {
        print_tree(p->left);
        printf("%s", p->word);
        print_list(p->head);
        print_tree(p->right);
    }
}

struct list *lalloc(void) {
    return (struct list *) malloc(sizeof(struct list));
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

int check_stopwords(char *w) {
    char *p0, *p;
    p0 = (char *) malloc(strlen(w)+1);  // +1 for trailing '\0'
    p = p0;
    while (*w != '\0')
        *p++ = tolower(*w++);      // fold cases
    *p = '\0';
    for (int i = 0; i < NKEYS; i++)
        if (strcmp(stopwords[i], p0) == 0)
            return 1;
    return 0;
}

void print_line(int ell) {
    for (int i = 0; i < ell; i++)
        putchar('-');
    putchar('\n');
}

int main(int argc, char *argv[]) {
    struct tree *root = NULL;
    char word[MAXWORD];

    int line_nr = 0;
    while ((line_nr = getword(word, MAXWORD, line_nr)) != -1) {
        if (isalpha(word[0]))
            if (check_stopwords(word) == 0)
                root = add_tree(root, word, line_nr);
    }
    print_line(80);
    print_tree(root);
    return 0;
}
