#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <string>
#include <cmath>

using namespace std;

int main()
{
	ifstream fin("tmp.txt");
	ofstream fout1("input.txt");
	ofstream fout2("answer.txt");
	
	string str;
	while (getline(fin, str) && str != "") 
	{
		if ('A' <= str[0] && str[0] <= 'Z') str[0]=str[0]-'A'+'a';
		fout1 << str << endl;
		getline(fin, str);
		fout2 << str << endl;
	}
	return 0;
}