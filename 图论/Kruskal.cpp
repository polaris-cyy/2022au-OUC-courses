#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;

const int MAX = 100;
const int N = 8; 

struct Triple{
	int tail;
	int head;
	int weight;
	Triple(){tail = head = weight = 0;}
	bool operator>(Triple T){
		return weight > T.weight;
	} 
	bool operator<(Triple T){
		return weight < T.weight;
	}
	void show(){cout << tail << "-" << head << ": " << weight << endl;}
};

void Kruskal(int** G, Triple* T,  int v){
	int** U = new int*[v];
	for(int i = 0; i < v; ++i){
		U[i] = new int[v];
		memset(U[i], 0, sizeof(int) * v);
	}
	Triple* E;
	//G用来存图
	//U用来表示两点点是否已经连通，以判断是否会形成圈
	//E用来存边
	//T用来返回生成树 
	//v表示顶个数
	
	//边数 
	int count = 0; 
	for(int i = 0; i < v; ++i){
		for(int j = i; j < v; ++j){
			if(G[i][j] && G[i][j] != MAX)
				++count;
		}
	}
	
	E = new Triple[count];
	count = 0;
	
	//存边和权 
	for(int i = 0; i < v; ++i){
		for(int j = i; j < v; ++j){
			if(G[i][j] && G[i][j] != MAX){
				E[count].head = i;
				E[count].tail = j;
				E[count++].weight = G[i][j];
			}
		}
	}
	int size = count - 1;
	count = 0;
	
	sort(E, E + size);
	
	for(int i = 0; i < size; ++i){
		E[i].show();
	}
	
	for(int i = 0; i < size; ++i){
		if(U[E[i].head][E[i].tail]){
			cout << i << endl;
			continue;
		}
		else{
			T[count++] = E[i];
			//这部分为什么写得这么麻烦？？
			//How to simplify? 
			for(int j = 0; j < N; ++j){
				if(U[E[i].head][j]){
					U[j][E[i].tail] = U[E[i].tail][j] = 1;
					for(int k = 0; k < N; ++k){
						if(U[k][j])
							U[k][E[i].tail] = U[E[i].tail][k] = 1;
					}
				}
				if(U[E[i].tail][j]){
					U[j][E[i].head] = U[E[i].head][j] = 1;
					for(int k = 0; k < N; ++k){
						if(U[k][j])
							U[k][E[i].head] = U[E[i].head][k] = 1;
					}
				}
				U[E[i].head][E[i].tail] = U[E[i].tail][E[i].head] = 1;
			}
		}
	}
}

int main(){
	int** G = new int*[N];//边权矩阵初始化
	for(int i = 0; i < N; ++i){
		G[i] = new int[N];
		memset(G[i], 0, N*sizeof(int));
	}
	
	FILE*fp = fopen("data.txt", "rb");
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j){
			fscanf(fp, "%d", &G[i][j]);
		}
	}
	
	Triple *T;
	T = new Triple[N-1];
	Kruskal(G, T, N);
	
	for(int i = 0; i < N-1; ++i){
		T[i].show();
	}
	return 0;
}
