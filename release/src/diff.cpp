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
	if (x == 1) puts("���������");
	if (x == 2) puts("���ٲ�������ָ����׼�ļ��ʹ��Ƚ��ļ���·����");
	if (x == 2) puts("���� pinyin ../data/answer.txt ../data/output.txt");
	if (x == 3) puts("�Ҳ�����׼�ı���");
	if (x == 4) puts("�Ҳ������Ƚ��ı���");
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
	fout << "����������" << tot << endl;
	fout << "��ȷ�ʣ�" << 1.0*(tot-wrong)/tot*100 << "%" << endl;

	cout << "����������" << tot << endl;
	cout << "��ȷ�ʣ�" << 1.0*(tot-wrong)/tot*100 << "%" << endl;
	cout << "����Ƚ���Ϣ�Ѿ��������Ŀ¼�µ� result.txt" << endl;
	return 0;
}