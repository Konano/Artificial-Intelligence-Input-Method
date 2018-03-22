//#pragma once

#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <string>
#include <cmath>

#include "jsoncpp/json.h"

#define MAXPINYIN 500
#define MAXCHAR 7000

using namespace std;

int PinyinTotal = 0, CharTotal = 0;

string Pinyin[MAXPINYIN];
map<string,int> Pinyin_map;
vector<int> Pinyin_vec[MAXPINYIN];

pair<char,char> Char[MAXCHAR];
map<pair<char,char>,int> Char_map;
//int Char_pinyin[MAXCHAR];

map<int,int> Times;
int Char_times[MAXCHAR];

inline void Error(const int id) // 报错
{
	if (id == 1) puts("训练集文件有误。");
	if (id == 2) puts("拼音汉字对照文件有误。");
	exit(1);
}

inline void ReadCharacter(const char *localFileName)
{
	string str;
	
	if (localFileName)
	{
		ifstream fin(localFileName);
		if (fin)
			while (getline(fin, str) && str != "")
			{
				int L = str.length(), i = str.find(' ');
				
				Pinyin[++PinyinTotal] = str.substr(0, i);
				Pinyin_map[Pinyin[PinyinTotal]] = PinyinTotal;
				
				while (i < L) if (str[i] & 0x80)
				{
					if (Char_map.count(make_pair(str[i], str[i+1])) == 0)
					{						
						Char[++CharTotal] = make_pair(str[i], str[i+1]);
						Char_map[Char[CharTotal]] = CharTotal;
					}
					Pinyin_vec[PinyinTotal].push_back(Char_map[make_pair(str[i], str[i+1])]);
					//Char_pinyin[CharTotal] = PinyinTotal;
					
					i += 2;
				} else i++;
			}
		else
			Error(2);
	}
	else
		Error(2);
}

inline void ReadData(const char *localFileName)
{
	if (localFileName)
	{
		ifstream fin(localFileName);
		if (fin)
		{
			int tot, tmp, tmp2;
			for(int i=1; i<=CharTotal; i++)
			{
				fin >> tmp;
				Char_times[i] += tmp;
			}
			
			fin >> tot;
			for(int i=1; i<=tot; i++)
			{
				fin >> tmp >> tmp2;
				Times[tmp] += tmp2;
			}
		}
	}
}

inline int ChineseChar(const char ch)
{
	if ((ch & 0xa0) == 0xa0 && (ch & 0x50) == 0x00) 
		return -1; // 中文字符
	if (ch & 0x80)
		return 1; // 汉字
	return 0;
}

inline void OutputChar(const int id)
{
	printf("%c%c", Char[id].first, Char[id].second);
}


#define Int(i, j) i*CharTotal+j-1
