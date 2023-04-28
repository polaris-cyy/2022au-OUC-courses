#include<bits/stdc++.h>
using namespace std;

const int N = 8;
const int P = 3;

int main(){
	int (*weight_matrix)[N] = new int[N][N];//边权矩阵初始化
	
	FILE*fp = fopen("data.txt", "rb");
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j){
			fscanf(fp, "%d", &weight_matrix[i][j]);
		}
	}
	
	int* S = new int[N];//初始化已经出现过的点
	for(int i = 0; i < N; ++i){
		if(i == P)
			S[i] = 1;
		else
			S[i] = 0;
	}

	int* l = new int[N];//初始化长度
	memset(l, 10000, N*sizeof(int));
	l[P] = 0;
	
	int current = P;

	for(int i = 0; i < N - 1; ++i){
		for(int j = 0; j < N; ++j){
			if(S[j] == 0)
				l[j] = min(l[j], weight_matrix[current][j] + l[current]);
		}

		int index = 0, m = 10000;
		for(int j = 0; j < N; ++j){
			if(S[j] == 0){
				if(l[j] < m){
					m = l[j];
					index = j;
				}
			}
		}
		
		S[index] = 1;
		current = index;
	}

	for(int i = 0; i < N; ++i){
		printf("%d ", l[i]);
	}

	fclose(fp);
	return 0;
}
