/*
Write an alternate version of squeeze(s1, s2) that deletes each character in s1 
that matches any character in the string s2. 

// original version only applies to a single char c:
//
void squeeze(char s[], int c) {
    int i, j;
    for (i = j = 0; s[i] != '\0'; i++) {
        if (s[i] != c) {
            s[j++] = s[i];
        }
    }
    s[j] = '\0';
}
*/

#include <stdio.h>

void squeeze(char s1[], char s2[]) {
    int i, j, k, match;
    match = 0;
    for (i = j = 0; s1[i] != '\0'; i++) {
        for (k = 0; s2[k] != '\0'; k++) {
            if (s1[i] == s2[k]) {
                match = 1;
                break;
            } else {
                match = 0;
            }
        }
        if (!match) {
            s1[j++] = s1[i];
        }
    }
    s1[j] = '\0';
}

int main() {
    char s1[] = "Hello World!";
    char s2[] = "aeiouAEIOU";
    squeeze(s1, s2);
    printf("%s\n", s1);
}