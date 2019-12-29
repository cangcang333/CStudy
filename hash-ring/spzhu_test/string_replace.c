#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//char *replace(char *src, char *oldStr, char *newStr)
void replace(char *src, char *oldStr, char *newStr)
{

	printf("strlen(%s) is %d and strlen(%s) is %d and strlen(%s) is %d\n", oldStr, strlen(oldStr), newStr, strlen(newStr), src, strlen(src));
	char *tmp;
	char *srcTmp;
	tmp = (char *)malloc(strlen(src));
	srcTmp = (char *)malloc(2 * strlen(src));

	int oldStrSize = strlen(oldStr);
	int newStrSize = strlen(newStr);
	int srcSize = strlen(src);

	int i = 0, j = 0;

	// Pass the situation of oldStr longer than src
	printf("print newStr for test\n");	
	for (j = 0; j < newStrSize; j++)
	{
		printf("%c\t", *(newStr+j));
	}
	printf("\n");

	for (i = 0, j = 0; i < srcSize; i++)
	{
		if (*(src+i) == *(oldStr+j))
		{
			if (j == oldStrSize - 1)
			{
				printf("Got 1 same, i = %d\n", i);
				memcpy(tmp, src, i + 1 - oldStrSize);
				printf("tmp is : %s, src+i is: %s\n", tmp, src+i+1);
				snprintf(srcTmp, 2 * strlen(src), "%s%s%s", tmp, newStr, src+i+1);
				printf("srcTmp is : %s\n", srcTmp);
				
				j = 0;
			}
			else
			{
				j++;
			}
		}
		else
		{
			j = 0;
		}
	}

	free(tmp);
	free(srcTmp);
	
}

int main(int argc, char *argv[])
{
	char *src = "shang tho thmu hi tho hai";
	char *oldStr = "tho";
	char *newStr = "thoughtyeah";

	replace(src, oldStr, newStr);

	// Expected output string after replace is "thought thmu hi thought hai";


	return 0;
}
