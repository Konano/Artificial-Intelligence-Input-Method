#define __DEBUG

#include "function.h"

using namespace std;

struct node
{
	map<int,int> children;
	vector<int> wd;
} Tree[MAXWORD];

int TreeTotal = 0;

inline void Insert(int id)
{
	int now = 0;
	int L = (int)Word_pinyin[id].size();
	for(int i = 0; i < L; i++)
	{
		if (Tree[now].children[Word_pinyin[id][i]] == 0)
			Tree[now].children[Word_pinyin[id][i]] = ++TreeTotal;
		now = Tree[now].children[Word_pinyin[id][i]];
	}
	Tree[now].wd.push_back(id);
}

inline void BuildTree() { for(int i = 1; i <= WordTotal; i++) Insert(i); }

int len, text[1000];

double f[1000][3000];
int g[1000][3000];

vector<pair<int,int> > st[1000];
vector<int> ed[1000];

inline int Count_1(int x) { return Times_1[x]; }
inline int Count_2(int x, int y) { return (Times_2.count(Long(x,y)) == 0) ? 0 : Times_2[Long(x,y)]; }
inline int Length(int x) { return Word[x].length()/2; }

inline string Translate(const string str)
{
	len = 0;

	int L = str.length(), S = 0, E = str.find(' ', S);
	while (E != -1)
		text[++len] = Pinyin_map[str.substr(S, E-S)], S = E+1, E = str.find(' ', S);
	text[++len] = Pinyin_map[str.substr(S, L-S)];

	len += 2; text[len-1] = text[0] = 1;

	for(int i = 0; i < len; i++) ed[i].clear(), st[i].clear();

	for(int i = 0; i < len; i++)
	{
		int T = 0, now = i;
		while (now < len && Tree[T].children.count(text[now]))
		{
			T = Tree[T].children[text[now]];
			int num = (int)Tree[T].wd.size();
			for(int j = 0; j < num; j++)
			{
				if (i) st[i-1].push_back(make_pair(Tree[T].wd[j], (int)ed[now].size()));
				ed[now].push_back(Tree[T].wd[j]);
			}
			now ++;
		}
	}
	for(int o = 0; o < len; o++)
	{
		int num = (int)ed[o].size();
		for(int i = 0; i < num; i++) f[o][i] = -1e90, g[o][i] = -1;
	}
	f[0][0] = 0;

	for(int o = 0; o < len-1; o++)
	{
		int num = (int)ed[o].size();
		int _num = (int)st[o].size();

		int tot_1 = 0;
		for(int j = 0; j < _num; j++)
			tot_1 += Count_1(st[o][j].first);

		for(int i = 0; i < num; i++)
		{
			int tot_2 = 0;
			for(int j = 0; j < _num; j++)
				tot_2 += Count_2(ed[o][i], st[o][j].first)+1;

			for(int j = 0; j < _num; j++)
			{
				int _o = o + Length(st[o][j].first);
				int _j = st[o][j].second;

				double tmp = f[o][i] + log(1.0*(Count_2(ed[o][i], st[o][j].first)+1) / tot_2);
				if (tmp > f[_o][_j])
					f[_o][_j] = tmp,
					g[_o][_j] = i;
			}
		}

		// int tot_1 = 0;
		// for(int i = 0; i < num; i++) tot_1 += Times_1[wd[o][i].first] + 1;

		// int tot_2 = 0;
		// for(int i = 0; i < num; i++)
		// {
		// 	int _o = o - wd[o][i].second;
		// 	int _num = (int)wd[_o].size();

		// 	for(int j = 0; j < _num; j++)
		// 		tot_2 += count_2(wd[_o][j].first, wd[o][i].first) + 1;
		// }

		// for(int i = 0; i < num; i++)
		// {
		// 	int _o = o - wd[o][i].second;
		// 	int _num = (int)wd[_o].size();

		// 	for(int j = 0; j < _num; j++)
		// 	{
		// 		double tmp = f[_o][j] + log((count_2(wd[_o][j].first, wd[o][i].first)+1) / tot_2);
		// 		if (tmp > f[o][i])
		// 		{
		// 			f[o][i] = tmp;
		// 			g[o][i] = j;
		// 		}
		// 	}
		// }

				// tot_2 += (Times_2.count(Long(wd[_o][j].first, wd[o][i].first)) ? Times_2[Long(wd[_o][j].first, wd[o][i].first)] : 0) + 1;


	}

	double MAX = -1e90;
	int Best = -1;
	int num = (int)ed[len-1].size();
	for(int i = 0; i < num; i++)
		if (MAX < f[len-1][i])
			MAX = f[len-1][i], Best = i;

	vector<int> ans;

	for(int o = len-1; o; )
	{
		ans.push_back(ed[o][Best]);
		int strL = Length(ed[o][Best]);
		Best = g[o][Best];
		o -= strL;
	}

	string zh_cn = "";

	for(int i = (int)ans.size()-1; i >= 0; i--) if (ans[i] != 1)
		zh_cn += Word[ans[i]];

	return zh_cn;
}

int main()
{
	ReadData();

	BuildTree();

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