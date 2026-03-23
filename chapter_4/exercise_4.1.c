/*
Write the function strrindex(s,t), which returns the position of the 
rightmost occurrence of t in s, or -1 if there is none. 
*/

#include <stdio.h>
#include <string.h>

// adapted from k&r section 4.1
// got rid of extraneous j variable
int strlindex(char s[], char t[]) {
    int i, k;
    for (i = 0; s[i] != '\0'; i++) {
        for (k = 0; t[k] != '\0' && s[i+k] == t[k]; k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

// right version, my impl
int strrindex(char s[], char t[]) {
    int i, k;
    int n = strlen(s);
    for (i = n-1; i >= 0; i--) {
        for (k = 0; t[k] != '\0' && s[i+k] == t[k]; k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

int main() {
    char s[] = "abcxyz";
    char t[] = "xyz";
    printf("actual: %d\n", strrindex(s, t));
    printf("expected: %d\n", 3);
    printf("\n");

    char s2[] = "abcxy";
    char t2[] = "xyz";
    printf("actual: %d\n", strrindex(s2, t2));
    printf("expected: %d\n", -1);
    printf("\n");

    char s3[] = "abcxy";
    char t3[] = "y";
    printf("actual: %d\n", strlindex(s3, t3));
    printf("expected: %d\n", 4);
    printf("\n");
}
