#include <stdio.h>

int main(int argc, char **argv)
{
	int i = 0x8140;
	int j = 0;
	int N = 188;

	for (j = 0; j < N; j++)
	{
		if ((i+j) % 256 == 0x7F )
		{
			printf("%X\n", i+j);
			i++;
			printf("%X%X\n", i+j, i+j+1);
		}
		else
		{
			printf("%X%X\n", i+j, i+j+1);
		}
	}

	return 0;
}
