#define __DEBUG
//#define FIRST

#define WORD_1
//#define WORD_2

#include "function.h"

using namespace std;

int len, text[1000];

inline void ReadInput(char *localFileName)
{
	string str, py, tmp;

	len = 1;

	localFileName[14] = 'C';
	ifstream fin(localFileName);

	if (fin) puts("Fuck");

	localFileName[14] = 'P';
	ifstream fpy(localFileName);

	while (!fin.eof())
	{
		fin >> str;
		if (str != "/")
		{
			int L = str.length() / 2;
			fpy >> py;
			for(int i = 1; i < L; i++)
				fpy >> tmp, py += '-' + tmp;
			text[len++] = Word_ID(str, py);
		}
		else
		{
			text[len++] = text[0] = 1;

			#ifdef WORD_1
			for(int j=1; j<len-1; j++) if (text[j])
				Times_1[text[j]]++;
			#endif

			#ifdef WORD_2
			for(int j=1; j<len; j++) if (text[j-1] && text[j])
				Times_2[Long(text[j-1], text[j])]++;
			#endif

			len = 1;
		}
	}
}

/*inline void ReadWord(const char *localFileName)
{
	string str;

	if (localFileName)
	{
		ifstream fin(localFileName);
		if (fin)
			while (getline(fin, str) && str != "")
			{
				int L = str.length(), i = str.find(' '), ii = i;

				while (i < L) if (str[i] & 0x80)
					Word_ID(make_pair(str[i], str[i+1]), str.substr(0, ii)),
					i += 2;
				else
					i ++;
			}
		else
			Error(2);
	}
	else
		Error(2);
}*/

inline void StoreData()
{
	// ============================================ 1-Gram

	#ifdef FIRST
	ofstream fout1("1-word");
	#else
	ofstream fout1("1-word-tmp");
	#endif

	for(int i=1; i<=WordTotal; i++)
		fout1 << Word[i] << ' ' << JoinPinyin(i) << ' ' << Times_1[i] << endl;

	// ============================================ 2-Gram

	/*#ifdef FIRST
	ofstream fout2("2-word");
	#else
	ofstream fout2("2-word-tmp");
	#endif

	for(map<int,int>::iterator iter = Times_2.begin(); iter != Times_2.end(); iter++)
		fout2 << OutputWord(iter->first/MAXWORD) << OutputWord(iter->first%MAXWORD) << ' ' << iter->second << endl;*/
}

int main()
{
	ReadData();

	char Filename[30] = "sina_news_gbk/S-00";

	int f = 1, ST, ED;

	printf("从第几个文件开始：\n");
	scanf("%d", &ST); f = ST-1;

	while (true)
	{
		printf("当前词数量为 %d\n", WordTotal);
		printf("指定处理到第几个文件：\n");
		scanf("%d", &ED);
		if (ED == -1) break;

		while (f < ED)
		{
			f++;

			printf("当前词数量为 %d\n", WordTotal);
			printf("\n开始读取第 %d 个文件……\n\n", f);

			Filename[16] = f/10 + '0';
			Filename[17] = f%10 + '0';

			ReadInput(Filename);
		}
	}

	StoreData();
	return 0;
}