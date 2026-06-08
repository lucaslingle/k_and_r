/*
The standard library function calloc(n, size) returns a pointer to n objects of size n, 
with storage initialized to zero. Write calloc, by calling malloc or modifying it. 
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef long Align;         // for alignment to long boundary
typedef union header {      // block header
    struct {
        union header *ptr;  // next block if on free list
        unsigned size;      // size of this block
    } s;
    Align x;                // force alignment of blocks
} Header;

static Header base;           // empty list to get started
static Header *freep = NULL;  // start of free list
Header *my_morecore(unsigned);
void my_free(void *);

int get_nunits(unsigned nbytes) {
    return (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;
}

void *my_malloc(unsigned nbytes) {
    Header *p, *prevp;
    unsigned nunits= get_nunits(nbytes);

    if ((prevp = freep) == NULL) {  // no free list yet, use base block.
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {    // big enough
            if (p->s.size == nunits)  // exactly
                prevp->s.ptr = p->s.ptr;
            else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p+1);
        }
        if (p == freep)     // wrapped around free list
            if ((p = my_morecore(nunits)) == NULL)  // adds to free list, returns freep or NULL
                return NULL;    // no space
    }
}

#define NALLOC 1024
Header *my_morecore(unsigned nu) {
    char *cp;
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1)  // no space
        return NULL;
    up = (Header *) cp;
    up->s.size = nu;
    my_free((void *)(up+1));
    return freep;
}

void my_free(void *ap) {
    Header *bp, *p;

    bp = (Header *)ap - 1; // point to block header
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;
    
    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
}

// code above is equivalent to book, with get_nunits refactored out of malloc.
// code below is mine.
void *my_calloc(int n, int size) {
    int nbytes_requested = n * size;
    char *p = (char *) my_malloc(nbytes_requested);

    int nunits = get_nunits(nbytes_requested);
    int nbytes_received = (nunits-1) * sizeof(Header);  // exclude header
    for (int i = 0; i < nbytes_received; i++)
        p[i] = 0;
    return (void *) p;
}

int main(int argc, char *argv[]) {
    int n = 10;
    int size = 10;

    int nbytes_requested = n * size;
    int nunits = get_nunits(nbytes_requested);
    int nbytes_received = (nunits-1) * sizeof(Header);  // exclude header

    printf("malloc\n");
    void *p = my_malloc(n * size);
    char *pc = (char *) p;
    for (int i = 0; i < 100; i++)
        printf("%d ", pc[i]);
    printf("\n");
    for (int i = nbytes_received-100; i < nbytes_received; i++)
        printf("%d ", pc[i]);
    printf("\n");

    printf("calloc\n");
    p = my_calloc(n, size);
    pc = (char *) p;
    for (int i = 0; i < 100; i++)
        printf("%d ", pc[i]);
    printf("\n");
    for (int i = nbytes_received-100; i < nbytes_received; i++)
        printf("%d ", pc[i]);
    printf("\n");

    // the docs say sbrk zeros out memory that is newly added anyway, 
    // so we may not need to zero it in my_calloc. 
    //
    // exception is if sbrk is ever called with negative increment, 
    // then called with positive, the memory will not be rezeroed.
    //
    // i will keep zeroing out in my_calloc for the absurd hypothetical 
    // where the user is also calling sbrk on their own. 

    return 0;
}
