/*************************************************************************
	> File Name: double_pointer_test1.c
	> Author: 
	> Mail: 
	> Created Time: Sun Jul  1 21:22:35 2018
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define ROW    2
#define COLUMN 3

int main(int argc, char **argv)
{
    int **b = (int **)malloc(sizeof(int *) * ROW);

    int i;
    for (i = 0; i < ROW; i++)
    {
        b[i] = (int *)malloc(sizeof(int) * COLUMN);
    }
    
    b[0][0] = 23;
    b[0][1] = 33;
    b[0][2] = 43;
    b[1][0] = 55;
    b[1][1] = 65;
    b[1][2] = 75;

    printf("b = %p\n", b);
    printf("&b = %p\n", &b);
    printf("*b = %p\n", *b);
    printf("&(*b) = %p\n", &(*b));
    printf("&(*(b+1)) = %p\n", &(*(b+1)));
    printf("*b+1 = %p\n", *b+1);
    printf("*(b+1) = %p\n", *(b+1));
    printf("**b = %d\n", **b);
    printf("&(b[0][0]) = %p\n", &(b[0][0]));
    printf("&(b[0][1]) = %p\n", &(b[0][1]));
    printf("&(b[1][0]) = %p\n", &(b[1][0]));
    printf("&(b[1][1]) = %p\n", &(b[1][1]));


    return 0;
}
