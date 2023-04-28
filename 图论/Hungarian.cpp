#include<iostream>
#include<cstring>
#include<stdlib.h>
using namespace std;

const int N = 8;	//ͼ�ж��ĸ��� 

bool G[N][N];	//ͼ�ڽӾ���
int match[N], n;	//B��ĳ�������A�ж������
bool used[N];
/*Hungarian algorithm
 *Question��
 *	����һ������ͼ�������һ�����ƥ�䡣 
 *Theory��
 *	Berge����ͨ���������������ƥ�䡣 
 *Steps��
 *	1.���һ����ʼƥ��(ͨ��Ϊ�գ��˴���Ϊ��ƥ��)
 *	2.����A��һδ����Ķ�������ʹ��B���׸���������Ķ���������
 *    3A.���ö�����ɹ���ת����һ�������ظ�Step 2
 *	  3B.���ö�δ����ɹ������Թ���һ���������
 *	    4A.���ɹ�����һ��������죬ͨ��Berge�������һ����ƥ��
 *		4B.��δ�ɹ�����һ��������죬������޷����䣬ת����һ�������ظ�Step 2
 *  5.A�����ж���ȡ���������� 
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
