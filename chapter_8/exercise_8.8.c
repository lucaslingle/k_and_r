/*
Write a routing bfree(p,n) that will free an arbitrary block p of n characters
into the free list maintained by malloc and free. By using bfree, a user can add
a static or external array to the free list at any time.
*/

#include <stdio.h>
#include <stdlib.h>
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

    if (nbytes == 0) {
        fprintf(stderr, "my_malloc: encountered invalid request size %d.\n", nbytes);
        // exit(1);
    }

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

    if (bp->s.size == 0) {
        fprintf(stderr, "my_free: encountered invalid size %d in block header.\n", bp->s.size);
        // exit(1);
    }
    if (freep == NULL) {  // no free list yet, use base block.
        base.s.ptr = freep = &base;
        base.s.size = 0;
    }

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

void my_bfree(void *q, int n) {
    if (n < 2 * sizeof(Header)) {
        fprintf(stderr, "bfree: encountered invalid size %d.\n", n);
        // exit(1);
    }
    if (freep == NULL) {  // no free list yet, use base block.
        base.s.ptr = freep = &base;
        base.s.size = 0;
    }

    Header *bp = (Header *) q;
    bp->s.size = n / sizeof(Header);

    Header *p;
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;
    
    if (bp + bp->s.size == p->s.ptr) {
        // printf("case 0");
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else {
        // printf("case 1");
        bp->s.ptr = p->s.ptr;
    }
    if (p + p->s.size == bp) {
        // printf("case 2");
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        // printf("case 3");
        p->s.ptr = bp;
    }
    freep = p;
}

int main(int argc, char *argv[]) {
    printf("Header size: %lu\n", sizeof(Header));

    char arr[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYABCDEFGHIJKLMNOPQRSTUVWXYABCDEFGHIJKLMNOPQRSTUVWXYABCDEFGHIJKLMNOPQRSTUVWX\0";
    my_bfree(arr, 100);

    printf("freep: %p\n", freep);
    printf("arr: %p\n", arr);

    int i = 0;
    Header *p = freep;
    for (; ; i++, p = p->s.ptr) {
        printf("Block %d: %p, %d\n", i, p, p->s.size);
        if (p != freep)
            break;
    }

    char *s = (char *) my_malloc(20);
    printf("strlen(s): %lu\n", strlen(s));
    printf("s: %s\n", s);

    return 0;
}
