/*
Write a function expand(s1, s2) that expands shorthand notations like a-z 
in the string s1 into the equivalent complete list abc...xyz in s2. 

Allow for letters of either case and digits, and be prepared to 
handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading 
or trailing - is taken literally.
*/

#include <stdio.h>

void expand(const char s1[], char s2[]) {
    int i = 0;
    int j = 0;
    int s1_im2 = EOF;
    int s1_im1 = EOF;
    int s1_i;
    while ((s1_i = s1[i]) != '\0') {
        if (('a' <= s1_im2) && (s1_im2 <= 'z') && (s1_im1 == '-') && ('a' <= s1_i) && (s1_i <= 'z')) {
            // lower1 to lower2
            for (int k=0; k<=(s1_i-s1_im2); k++) {
                s2[j] = s1_im2 + k;
                j++;
            }
            s1_im2 = EOF;
            s1_im1 = EOF;
        } else if (('A' <= s1_im2) && (s1_im2 <= 'Z') && (s1_im1 == '-') && ('A' <= s1_i) && (s1_i <= 'Z')) {
            // upper1 to upper2
            for (int k=0; k<=(s1_i-s1_im2); k++) {
                s2[j] = s1_im2 + k;
                j++;
            }
            s1_im2 = EOF;
            s1_im1 = EOF;
        } else if (('0' <= s1_im2) && (s1_im2 <= '9') && (s1_im1 == '-') && ('0' <= s1_i) && (s1_i <= '9')) {
            // digit1 to digit2
            for (int k=0; k<=(s1_i-s1_im2); k++) {
                s2[j] = s1_im2 + k;
                j++;
            }
            s1_im2 = EOF;
            s1_im1 = EOF;
        } else if (s1_im2 != EOF) {
            s2[j] = s1_im2;
            j++;
            s1_im2 = s1_im1;
            s1_im1 = s1_i;
        } else if (s1_im2 == EOF) {
            s1_im2 = s1_im1;
            s1_im1 = s1_i;
        }
        i++;
    }

    if (s1_im2 != EOF) {
        s2[j] = s1_im2;
        j++;
    }
    if (s1_im1 != EOF) {
        s2[j] = s1_im1;
        j++;
    }
    s2[j] = '\0';
}

int main() {
    char s1[] = "a-y lmao 0-9 mountain dew a-b-c a-z0-9 -a-z";
    char s2[1000];
    char s2_prime[] = "abcdefghijklmnopqrstuvwxy lmao 0123456789 mountain dew abcdefghijklmnopqrstuvwxyz0123456789 -abcdefghijklmnopqrstuvwxyz";
    expand(s1, s2);
    printf("%s\n", s2);
    printf("%s\n", s2_prime);
}
