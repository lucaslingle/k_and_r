/*
Write a function undef that will remove a name and definition 
from the table maintained by lookup and install.
*/

#define HASHSIZE 101
#define HASHCONST 31

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
}
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
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else  // already there, must update defn
        free((void *) np->defn);
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

void undef(char *s) {
    struct nlist *prev = NULL;
    struct nlist *node = hashtab[hash(s)];

    while (node) {
        if (strcmp(s, node->name) == 0) {
            if (prev == NULL)
                hashval[hash(s)] = node->next;
            else
                prev->next = node->next;
            free((void *) node);
        }
        prev = node;
        node = node->next;
    }
}
