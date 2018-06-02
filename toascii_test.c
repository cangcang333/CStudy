/*
 * This program prints encoding of the 8-bit US-ASCII characters
 * 0x5c to 0x62 are mapped to by toascii().
 */

#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int ch;

    for (ch = 0x5c; ch < 0x63; ch++)
    {
        printf("toascii(%#04x) = %c\n", ch, toascii(ch));
    }

    return 0;
}
