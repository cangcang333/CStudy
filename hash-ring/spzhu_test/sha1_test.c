#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "sha1.h"

int main()
{
	SHA1Context sha1_ctx;
//	uint8_t *data = "message digest";
	uint8_t *data = "abc";
	uint8_t dataLen = strlen(data);
	
	SHA1Reset(&sha1_ctx);
	SHA1Input(&sha1_ctx, data, dataLen);

	if (SHA1Result(&sha1_ctx) != 1)
	{
		printf("SHA1Result failed\n");
		return -1;
	}

	int i = 0;
	for (i = 0; i < 5; i++)
	{
		printf("Message_Digest[%d] = 0x%02X\n", i, sha1_ctx.Message_Digest[i]);

	}
	printf("\n");

	uint64_t keyInt = sha1_ctx.Message_Digest[3];
	keyInt <<= 32;
	keyInt |= sha1_ctx.Message_Digest[4];
	
	printf("keyInt is 0x%02lX\n", keyInt);

	return 0;
}
