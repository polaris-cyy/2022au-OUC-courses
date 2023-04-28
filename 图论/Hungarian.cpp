#include<iostream>
#include<cstring>
#include<stdlib.h>
using namespace std;

const int N = 8;	//图中顶的个数 

bool G[N][N];	//图邻接矩阵
int match[N], n;	//B中某顶许配的A中顶的序号
bool used[N];
/*Hungarian algorithm
 *Question：
 *	给定一个二分图，求得其一个最大匹配。 
 *Theory：
 *	Berge定理，通过可增广轨求得最大匹配。 
 *Steps：
 *	1.获得一个初始匹配(通常为空，此处即为空匹配)
 *	2.对于A中一未许配的顶，尝试使用B中首个与其关联的顶对其许配
 *    3A.若该顶许配成功，转至下一顶，并重复Step 2
 *	  3B.若该顶未许配成功，尝试构造一条可增广轨
 *	    4A.若成功构造一条可增广轨，通过Berge定理，求得一更大匹配
 *		4B.若未成功构造一条可增广轨，这个顶无法许配，转至下一顶，并重复Step 2
 *  5.A中所有顶均取过，结束。 
 */ 
 
bool dfs(int v)
{
	for(int i = 0; i < n; ++i)
	{
		if(G[v][i] && !used[i])
		{
			used[i] = true;
			if(match[i] == -1 || dfs(match[i]))
			{
				match[i] = v;
				match[v] = i;
				return true;
			}
		}
	}
	return false;
}

void Hungarian()
{
	memset(match, -1, sizeof(match));
	for(int i = 0; i < n; ++i)
	{
		if(match[i] == -1)
			dfs(i);
	}
}

int main()
{
	cin >> n;
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			cin >> G[i][j];
		} 
	}
	Hungarian();
	return 0;
}
