/*************************************************************************
	> File Name: ascii_test.c
	> Author: 
	> Mail: 
	> Created Time: Wed Jun 13 13:38:07 2018
 ************************************************************************/

#include <stdio.h>

#define f(a, b) a##b
#define g(a)    #a
#define h(a)    g(a)

int main(int argc, char *argv[])
{
    char a = 'A';
    while(a < 127)
    {
        printf("%d = %c\n", a, a);
        a++;
    }
    /* 0 is NULL*/
    printf("%d = NULL\n", a);

    signed char b = -46;
    printf("%d\n", b);

    printf("%s\n", h(f(2, 3)));
    printf("%s\n", g(f(1, 2)));

    return 0;
}


