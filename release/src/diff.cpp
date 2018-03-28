#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <string>
#include <cmath>

using namespace std;

inline void ERROR(int x)
{
	if (x == 1) puts("过多参数。");
	if (x == 2) puts("过少参数，请指定标准文件和待比较文件的路径。");
	if (x == 2) puts("例如 pinyin ../data/answer.txt ../data/output.txt");
	if (x == 3) puts("找不到标准文本。");
	if (x == 4) puts("找不到待比较文本。");
	exit(1);
}

int main(int argc, char** argv)
{
	if (argc > 3) ERROR(1);
	if (argc < 3) ERROR(2);

	ifstream fin1(argv[2]); if (!fin1) ERROR(4);
	ifstream fin2(argv[1]); if (!fin2) ERROR(4);
	ofstream fout("../result.txt");

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
	fout << "单字总数：" << tot << endl;
	fout << "正确率：" << 1.0*(tot-wrong)/tot*100 << "%" << endl;

	cout << "单字总数：" << tot << endl;
	cout << "正确率：" << 1.0*(tot-wrong)/tot*100 << "%" << endl;
	cout << "具体比较信息已经输出到主目录下的 result.txt" << endl;
	return 0;
}