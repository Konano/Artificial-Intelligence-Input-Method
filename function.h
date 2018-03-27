//#pragma once

#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <string>
#include <cmath>

#define MAXPINYIN 500
#define MAXWORD 1500000

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

	char str[500], py[500];

	while (fin1 >> str >> py)
		fin1 >> Times_1[Word_ID(str, py)];

	// ============================================ 2-word

	ifstream fin2("2-word");

	long long tmp;

	while (fin2 >> tmp)
		fin2 >> Times_2[tmp];
}

/*inline int ChineseWord(const char ch, const char ch2)
{
	if ((0xffffffa1 <= (int)ch && (int)ch <= 0xffffffa8) || ((int)ch == 0xffffffa9 && (int)ch2 != 0xffffff96))
		return -1;
	if (ch & 0x80)
		return 1;
	return 0;
}

#include <sstream>
string Int_to_String(int n)
{
	ostringstream stream;
	stream << n;
	return stream.str();
}

inline string OutputWord(const int id)
{
	//cout << "Word " << id << ": " << Word[id].first << Word[id].second << " " << Pinyin[Word_pinyin[id]] << endl;

	if (id == 0) return "??0";

	string tmp = ""; int i = 0;
	while (Word_vec[Word[id]][i] != Word_pinyin[id]) i++;
	return tmp + Word[id].first + Word[id].second + Int_to_String(i);
}

inline void OutputWord2(const int id)
{
	cout << "Word " << id << ": " << Word[id].first << Word[id].second << " " << Pinyin[Word_pinyin[id]] << endl;
}*/
