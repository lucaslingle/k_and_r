/*
Design and write _flushbuf, fflush, and fclose.
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

typedef struct my_iobuf {
    int cnt;
    char *ptr;
    char *base;
    int flag;
    int fd;
} FILE;
FILE my_iob[OPEN_MAX] = {
    { 0, (char *) 0, (char *) 0, _READ, 0},
    { 0, (char *) 0, (char *) 0, _WRITE, 1},
    { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2},
};

#define stdin  (&my_iob[0])
#define stdout (&my_iob[1])
#define stderr (&my_iob[2])

int my_fillbuf(FILE *);
int my_flushbuf(int, FILE *);

#define feof(p)    (((p)->flag & _EOF) != 0)
#define ferror(p)  (((p)->flag & _ERR) != 0)
#define fileno(p)  ((p)->fd)

#define getc(p)    (--(p)->cnt >= 0 \
                    ? (unsigned char) *(p)->ptr++ : my_fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 \
                    ? *(p)->ptr++ = (x) : my_flushbuf((x), p))
#define getchar()  getc(stdin)
#define putchar(x)  putc((x), stdout)
#define PERMS 0666

FILE *my_fopen(char *name, char *mode) {
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = my_iob; fp < my_iob + OPEN_MAX; fp++)
        if ((fp->flag & (_READ | _WRITE)) == 0)  // found free slot
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
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}

int my_fillbuf(FILE *fp) {
    int bufsize;

    if ((fp->flag & (_READ | _WRITE | _ERR)) != _READ)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL)  // no buffer allocd yet
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;  // cant get buffer
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

int my_flushbuf(int x, FILE *fp) {
    int bufsize;

    if ((fp->flag & (_READ | _WRITE | _ERR)) != _WRITE)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ; // decides if fp buf has size 1
    if (fp->base == NULL) {  // no buffer allocd yet
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;  // cant get buffer
        fp->cnt = bufsize;
        fp->ptr = fp->base;
        *fp->ptr++ = x;
        fp->cnt--;
        return 0;
    } else {
        int added = 0;
        if (fp->cnt > 0) {
            *fp->ptr++ = x;
            fp->cnt--;
            added = 1;
        }
        if (write(fp->fd, fp->base, bufsize - fp->cnt) != bufsize - fp->cnt) {
            fp->flag |= _ERR;
            return EOF;
        }
        fp->cnt = bufsize;
        fp->ptr = fp->base;
        if (!added) {
            *fp->ptr++ = x;
            fp->cnt--;
        }
        return 0;
    }
}

int my_fflush(FILE *fp) {
    int bufsize;

    if ((fp->flag & (_READ | _WRITE | _ERR)) != _WRITE)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ; // decides if fp buf has size 1
    if (fp->base == NULL) {  // no buffer allocd yet
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;  // cant get buffer
        fp->ptr = fp->base;
    }
    if (write(fp->fd, fp->base, bufsize - fp->cnt) != bufsize - fp->cnt) {
        fp->flag |= _ERR;
        return EOF;
    }
    fp->cnt = bufsize;
    fp->ptr = fp->base;
    return 0;
}

int my_fclose(FILE *fp) {
    // flush before closing
    int ret = my_fflush(fp);
    // fp is an element of my_iob, we gotta free it up for fopen 
    // by setting read and write flag bits to zero. 
    fp->flag &= ~_READ;
    fp->flag &= ~_WRITE;
    // free up file descriptor with os
    int ret2 = close(fp->fd);
    // indicate if any errors
    return (ret != 0 || ret2 != 0) ? -1 : 0;
}

int main(int argc, char *argv[]) {
    FILE *fp = my_fopen(argv[1], "a");
    putc('\n', fp);
    putc('\n', fp);
    char *s = argv[2];
    for (; *s; s++)
        putc(*s, fp);
    putc('\n', fp);
    putc('\n', fp);
    int status = my_fclose(fp);
    putchar('0' + status);
    putchar('\n');
    return status;
}
