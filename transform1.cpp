#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <vector>
#include <iconv.h>
#include <numeric>

using namespace std;


#define LEN 23779

static map<int, int> gbk2Ebcdic;
static map<int, int> ebcdic2Gbk;

static int  gbk2EbcdicChar[LEN]= {0};
static int  gbk2EbcdicInt[LEN]= {0};

static int ebcdic2GbkChar[LEN] = {0};
static int ebcdic2GbkInt[LEN] = {0};

/*
int initEbcdictGBKMapping()
{
	ifstream infile("GBK");
	string line;
	while (getline (infile , line))
	{
		string gbkChar = line.substr(0, 4);
		unsigned int gbkInt = stoul(gbkChar, nullptr, 16);
		string ebcdicChar = line.substr(4, 4);
		int ebcdicInt = stoul(ebcdicChar, nullptr, 16);
		gbk2EbcdicChar.insert(pair<int, int> (gbkInt, ebcdicInt));
		ebcdic2Gbk.insert(pair<int, int> (ebcdicInt, gbkInt));
	
	}
	int index = 0;
	map<int, int>::iterator iter;
	iter = gbk2Ebcdic.begin();
	while (iter != gbk2Ebcdic.end())
	{
	
		gbk2EbcdicChar[index] = iter->first;
		gbk2EbcdicInt[index++] = iter->second;
		iter++;
	}

}
*/


void changeTest(unsigned char *uc, int len)
{
	//
	uc[3] = 0x99;
	uc[4] = 0x88;
	//
}


int main(int argc, char **argv)
{
	int i = 0;
	unsigned char str[7] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde};
	str[1] = 0x43;
	str[2] = 0xff;
	changeTest(str, 7);
	for (i = 0; i < 7; i++)
	{
		printf("%X\t", str[i]);
	}
	printf("\n");
}
