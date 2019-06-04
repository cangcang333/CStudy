#include <iostream>
#include <fstream>
#include <string>
#include <iconv.h>  // for gbk/big5/utf8 
#include <string.h>

using namespace std;

int code_convert(char *from_charset, char *to_charset, char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	iconv_t cd;
	int rc;
	char **pin = &inbuf;
	char **pout = &outbuf;
	cd = iconv_open(to_charset, from_charset);
	if (cd == 0)
	{
		return -1;
	}
	memset(outbuf, 0, outlen);
	if (iconv(cd, pin, &inlen, pout, &outlen) == -1)
	{
		return -1;
	}
	iconv_close(cd);

	return 0;
}

string any2utf8(string in, string fromEncode, string toEncode)
{
	char *inbuf = (char *)in.c_str();
	int inlen = strlen(inbuf);
	int outlen = inlen * 3;  // in case unicode 3 times than ascii
	char outbuf[outlen] = {0};
	int rst = code_convert((char *)fromEncode.c_str(), (char *)toEncode.c_str(), inbuf, inlen, outbuf, outlen);
	if (rst == 0)
	{
		return string(outbuf);
	}
	else
	{
		return in;
	}
}

string string2utf8(const char *in)
{
	return any2utf8(string(in), string("gbk"), string("utf-8"));	
}

int main(int argc, char **argv)
{
	string msg = "0e5069586a55de4d9c559b586a4a4c55cf0f";
	char *gbkStr = "81408141";
	cout << string2utf8(gbkStr) << endl;
	

	return 0;
}

