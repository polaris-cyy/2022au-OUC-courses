#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <cstdlib>
#include <stack> 
#include <algorithm>
#include "graph.h"
using namespace std;

FILE* fp;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void test(int n);

int main(int argc, char** argv) {
	fp = freopen("test.txt", "r", stdin); 
	//test�����Ĳ���n�������ھ����������֮��Ҫ�������ھ��� 
	//����Ҫ�ֶ����ԣ���Ҫ��fp��ش���ɾ�������߸ı�test.txt�е�ֵ�� 
	int n = 0;
	while(cin >> n) {
		test(n);
	}
	fclose(fp);
	return 0;
}

void test(int n) {
	G g;
	g.InitGraph(n);
	g.PrintAdjMat();
	g.InitRelMat();
	g.PrintRelMat();
	g.STCount();
	g.PrintSTCount();
//	g.PrintSimpRelMat();
	g.InitSpanTree();
	g.PrintSpanTree();
//	g.PrintStRelMat();
	g.InitSegSys();
	g.PrintSegSys();
	g.ShowDuanSet();
	g.InitCirSys();
	g.PrintCirSys(); 
	g.ShowHuanLuSys();
}
