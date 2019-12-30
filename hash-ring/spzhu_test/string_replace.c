#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void replace(char *src, char *oldStr, char *newStr, char **newSrc)
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
	int count = 0;
	int arr[srcSize];

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
				arr[count] = i;
				count++;	
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
	printf("Found %d time of %s\n", count, oldStr);
	printf("Origina src is [%s]\n", src);

	char *finalStr;
	int finalLen = srcSize + (newStrSize - oldStrSize) * count;
	finalStr = (char *)malloc(sizeof(char) * finalLen);
	memset(tmp, 0x00, srcSize);	
	memcpy(tmp, src, arr[0] + 1 - oldStrSize);
	snprintf(finalStr, finalLen, "%s%s", tmp, newStr);
	printf("First finalStr is : %s\n", finalStr);
	
	for (j = 0; j < count-1; j++)
	{
		printf("arr[%d] = %d\n", j, arr[j]);
		memset(tmp, 0x00, srcSize);
		int copyLen = arr[j+1]-oldStrSize-arr[j];
		printf("copyLen is %d\n", copyLen);

		i = arr[j]+1;
		memcpy(tmp, src + i, copyLen);	
		strncat(finalStr, tmp, copyLen);
		printf("finalStr is : %s\n", finalStr);
		strncat(finalStr, newStr, newStrSize);
		printf("finalStr is : %s\n", finalStr);
	}

	strcat(finalStr, src+arr[count-1]+1);
	printf("finalStr is : %s\n", finalStr);

	memcpy(*newSrc, finalStr, strlen(finalStr));
	
	

	free(tmp);
	free(srcTmp);
	free(finalStr);
	
}

int main(int argc, char *argv[])
{
	char *src = "tho  shang tho thmu hi tho hai tho mmm tho";
	char *newSrc;
	char *oldStr = "tho";
	char *newStr = "thoughtyeah";
	newSrc = (char *)malloc(sizeof(char) * strlen(newStr) * strlen(src));

	replace(src, oldStr, newStr, &newSrc);
	printf("************************************************************************\n");
	printf("newSrc is [%s]\n", newSrc);

	return 0;
}
