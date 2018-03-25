#define __DEBUG
//#define FIRST

#include "function.h"

using namespace std;

int len, text[10000];

#ifdef __DEBUG
int tot = 0;
#endif

inline void Analyze(string str, ifstream &fpy)
{
	int L = str.length(), i = 0;
	
	#ifdef __DEBUG
	//cout << hex << (int)str[1];
	//cout << str << endl;
	#endif
	
	while (i+1 < L) 
		switch (ChineseChar(str[i], str[i+1]))
		{
			case -1: i++;
			case 0: i++; break;
			case 1:
			{
				len = 0;
				while ((i+1 < L) && ChineseChar(str[i], str[i+1]) == 1)
				{
					string py; fpy >> py;
					
					#ifdef __DEBUG
					//cout << str[i] << str[i+1] << py << endl;
					int tmp = CharTotal;
					#endif
					
					text[len++] = Character_ID(make_pair(str[i], str[i+1]), py);
					
					#ifdef __DEBUG
					if (tmp != CharTotal) 
						OutputChar2(CharTotal);
					#endif
					
					i += 2;
				}
				
				for(int j=1; j<len; j++) if (text[j-1] && text[j])
					Times_2[Int(text[j-1], text[j])]++;
				for(int j=0; j<len; j++) if (text[j])
					Times_1[text[j]]++;
				
				#ifdef __DEBUG
				//for(int j=1; j<=len; j++) OutputChar(text[j]); puts("");
				#endif
			}
		}
}

inline void ReadInput(char *localFileName)
{
	string str;
	
	localFileName[14] = 'S';
	ifstream fin(localFileName);
	localFileName[14] = 'P';
	ifstream fpy(localFileName);
	
	while (!fin.eof())
	{
		#ifdef __DEBUG
		tot++; //if (tot % 2000 == 0) printf("Now: %d\n", tot);
		printf("Now: %d\n", tot);
		#endif
		
		getline(fin, str);
		Analyze(str, fpy);
	}
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
				int L = str.length(), i = str.find(' '), ii = i;
				
				while (i < L) if (str[i] & 0x80)
					Character_ID(make_pair(str[i], str[i+1]), str.substr(0, ii)), 
					i += 2;
				else 
					i ++;
			}
		else
			Error(2);
	}
	else
		Error(2);
}

inline void StoreData()
{
	// ============================================ 1-Gram
	
	#ifdef FIRST
	ofstream fout1("1-gram");
	#else
	ofstream fout1("1-gram-tmp");
	#endif
	
	for(int i=1; i<=CharTotal; i++) 
		fout1 << Char[i].first << Char[i].second << ' ' << Pinyin[Char_pinyin[i]] << ' ' << Times_1[i] << endl;
	
	// ============================================ 2-Gram
	
	#ifdef FIRST
	ofstream fout2("2-gram");
	#else
	ofstream fout2("2-gram-tmp");
	#endif
	
	for(map<int,int>::iterator iter = Times_2.begin(); iter != Times_2.end(); iter++)
		fout2 << OutputChar(iter->first/MAXCHAR) << OutputChar(iter->first%MAXCHAR) << ' ' << iter->second << endl;
}

int main()
{
	#ifdef FIRST
	ReadCharacter("pinyin");
	#else
	ReadData();
	#endif
	
	char Filename[30] = "sina_news_gbk/S-00";
	
	int f = 1, ST, ED;
	
	printf("从第几个文件开始：\n");
	scanf("%d", &ST); f = ST-1;
	
	while (true)
	{
		printf("指定处理到第几个文件：\n");
		scanf("%d", &ED);
		if (ED == -1) break;
		
		while (f < ED)
		{
			f++;
			
			printf("\n开始读取第 %d 个文件……\n\n", f);
			
			Filename[16] = f/10 + '0';
			Filename[17] = f%10 + '0';
			
			ReadInput(Filename);
		}
	}
	
	StoreData();
	return 0;
}