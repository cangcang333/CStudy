/*************************************************************************
	> File Name: size_test.c
	> Author: 
	> Mail: 
	> Created Time: Sat Jun  2 19:08:43 2018
 ************************************************************************/

#include <stdio.h>

int getSize(int data[])
{
    return sizeof(data);
}

int main(int argc, char *argv[])
{
    int data1[] = {2, 3, 4, 5, 6};
    int size1 = sizeof(data1);

    int *data2 = data1;
    int size2 = sizeof(data2);

    int size3 = getSize(data1);

    printf("%d, %d, %d\n", size1, size2, size3);

    return 0;
}

