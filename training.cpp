#define __DEBUG

#include "function.h"

using namespace std;

int len, text[1000];

inline void Analyze(string str)
{
	int L = str.length(), i = 0;
	
	while (i < L) 
		switch (ChineseChar(str[i]))
		{
			case -1: i++;
			case 0: i++; break;
			case 1:
			{
				len = 0;
				while ((i < L) && ChineseChar(str[i]) == 1)
				{
					if (Char_map.count(make_pair(str[i], str[i+1])))
						text[len++] = Char_map[make_pair(str[i], str[i+1])];
					else
						text[len++] = 0;
					i += 2;
				}
				for(int j=1; j<len; j++) if (text[j-1] && text[j])
					Times[Int(text[j-1], text[j])]++;
				for(int j=0; j<len; j++) if (text[j])
					Char_times[text[j]]++;
				
				#ifdef __DEBUG
				//for(int j=0; j<len; j++) OutputChar(text[j]); puts("");
				#endif
			}
		}
}

inline void ReadInput(const char *localFileName)
{
	#ifdef __DEBUG
	int tot = 0;
	#endif
	
	string str; 
	
	if (localFileName)
	{
		ifstream fin(localFileName);
		if (fin)
			while (getline(fin, str) && str != "")
			{
				Json::Reader reader;
				Json::Value input;
				reader.parse(str, input);
				
				#ifdef __DEBUG
				tot++; if (tot % 2000 == 0) printf("Now: %d\n", tot);
				#endif
				
				Analyze(input["html"].asString());
			}
		else
			Error(1);
	}
	else
		Error(1);
}

inline void StoreData(const char *localFileName)
{
	ofstream fout(localFileName);
	
	for(int i=1; i<=CharTotal; i++) 
		fout << Char_times[i] << endl;
	
	fout << endl << Times.size() << endl;
	
	for(map<int,int>::iterator iter = Times.begin(); iter != Times.end(); iter++)
		fout << iter->first << iter->second << endl;
}

int main()
{
	ReadCharacter("pinyin.txt");
	
	char Filename[30] = "sina_news_gbk/2016-00.txt";
	
	for(int month=01; month<=11; month++)
	{
		#ifdef __DEBUG
		printf("\n开始读取第 %d 个月的新闻……\n\n", month);
		#endif
		
		Filename[19] = month/10 + '0';
		Filename[20] = month%10 + '0';
		ReadInput(Filename);
	}
	
	ReadData("data.txt");
	StoreData("data.txt");
	return 0;
}