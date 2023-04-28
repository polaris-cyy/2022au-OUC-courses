#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
#define N 507
int match[N], n;
bool used[N];
vector<int> Map[N];

bool dfs(int v)
{
	for(int i = 0; i < Map[v].size(); ++i)
	{
		int x = Map[v][i];
		if(!used[x])
		{
			used[x] = true;
			if(match[x] == -1 || dfs(match[x]))
			{
				match[v] = x;
				match[x] = v;
				return true;
			}
		}
	}
	return false;
}

int Hungarian()
{
	int ans = 0;
	for(int i = 0; i < n; ++i)
	{
		memset(used, false, sizeof(used));
		if(match[i] == -1)
			ans += dfs(i);
	}
	return ans;
}

int main()
{
	while(cin >> n)
	{
		memset(match, -1, sizeof(match));
		for(int i = 0; i < n; ++i)
			Map[i].clear();
		for(int i = 0; i < n; ++i)
		{
			int p, q;
			scanf("%d: (%d)", &p, &q);
			while(q--)
			{
				int j;
				scanf("%d", &j);
				Map[j].push_back(p);
				Map[p].push_back(j);
			}
		}
		printf("%d\n", n - Hungarian());
	}
	return 0;
}
