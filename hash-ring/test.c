#include <stdio.h>





typedef unsigned char md5_byte_t; /* 8-bit byte */
typedef unsigned int md5_word_t; /* 32-bit word */

/* Define the state of the MD5 Algorithm. */
typedef struct md5_state_s {
    md5_word_t count[2];	/* message length in bits, lsw first */
    md5_word_t abcd[4];		/* digest buffer */
    md5_byte_t buf[64];		/* accumulate block */
} md5_state_t;

#define T_MASK ((md5_word_t)~0)

int main()
{
	printf("T_MASK is %d\n", T_MASK);	
	printf("T_MASK is 0x%X\n", T_MASK);	

	printf("(~A) is 0x%X\n", (~'A'));

	return 0;
}
