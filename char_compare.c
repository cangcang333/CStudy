/*************************************************************************
	> File Name: char_compare.c
	> Author: 
	> Mail: 
	> Created Time: 五  6/ 1 20:36:21 2018
 ************************************************************************/

#include <stdio.h>

#define PACK_MGM_REQ  3


int main(int argc, char *argv[])
{
    int typeMgm = toascii(PACK_MGM_REQ);
    printf("typeMgm is %d\n", typeMgm);

    char ch = toascii(PACK_MGM_REQ);

    printf("ch = %c\n", ch);
    printf("typeMgm = %c\n", typeMgm);
    if (typeMgm == ch)
        printf("Equal\n");
    else
        printf("Shit\n");


    return 0;
}

