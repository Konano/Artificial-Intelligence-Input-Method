#define __DEBUG

#include "function.h"

using namespace std;

#define MAXLIMIT 10000000

struct node{long long ll; int cs, id;};
bool operator < (const node &a, const node &b){return a.ll>b.ll;}
priority_queue<node>num;

struct js{long long ll; int cs;};
bool operator < (const js &a, const js &b){return a.cs>b.cs;}
priority_queue<js>rs;

inline void PushIn(long long ll, int cs)
{
	if ((int)rs.size() < MAXLIMIT)
		rs.push((js){ll,cs});
	else if (cs > rs.top().cs)
		rs.pop(), rs.push((js){ll,cs});
}

char str[50];
int num_tot = 0;
ifstream G[79];

inline void GetNum(int f)
{
	long long id;
	int tmp;
	if (G[f] >> id >> tmp)
	{
		num.push((node){id,tmp,f});
		num_tot ++;
		if (num_tot % 100000 == 0) printf("%d\n", num_tot);
	}
}

inline void StoreData()
{
	ofstream fout("2-word");

	while (!rs.empty())
	{
		js iter = rs.top(); rs.pop();
		fout << iter.ll << ' ' << iter.cs << endl;
	}
}

int main()
{
	char Filename[30] = "data/00";

	for(int f=1; f<=75; f++)
	{
		Filename[5] = f/10 + '0';
		Filename[6] = f%10 + '0';

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