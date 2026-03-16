/*
Write the function htoi(s), which converts a string of hexadecimal digits (including an optional 0x or 0X) into its equivalent integer value. 
The allowable digits are 0 through 9, a through f, and A through F.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int htoi(char s[]) {
    int i, j;
    int start = 0;
    int contrib = 0;
    int value = 0;

    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        start = 2;
    }
    for (i = start; i < strlen(s); i++) {
        if ('0' <= s[i] && s[i] <= '9') {
            contrib = s[i] - '0';
        } else if ('a' <= s[i] && s[i] <= 'f') {
            contrib = s[i] - 'a' + 10;
        } else if ('A' <= s[i] && s[i] <= 'F') {
            contrib = s[i] - 'A' + 10;
        }
        for (j = 0; j < i - start; j++) {
            contrib = contrib * 16L;
        }
        value = value + contrib;
    }
    return value;
}

int main() {
    char s[] = "0xFFF";
    printf("value: %d\n", htoi(s));
    return 0;
}
