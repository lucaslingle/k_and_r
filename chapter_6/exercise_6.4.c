/*
Write a program that prints the distinct words in its input 
sorted into decreasing order of frequency of occurrence. 
Precede each word by its count. 
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXWORD 100

int getword(char *, int);
int getch(void);
void ungetch(int);

int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;
    while (isspace(c = getch()))
        ;
    if (c == EOF)
        return -1;
    *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return 1;
    }
    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return 0;
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

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};
struct tnode *talloc(void);
char *my_strdup(char *);

struct tnode *add_tree(struct tnode *p, char *w) {
    int cond;
    if (p == NULL) {
        p = talloc();
        p->word = my_strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
        return p;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = add_tree(p->left, w);
    else
        p->right = add_tree(p->right, w);
    return p;
}

struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *my_strdup(char *s) {
    char *p;
    p = (char *) malloc(strlen(s)+1);  // +1 for trailing '\0'
    if (p != NULL)
        strcpy(p, s);
    return p;
}

void print_line(int ell) {
    for (int i = 0; i < ell; i++)
        putchar('-');
    putchar('\n');
}

int tree_to_count(struct tnode *p) {
    int nr_nodes = 0;
    if (p != NULL) {
        nr_nodes += tree_to_count(p->left);
        nr_nodes += 1;
        nr_nodes += tree_to_count(p->right);
    }
    return nr_nodes;
}

void tree_to_unsorted_pointer_array(struct tnode *p, struct tnode *a[], int is_root) {
    static int idx = 0;
    if (p != NULL) {
        a[idx++] = p;
        tree_to_unsorted_pointer_array(p->left, a, 0);
        tree_to_unsorted_pointer_array(p->right, a, 0);
    }
    if (is_root)
        idx = 0;
}

void swap(struct tnode *a[], int i, int j) {
    struct tnode *temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void qsort_pointer_array_by_count(struct tnode *a[], int left, int right) {
    int i, last;
    if (left >= right)
        return;
    swap(a, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((a[i]->count) > (a[left]->count))
            swap(a, ++last, i);
    swap(a, left, last);
    qsort_pointer_array_by_count(a, left, last-1);
    qsort_pointer_array_by_count(a, last+1, right);
}

int main(int argc, char *argv[]) {
    struct tnode *root = NULL;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != -1)
        if (isalpha(word[0]))
            root = add_tree(root, word);
    int nr_nodes = tree_to_count(root);
    struct tnode **arr = malloc(nr_nodes * sizeof(struct tnode *));
    tree_to_unsorted_pointer_array(root, arr, 1);
    qsort_pointer_array_by_count(arr, 0, nr_nodes-1);
    print_line(80);
    for (int i = 0; i < nr_nodes; i++)
        printf("%d: %s\n", arr[i]->count, arr[i]->word);
    return 0;
}
