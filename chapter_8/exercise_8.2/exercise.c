/*
Rewrite fopen and _fillbuf with [bit] fields instead of 
explicit bit operations. Compare code size and execution speed.
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define EOF      (-1)
#define BUFSIZ   1024
#define OPEN_MAX 20  // max num files open at once

enum _flags {
    _READ  = 01,
    _WRITE = 02,
    _UNBUF = 04,
    _EOF   = 010,
    _ERR   = 020
};

// see k&r page 150 for reference on bit fields.
// make bitwidth-1 fields each for the five flags.
typedef struct _flagbits {
    unsigned int read : 1;
    unsigned int write : 1;
    unsigned int unbuf : 1;
    unsigned int eof : 1;
    unsigned int err : 1;
} FLAGBITS;

typedef struct my_iobuf {
    int cnt;
    char *ptr;
    char *base;
    FLAGBITS flag;
    int fd;
} FILE;
FILE my_iob[OPEN_MAX] = {
    { 0, (char *) 0, (char *) 0, (FLAGBITS) { 1, 0, 0, 0, 0 }, 0},
    { 0, (char *) 0, (char *) 0, (FLAGBITS) { 0, 1, 0, 0, 0 }, 1},
    { 0, (char *) 0, (char *) 0, (FLAGBITS) { 0, 1, 1, 0, 0 }, 2},
};

#define stdin  (&my_iob[0])
#define stdout (&my_iob[1])
#define stderr (&my_iob[2])

int _fillbuf(FILE *);

#define feof(p)    (((p)->flag.eof) != 0)
#define ferror(p)  (((p)->flag.err) != 0)
#define fileno(p)  ((p)->fd)

#define getc(p)    (--(p)->cnt >= 0 \
                    ? (unsigned char) *(p)->ptr++ : my_fillbuf(p))
#define getchar()  getc(stdin)
#define PERMS 0666

FILE *my_fopen(char *name, char *mode) {
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = my_iob; fp < my_iob + OPEN_MAX; fp++)
        if (!fp->flag.read && !fp->flag.write)  // found free slot
            break;
    if (fp >= my_iob + OPEN_MAX)
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1)
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (FLAGBITS) { 0, 0, 0, 0, 0 }; 
    if (*mode == 'r')
        fp->flag.read = 1;
    else
        fp->flag.write = 1;
    return fp;
}

int my_fillbuf(FILE *fp) {
    int bufsize;

    if (!fp->flag.read || fp->flag.write || fp->flag.err)
        return EOF;
    bufsize = (fp->flag.unbuf) ? 1 : BUFSIZ;
    if (fp->base == NULL)  // no buffer allocd yet
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;  // cant get buffer
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag.eof = 1;
        else
            fp->flag.err = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

int main(int argc, char *argv[]) {
    FILE *fp = my_fopen(argv[1], "r");
    int c = my_fillbuf(fp);
    return 0;
}
