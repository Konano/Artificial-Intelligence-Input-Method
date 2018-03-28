#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <string>
#include <cmath>

inline void ERROR(int x)
{
	if (x == 1) puts("过多参数。");
	if (x == 2) puts("过少参数，请指定输入文件和输出文件的路径。");
	if (x == 2) puts("例如 pinyin_2.exe ../data/input.txt ../data/output.txt");
	if (x == 3) puts("找不到输入文件。");
	if (x == 4) puts("找不到数据文件 1-word");
	if (x == 5) puts("找不到数据文件 2-word");
	exit(1);
}

#define MAXPINYIN 500		// 拼音总数
#define MAXWORD 1500000		// 单词总数

#define Long(i, j) 1LL*i*MAXWORD+j

using namespace std;

int PinyinTotal = 0, WordTotal = 0;

string Pinyin[MAXPINYIN];
map<string,int> Pinyin_map;

string Word[MAXWORD];
vector<int> Word_pinyin[MAXWORD];
map<pair<string,int>,int> Word_map;

inline int Pinyin_ID(string py)
{
	if (py=="n") py="en";
	if (py=="lve") py="lue";
	if (py=="nve") py="nue";
	// pypinyin 注音的手动修改

	if (Pinyin_map[py] == 0)
		return Pinyin[Pinyin_map[py] = ++PinyinTotal] = py, PinyinTotal;
	return Pinyin_map[py];
}

inline int PinyinHash(int id)
{
	int tmp = (int)Word_pinyin[id].size(), num = 0;
	for(int i = 0; i < tmp; i++)
		num = (2333LL * num + Word_pinyin[id][i]) % 1000000007;
	return num;
}

inline int PinyinHash(string py)
{
	int L = py.length();
	int num = 0;
	int S = 0, E = py.find('-', S);

	while (E != -1)
	{
		num = (2333LL * num + Pinyin_ID(py.substr(S, E-S))) % 1000000007;
		S = E + 1;
		E = py.find('-', S);
	}
	num = (2333LL * num + Pinyin_ID(py.substr(S, L-S))) % 1000000007;
	return num;
}

inline string JoinPinyin(int id)
{
	string tmp = Pinyin[Word_pinyin[id][0]];
	int tot = (int)Word_pinyin[id].size();
	for(int i = 1; i < tot; i++)
		tmp += '-' + Pinyin[Word_pinyin[id][i]];
	return tmp;
}

inline void SplitPinyin(int id, string py)
{
	int L = py.length();
	int S = 0, E = py.find('-', S);

	while (E != -1)
	{
		Word_pinyin[id].push_back(Pinyin_ID(py.substr(S, E-S)));
		S = E + 1;
		E = py.find('-', S);
	}

	Word_pinyin[id].push_back(Pinyin_ID(py.substr(S, L-S)));
}

inline int Word_ID(string wd, string py)
{
	int H = PinyinHash(py);
	if (Word_map.count(make_pair(wd, H)))
		return Word_map[make_pair(wd, H)];

	WordTotal ++;
	Word[WordTotal] = wd;
	Word_map[make_pair(wd, H)] = WordTotal;
	SplitPinyin(WordTotal, py);

	return WordTotal;
}

map<long long,int> Times_2;
int Times_1[MAXWORD];

inline void ReadData()
{
	// ============================================ 1-word

	ifstream fin1("1-word");
	if (!fin1) ERROR(4);

	char str[500], py[500];

	while (fin1 >> str >> py)
		fin1 >> Times_1[Word_ID(str, py)];

	// ============================================ 2-word

	ifstream fin2("2-word");
	if (!fin2) ERROR(5);

	long long tmp;

	while (fin2 >> tmp)
		fin2 >> Times_2[tmp];
}
