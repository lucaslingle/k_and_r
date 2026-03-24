/*
Write a routine ungets(s) that will push back an entire string onto the input. 
Should ungets know about buf and bufp, or should it just use ungetch? 
*/

// implementation 1:
// if we assume ungets will only be called once before the buffer is cleared,
// it would suffice to implement ungets to write chars to buf in reverse order via ungetch. 
// HOWEVER: this assumes the correct behavior by the user.
// 
// implementation 2:
// we can also implement ungets to use buf as a fifo queue by maintaining 
// pointers to the head and tail of the filled entries of buf. this way, 
// we can call ungets on earlier text first and later text later, and it will still work. 
//
// below i will use implementation 2.

#include <stdio.h>
#include <string.h>
#define BUFSIZE 100
#define NONE -11111

int getch_queued(void);
void ungetch_queued(int);
char buffer[BUFSIZE];
int buffer_head = NONE; // pointer to first occupied element of queue
int buffer_tail = 0; // pointer to first open slot after queue entries

int getch_queued(void) {
    int value;
    if (buffer_head == NONE) {
        return getchar();
    }
    value = buffer[buffer_head];
    buffer_head = (buffer_head == BUFSIZE - 1) ? 0 : (buffer_head+1);
    if (buffer_head == buffer_tail) {
        buffer_head = NONE;
        buffer_tail = 0;
    }   
    return value;
}

void ungetch_queued(int c) {
    if (buffer_head == NONE) {
        buffer[0] = c;
        buffer_head = 0;
        buffer_tail = 1;
        return;
    }
    if (buffer_tail == buffer_head) {
        printf("error: ungetch buffer full.\n");
        return;
    }
    buffer[buffer_tail] = c;
    buffer_tail = (buffer_tail == BUFSIZE - 1) ? 0 : (buffer_tail+1);
    return;
}

void ungets(char s[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        ungetch_queued(s[i]);
    }
}

int main() {
    char s1[4];
    s1[0] = getch_queued();
    s1[1] = getch_queued();
    s1[2] = getch_queued();
    s1[3] = '\0';
    printf("s1: %s\n", s1);

    char s2[4];
    s2[0] = getch_queued();
    s2[1] = getch_queued();
    s2[2] = getch_queued();
    s2[3] = '\0';
    printf("s2: %s\n", s2);

    ungets(s1);
    ungets(s2);

    char s3[7];
    s3[0] = getch_queued();
    s3[1] = getch_queued();
    s3[2] = getch_queued();
    s3[3] = getch_queued();
    s3[4] = getch_queued();
    s3[5] = getch_queued();
    s3[6] = '\0';
    printf("s3: %s\n", s3);
}
