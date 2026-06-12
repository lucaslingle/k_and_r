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
        union header *ptr;    // next block if on free list
        unsigned bytes;     // size of this block in bytes
    } s;
    Align x;                // force alignment of blocks
} Header;

static Header base = {};      // empty object to get started
static Header *freep = NULL;  // start of free list
Header *my_morecore(unsigned);
void my_free(void *);

void *my_malloc(unsigned nbytes) {
    Header *p, *prevp;

    if (nbytes == 0) {
        fprintf(stderr, "my_malloc: encountered invalid request size %d.\n", nbytes);
        // exit(1);
    }

    if ((prevp = freep) == NULL) {  // no free list yet, use base block.
        base.s.ptr = freep = prevp = &base;
        base.s.bytes = sizeof(Header);
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.bytes >= sizeof(Header) + nbytes) {    // big enough
            if (p->s.bytes == sizeof(Header) + nbytes)  // exactly
                prevp->s.ptr = p->s.ptr;
            else {
                p->s.bytes -= sizeof(Header) + nbytes;
                p = (Header *)((char *)p + p->s.bytes);
                p->s.bytes = sizeof(Header) + nbytes;
            }
            freep = prevp;
            return (void *)((char *)p + sizeof(Header));
        }
        if (p == freep)     // wrapped around free list
            if ((p = my_morecore(sizeof(Header) + nbytes)) == NULL)  // adds to free list, maybe rets freep
                return NULL;    // no space
    }
}

#define NALLOC 1024
Header *my_morecore(unsigned nu) {
    char *p;
    Header *hp;

    if (nu < NALLOC)
        nu = NALLOC;
    p = sbrk(nu);
    if (p == (char *) -1)  // no space
        return NULL;
    hp = (Header *) p;
    hp->s.bytes = nu;
    my_free((void *)(p + sizeof(Header)));
    return freep;
}

void my_free(void *ap) {
    Header *bp, *p;
    bp = (Header *)((char *)ap - sizeof(Header)); // point to block header

    if (bp->s.bytes == 0) {
        fprintf(stderr, "my_free: encountered invalid byte size %d in block header.\n", bp->s.bytes);
        // exit(1);
    }
    if (freep == NULL) {  // no free list yet, use base block.
        base.s.ptr = freep = &base;
        base.s.bytes = sizeof(Header);
    }

    // find a free block pointer p such that bp between p and p->s.ptr
    for (p = freep; !(p < bp && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (p < bp || bp < p->s.ptr))
            break;
    
    if ((char *)bp + bp->s.bytes == (char *)p->s.ptr) {
        bp->s.bytes += p->s.ptr->s.bytes;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    if ((char *)p + p->s.bytes == (char *)bp) {
        p->s.bytes += bp->s.bytes;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
}

void my_bfree(char *q, int n) {
    if (n < sizeof(Header)) {
        fprintf(stderr, "bfree: char array size %d too small to free with header info.\n", n);
        // exit(1);
    }
    if (freep == NULL) {  // no free list yet, use base block.
        base.s.ptr = freep = &base;
        base.s.bytes = sizeof(Header);
    }

    Header *bp, *p;
    bp = (Header *) q;
    bp->s.bytes = n;

    // find a free block pointer p such that bp between p and p->s.ptr
    for (p = freep; !(p < bp && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (p < bp || bp < p->s.ptr))
            break;
    
    if ((char *)bp + bp->s.bytes == (char *)p->s.ptr) {
        bp->s.bytes += p->s.ptr->s.bytes;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    if ((char *)p + p->s.bytes == (char *)bp) {
        p->s.bytes += bp->s.bytes;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
}

int main(int argc, char *argv[]) {
    printf("Header size: %lu\n", sizeof(Header));

    char arr[100] = "ABCDEFGHIJKLMNOPQRSTUVWX1ABCDEFGHIJKLMNOPQRSTUVWX2ABCDEFGHIJKLMNOPQRSTUVWX3ABCDEFGHIJKLMNOPQRSTUVWX4";
    my_bfree(arr, 100);

    printf("freep: %p\n", freep);
    printf("arr: %p\n", arr);

    Header *p = freep;
    char *bs;
    for (int i = 0; i < 3; i++, p = p->s.ptr) {
        printf("Block %d: %p, %d\n", i, p, p->s.bytes);
        bs = (char *) p;
        putchar('\t');
        for (int j = 0; j < p->s.bytes; j++)
            putchar(*bs++);
        putchar('\n');
    }

    char *s = (char *) my_malloc(20);
    for (int j = 0; j < 20; j++)
        putchar(*s++);
    putchar('\n');

    p = freep;
    for (int i = 0; i < 3; i++, p = p->s.ptr) {
        printf("Block %d: %p, %d\n", i, p, p->s.bytes);
        bs = (char *) p;
        putchar('\t');
        for (int j = 0; j < p->s.bytes; j++)
            putchar(*bs++);
        putchar('\n');
    }

    return 0;
}
