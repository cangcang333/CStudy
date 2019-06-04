#include <iostream>
#include <fstream>
#include <string>



using namespace std;

map<int, int> gbk2Ebcdic;
map<int, int> ebcdic2Gbk;
vector<int> ebcdic2GbkChar;
vector<int> ebcdic2GbkInt;


/* Initial the EBCDIC and GBK mapping */
int initEbcdicGBKMapping()
{
	ifstream infile("GBK");
	string line;
	while (getline(infile, line))
	{
		string gbkChar = line.substr(0, 4);
		int gbkInt = stoi(gbkChar);
		string ebcdicChar = line.substr(4, 4);
		int ebcdicInt = stoi(ebcdicChar);
		
		gbk2Ebcdic.insert(pair<int, int> (gbkInt, ebcdicInt));
		ebcdic2Gbk.insert(pair<int, int> (ebcdicInt, gbkInt));	
	}

	map<int, int>::iterator iter;
	iter = ebcdic2Gbk.begin();
	while (iter != ebcdic2Gbk.end())
	{
		int i = stoi(iter);  
	}
	
	return 0;
}


int main(int argc, char **argv)
{
	string msg = "0e5069586a55de4d9c559b586a4a4c55cf0f";
	string rsp = ebcdicToGBK(msg);
	cout << "EBCDIC to GBK rsp: " << rsp << endl;
	
	

	return 0;
}

