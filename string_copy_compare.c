/* This program compare string compare function: memcpy and strcpy */

#include <stdio.h>
#include <string.h>

void dump5(char *str);

int main(int argc, char *argv[])
{
    char s[5] = {'s', 'a', '\0', 'c', 'h'};

    char membuff[5];
    char strbuff[5];
    memset(membuff, 0, 5);
    memset(strbuff, 0, 5);

    strcpy(strbuff, s);
    memcpy(membuff, s, 5);

    dump5(membuff);
    dump5(strbuff);

    return 0;
}

void dump5(char *str)
{
    int n = 0;
    char *p = str;
    for (n = 0; n < 5; n++)
    {
        printf("%2.2x ", *p);
//        printf("%3.2x ", *p);
        ++p;
    }
    
    printf("\t");

    p = str;
    for (n = 0; n < 5; n++)
    {
        printf("%c", *p ? *p : ' ');
        ++p;
    }

    printf("\n", str);
}
