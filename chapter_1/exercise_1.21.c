/*
Write a program entab that replaces strings of blanks by the minimum number 
of tabs and blanks to achieve the same spacing. 
Use the same tab stops as for the previous problem. 

When either a tab or a single blank would suffice to reach a tab stop, 
which should be given preference? 
*/

#include <stdio.h>
#define N 8

// note: my code assumes no tab chars included in the input, only allows in output.
int main() {
    int c, space_streak, line_offset;
    space_streak = 0;
    line_offset = 0;

    while ((c = getchar()) != EOF) {
        if (space_streak > 0 && line_offset % N == 0) {
            // putchar('0');
            putchar('\t');
            space_streak = 0;
        }
        
        if (c == ' ') {
            // putchar('1');
            space_streak++;
            line_offset++;
        } else {
            // putchar('2');
            putchar(c);
            space_streak = 0;
            line_offset++;
        }
    }
}
