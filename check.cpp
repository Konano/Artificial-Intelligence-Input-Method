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
	ifstream fin1("output.txt");
	ifstream fin2("answer.txt");
	ofstream fout("result.txt");
	
	string str1, str2; int tot=0, wrong=0;
	while (getline(fin1, str1) && str1 != "" && getline(fin2, str2) && str2 != "")
	{
		int tmpwrong=wrong;
		int L=str1.length();
		tot+=L/2;
		
		for(int i=0; i<L; i+=2)
			if (str1[i]!=str2[i] || str1[i+1]!=str2[i+1])
				wrong++;
		if (wrong != tmpwrong)
			fout << str2 << endl << str1 << endl << endl;
	}
	fout << "==============================================" << endl;
	fout << "总数：" << tot << endl;
	fout << "正确率：" << 1.0*(tot-wrong)/tot*100 << "%" << endl;
	return 0;
}