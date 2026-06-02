/*
Modify the fsize program to print the other information
contained in the inode entry.
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define NAME_MAXLEN 14
typedef struct {
    long ino;               // inode number
    char name[NAME_MAXLEN+1];  // dirname + null byte at end
} Dirent;

typedef struct {
    int fd;
    Dirent d;
} DIR;

DIR *opendir(char *dirname);
Dirent *readdir(DIR *dfd);
void closedir(DIR *dfd);

void fsize(char *);
int stat(char *, struct stat *);
void dirwalk(char *, void (*fcn)(char *));

int main(int argc, char *argv[]) {
    if (argc == 1)
        fsize(".");
    else
        while (--argc > 0)
            fsize(*++argv);
    return 0;
}

void fsize(char *name) {
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, fsize);
    
    // printf("%8ld %s\n", stbuf.st_size, name);  // book
    printf("%s\n", name);                         // exercise
    printf("\t st_dev:   %li\n", stbuf.st_dev);   // exercise
    printf("\t st_ino:   %li\n", stbuf.st_ino);   // exercise
    printf("\t st_mode:  %i\n", stbuf.st_mode);   // exercise
    printf("\t st_nlink: %i\n", stbuf.st_nlink);  // exercise
    printf("\t st_uid:   %i\n", stbuf.st_uid);    // exercise
    printf("\t st_gid:   %i\n", stbuf.st_gid);    // exercise
    printf("\t st_rdev:  %li\n", stbuf.st_rdev);  // exercise
    printf("\t st_size:  %li\n", stbuf.st_size);  // exercise
    printf("\t st_atime: %li\n", stbuf.st_atime); // exercise
    printf("\t st_mtime: %li\n", stbuf.st_mtime); // exercise
    printf("\t st_ctime: %li\n", stbuf.st_ctime); // exercise
}

#define PATH_MAXLEN 1024
void dirwalk(char *dir, void (*fcn)(char *)) {
    char name[PATH_MAXLEN];
    Dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, "..") == 0)
            continue;
        if (strlen(dir)+strlen(dp->name)+2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s/%s too long", dir, dp->name);
        else {
            sprintf(name, "%s/%s", dir, dp->name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}

// NOTE: Everything below here is written for V7 and SysV Unix
// The goal is to impl opendir, readdir, writedir for those systems 
//   in a way that will present a platform-independent interface via Dirent.  
// On other systems, the impl of pendir, readdir, writedir will differ. 
#ifndef DIRSIZ
#define DIRSIZ 14
#endif
struct direct {
    ino_t d_ino;         // inode number, ino_t is typedef'd in sys/types.h
    char d_name[DIRSIZ]; // no ending null byte
}

int fstat(int fd, struct stat *);

DIR *opendir(char *dirname) {
    int fd;
    struct stat stbuf;
    DIR *dp;

    if ((fd = open(dirname, O_RDONLY, 0)) == -1
        || fstat(fd, &stbuf) == -1
        || (stbuf.st_mode & S_IFMT) != S_IFDIR
        || (dp = (DIR *) malloc(sizeof(DIR))) == NULL)
        return NULL;
    dp->fd = fd;
    return dp;
}

void closedir(DIR *dp) {
    if (dp) {
        close(dp->fd);
        free(dp);
    }
}

#include <sys/dir.h>
Dirent *readdir(DIR *dp) {
    struct direct dirbuf;
    static Dirent d;

    while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
        if (dirbuf.d_ino == 0)  // inode zero indicates removed, so skip
            continue;
        d.ino = dirbuf.d_ino;
        strncpy(d.name, dirbuf.d_name, DIRSIZ);
        d.name[DIRSIZ] = '\0';
        return &d;
    }
    return NULL;
}

