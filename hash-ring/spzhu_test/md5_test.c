#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "md5.h"

int main()
{
//	uint8_t *data = "a";
//	uint8_t *data = "abc";
	uint8_t *data = "message digest";
	uint8_t dataLen = strlen(data);
	printf("data: %s\n", data);
	printf("length data is %d\n", strlen(data));
	uint8_t digest[16];
	md5_state_t state;

	md5_init(&state);
	md5_append(&state, (md5_byte_t *)data, dataLen);
	md5_finish(&state, (md5_byte_t *)&digest);

	int i = 0;
	printf("0x");
	for (i = 0; i < 16; i++)
	{
		printf("%0x", digest[i]);
	}
	printf("\n");

	

	return 0;
}

