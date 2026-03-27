#define NUMBER 0
#define SYMBOLIC_OPERATOR 1
#define NAMED_OPERATOR 2
#define WRITE_VARIABLE 3
#define READ_VARIABLE 4
#define READ_PRINTED 5
#define NEWLINE 6

double parse_double(char []);
void push(double);
double pop(void);
int getop(char []);
// int getch(void);
// void ungetch(int);
