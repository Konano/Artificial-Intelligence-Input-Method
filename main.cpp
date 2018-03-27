#define __DEBUG

#include "function.h"

using namespace std;

int len, text[1000];
char zh_cn[1000];

double f[1000][1000];
int g[1000][1000];

inline char* Translate(const string str)
{
	len = 0;

	int L = str.length(), S = 0, E = str.find(' ', S);
	while (E != -1)
		text[++len] = Pinyin_map[str.substr(S, E-S)], S = E+1, E = str.find(' ', S);
	text[++len] = Pinyin_map[str.substr(S, L-S)];

	len += 2; text[len-1] = text[0] = 1; f[0][0] = 0;

	for(int o=1; o<len; o++)
	{
		int num_0 = (o?(int)Pinyin_vec[text[o-1]].size():0);
		int num_1 = (int)Pinyin_vec[text[o]].size();
		int tot = 0;

		for(int i=0; i<num_1; i++) for(int j=0; j<num_0; j++)
			tot += Times_2[Int(Pinyin_vec[text[o-1]][j], Pinyin_vec[text[o]][i])]+1;

		for(int i=0; i<num_1; i++)
		{
			f[o][i] = -1e90, g[o][i] = -1;
			for(int j=0; j<num_0; j++)
			{
				double tmp = f[o-1][j] + log(1.0*(Times_2[Int(Pinyin_vec[text[o-1]][j], Pinyin_vec[text[o]][i])]+1) / tot);
				if (f[o][i] < tmp)
					f[o][i] = tmp, g[o][i] = j;
			}
		}
	}

	double MAX = -1e90;
	int Best = -1;
	int num = (int)Pinyin_vec[text[len-1]].size();
	for(int i=0; i<num; i++)
		if (MAX < f[len-1][i])
			MAX = f[len-1][i], Best = i;

	for(int o=len-1; o>0; o--)
	{
		zh_cn[o*2] = Char[Pinyin_vec[text[o]][Best]].first;
		zh_cn[o*2+1] = Char[Pinyin_vec[text[o]][Best]].second;
		Best = g[o][Best];
	}

	zh_cn[len*2-2] = 0;

	return zh_cn+2;
}

int main()
{
	ReadData();

	#ifdef __DEBUG
	puts("完成数据导入！");
	#endif

	ifstream fin("input.txt");
	ofstream fout("output.txt");

	string str; int tot = 0;
	while (getline(fin, str) && str != "")
	{
		printf("Now: %d\n", ++tot);
		fout << Translate(str) << endl;
	}
	return 0;
}