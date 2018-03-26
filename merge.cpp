#define __DEBUG

#include "function.h"

using namespace std;

/* int len, text[10000];

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
} */

struct node{long long ll; int cs, id;};
bool operator < (const node &a, const node &b){return a.ll>b.ll;}
priority_queue<node>num;

struct js{long long ll; int cs;};
bool operator < (const js &a, const js &b){return a.cs>b.cs;}
priority_queue<js>rs;

inline void PushIn(long long ll, int cs)
{
	if ((int)rs.size() < 5000000)
		rs.push((js){ll,cs});
	else if (cs > rs.top().cs)
		rs.pop(), rs.push((js){ll,cs});
}

char str[50];
int num_tot = 0;
ifstream G[19];

inline void GetNum(int f)
{
	if (G[f].eof()) return;
	
	G[f] >> str; if (str[0] == 0) return;
		
	int id1 = Char_map[make_pair(make_pair(str[0], str[1]), Char_vec[make_pair(str[0], str[1])][str[2]-'0'])];
	int id2 = Char_map[make_pair(make_pair(str[3], str[4]), Char_vec[make_pair(str[3], str[4])][str[5]-'0'])];
	int id3 = Char_map[make_pair(make_pair(str[6], str[7]), Char_vec[make_pair(str[6], str[7])][str[8]-'0'])];
	int tmp; G[f] >> tmp;
	
	num.push((node){Long(id1, id2, id3),tmp,f});
	
	num_tot ++;
	if (num_tot % 10000 == 0) printf("%d\n", num_tot);
}

inline void StoreData()
{
	ofstream fout("3-gram");
	
	while (!rs.empty())
	{
		js iter = rs.top(); rs.pop();
		fout << OutputChar((iter.ll/MAXCHAR)/MAXCHAR) << OutputChar((iter.ll/MAXCHAR)%MAXCHAR) << OutputChar(iter.ll%MAXCHAR) << ' ' << iter.cs << endl;
	}
} 

int main()
{
	ReadData();
	
	char Filename[30] = "data/3-00";
	
	for(int f=1; f<=15; f++)
	{
		Filename[7] = f/10 + '0';
		Filename[8] = f%10 + '0';
		
		G[f].open(Filename);
		
		GetNum(f);
	}
	
	long long ll;
	int cs;
	while (!num.empty())
	{
		ll = num.top().ll;
		cs = 0;
		
		while (!num.empty() && num.top().ll == ll)
		{
			cs += num.top().cs;
			GetNum(num.top().id);
			num.pop();
		}
		
		PushIn(ll, cs);
	}
	
	StoreData();
	
	return 0;
}