#include<iostream>
#include<string.h>
using namespace std;

void DFS(int** G, int** T, int* father_array, int v, int* u, int father = 0, int cur = 0){
	//G���ڽӾ���
	//T������Ƿ��ù�
	//father_array�洢ÿ�����ĸ����
	//v���������
	//father����������ĸ����
	//cur����ǰ����
	//u�������Ѿ���ʹ�ù� 
	u[cur] = 1;	//ÿ������һ���µĽ��ʱ�������עΪ��ʹ�� 
	if(cur != father)
		father_array[cur] = father;	//��¼����father 
	else
		father_array[cur] = -1;	//��ʼ�ڵ�
		 
	cout << cur << " " << father_array[cur] << endl;
	
	for(int i = 0; i < v; ++i){
		if(G[i][cur] && G[i][cur] != 100 && !T[i][cur] && !u[i]){
			//�� && ��δʹ�� && ����δʹ�� 
			T[i][cur] = T[cur][i] = 1;
			DFS(G, T, father_array, v, u, cur, i);
		}
	}
}

int main(){
	//initialize
	int** G = new int*[8];
	int** T = new int*[8];
	for(int i = 0; i < 8; ++i){
		G[i] = new int[8];
		T[i] = new int[8];
		memset(G[i], 0, sizeof(int) * 8);
		memset(T[i], 0, sizeof(int) * 8);
	}
	
	FILE*fp = fopen("data.txt", "rb");
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j){
			fscanf(fp, "%d", &G[i][j]);
		}
	}
	int* father_array = new int[8];
	memset(father_array, 0, 8*sizeof(int));
	int* u = new int[8];
	memset(u, 0, 8*sizeof(int));

	DFS(G, T, father_array, 8, u);
	
	for(int i = 0; i < 8; ++i){
		cout << father_array[i] << " ";
	}
	
	fclose(fp);
	
	return 0;
}
