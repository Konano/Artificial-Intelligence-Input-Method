#define __DEBUG

#include "function.h"

using namespace std;

int len, text[1000];
char zh_cn[1000];

double f[100][100000];
int g[100][100000];

inline char* Translate(const string str)
{
	len = 0;

	int L = str.length(), S = 0, E = str.find(' ', S);
	while (E != -1)
		text[len++] = Pinyin_map[str.substr(S, E-S)], S = E+1, E = str.find(' ', S);
	text[len++] = Pinyin_map[str.substr(S, L-S)];

	for(int o=0; o<len; o++)
	{
		int num_0 = ((o-1>0)?(int)Pinyin_vec[text[o-2]].size():0);
		int num_1 = ((o>0)	?(int)Pinyin_vec[text[o-1]].size():0);
		int num_2 = (int)Pinyin_vec[text[o]].size();
		int tot_1 = 0;
		int tot_2 = 0;
		int tot_3 = 0;

		for(int i=0; i<num_2; i++)
			tot_1 += Times_1[Pinyin_vec[text[o]][i]]+1;

		for(int i=0; i<num_2; i++) for(int j=0; j<num_1; j++)
			tot_2 += (Times_2.count(Int(Pinyin_vec[text[o-1]][j], Pinyin_vec[text[o]][i])) ? Times_2[Int(Pinyin_vec[text[o-1]][j], Pinyin_vec[text[o]][i])] : 0)+1;

		for(int i=0; i<num_2; i++) for(int j=0; j<num_1; j++) for(int k=0; k<num_0; k++)
			tot_3 += (Times_3.count(Long(Pinyin_vec[text[o-2]][j], Pinyin_vec[text[o-1]][i], Pinyin_vec[text[o]][i])) ? Times_3[Long(Pinyin_vec[text[o-2]][j], Pinyin_vec[text[o-1]][i], Pinyin_vec[text[o]][i])] : 0)+1;

		if (o == 0)
			for(int i=0; i<num_2; i++)
				f[0][i] = log(1.0*Times_1[Pinyin_vec[text[o]][i]]+1 / tot_1);
		else if (o == 1)
			for(int i=0; i<num_2; i++)
			{
				for(int j=0; j<num_1; j++)
				{
					f[o][j*num_2+i] = f[o-1][j] +
									  log(1.0*((Times_2.count(Int(Pinyin_vec[text[o-1]][j], Pinyin_vec[text[o]][i])) ? Times_2[Int(Pinyin_vec[text[o-1]][j], Pinyin_vec[text[o]][i])] : 0)+1) / tot_2) +
									  log(1.0*(Times_1[Pinyin_vec[text[o]][i]]+1) / tot_1),
					g[o][j*num_2+i] = j;
				}
			}
		else
			for(int i=0; i<num_2; i++)
			{
				for(int j=0; j<num_1; j++)
				{
					f[o][j*num_2+i] = -1e90, g[o][j*num_2+i] = -1;
					for(int k=0; k<num_0; k++)
					{
						double tmp = f[o-1][k*num_1+j] +
									 log(1.0*((Times_3.count(Long(Pinyin_vec[text[o-2]][j], Pinyin_vec[text[o-1]][i], Pinyin_vec[text[o]][i])) ? Times_3[Long(Pinyin_vec[text[o-2]][j], Pinyin_vec[text[o-1]][i], Pinyin_vec[text[o]][i])] : 0)+1) / tot_3) +
									 log(1.0*((Times_2.count(Int(Pinyin_vec[text[o-1]][j], Pinyin_vec[text[o]][i])) ? Times_2[Int(Pinyin_vec[text[o-1]][j], Pinyin_vec[text[o]][i])] : 0)+1) / tot_2) +
									 log(1.0*(Times_1[Pinyin_vec[text[o]][i]]+1) / tot_1);
						if (f[o][j*num_2+i] < tmp)
							f[o][j*num_2+i] = tmp, g[o][j*num_2+i] = k*num_1+j;
					}
				}
			}
	}

	double MAX = -1e90;
	int Best = -1;
	int num_0 = (int)Pinyin_vec[text[len-1]].size();
	int num_1 = ((len > 1) ? (int)Pinyin_vec[text[len-2]].size() : 1);
	for(int i=0; i<num_0; i++)
		for(int j=0; j<num_1; j++)
			if (MAX < f[len-1][j*num_0+i])
				MAX = f[len-1][j*num_0+i], Best = j*num_0+i;

	for(int o=len-1; o>0; o--)
	{
		zh_cn[o*2] = Char[Pinyin_vec[text[o]][Best%(int)Pinyin_vec[text[o]].size()]].first;
		zh_cn[o*2+1] = Char[Pinyin_vec[text[o]][Best%(int)Pinyin_vec[text[o]].size()]].second;
		Best = g[o][Best];
	}

	zh_cn[0] = Char[Pinyin_vec[text[0]][Best]].first;
	zh_cn[1] = Char[Pinyin_vec[text[0]][Best]].second;
	zh_cn[len*2] = 0;

	return zh_cn;
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