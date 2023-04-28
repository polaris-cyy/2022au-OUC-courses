#include<iostream>
#include<string.h>
#include<bits/stdc++.h>
using namespace std;
const int MAX = 100;

void BFS(int** T, int** G, int v){	
	//G用来存图, 是一个无向图 
	//T用来返回生成树
	//v是顶点个数
//	for(int i = 0; i < v; ++i){
//		for(int j = 0; j < v; ++j){
//			cout << G[i][j] << " ";
//		}
//		cout << endl;
//	}
	
	int* l = new int[v];
	
	memset(l, -1, v * sizeof(int));
	l[0] = 0;
	for(int i = 0; i < v; ++i){
		int flag = 1;
		for(int j = 0; j < v; ++j){
			if(l[j] == i){
				for(int k = 0; k < v; ++k){
					if(j != k && G[j][k] != MAX && l[k] == -1){
						l[k] = i + 1;
						T[j][k] = T[k][j] = 1;
					}
				}
				flag = 0;
			}
		}
		if(flag)
			break;
	}
}

int main(){
	int** G = new int*[8];
	int** T = new int*[8];
	for(int i = 0; i < 8; ++i){
		G[i] = new int[8];
		T[i] = new int[8];
	}
	
	
	for(int i = 0; i < 8; ++i){
		memset(T[i], 0, 8*sizeof(int));
	}
	
	FILE*fp = fopen("data.txt", "rb");
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j){
			fscanf(fp, "%d", &G[i][j]);
		}
	}
	
	BFS(T, G, 8);
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j){
			cout << T[i][j] << " ";
		}
		cout << endl;
	}
	fclose(fp); 
	return 0;
}
