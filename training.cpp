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
				
				for(int j=2; j<len; j++) if (text[j-2] && text[j-1] && text[j])
					Times_3[Long(text[j-2], text[j-1], text[j])]++;
				/* for(int j=1; j<len; j++) if (text[j-1] && text[j])
					Times_2[Int(text[j-1], text[j])]++;
				for(int j=0; j<len; j++) if (text[j])
					Times_1[text[j]]++; */
				
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
		//printf("Now: %d\n", tot);
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

inline void StoreData(int f)
{
	char Filename[30] = "data/3-00";
	
	Filename[7] = f/10 + '0';
	Filename[8] = f%10 + '0';
	
	ofstream fout(Filename);
	
	for(map<long long,int>::iterator iter = Times_3.begin(); iter != Times_3.end(); iter++)
		fout << OutputChar((iter->first/MAXCHAR)/MAXCHAR) << OutputChar((iter->first/MAXCHAR)%MAXCHAR) << OutputChar(iter->first%MAXCHAR) << ' ' << iter->second << endl;
}

int main()
{
	ReadData();
	
	char Filename[30] = "sina_news_gbk/S-00";
	
	for(int f = 1; f <= 75; f++)
	{
		printf("# %d\n", f);
		
		Filename[16] = f/10 + '0';
		Filename[17] = f%10 + '0';
		
		ReadInput(Filename);
		
		if (f % 5 == 0)
		{
			printf("$ %d - %d\n", f/5, (int)Times_3.size());
			StoreData(f/5);
			Times_3.clear();
		}
	}
	
	return 0;
}