#include "unionset.h"
using namespace std;

class G{
	friend class UnionSet;
	
	public:
		G();
		void InitGraph(int x);	//初始化图 
		void InitRelMat();	//相邻矩阵
		int CalMatrix(int**Matrix, int n);	//输入二维数组和阶数，返回行列式的值 
		int STCount();	//生成树个数 
		void PrintSTCount();	//打印生成树个数 
		void InitSpanTree();	//生成树 
		bool InitSegSys();	//基本割集系统 
		void ShowDuanSet();	//断集空间 
		bool InitCirSys();	//基本回路系统 
		void ShowHuanLuSys();	//环路系统 
		void PrintAdjMat();	//打印相邻矩阵 
		void PrintRelMat();	//打印关联矩阵 
		void PrintSpanTree();	//打印生成树 
		void PrintSimpRelMat();	//打印关联矩阵·稠密版 
		void PrintStRelMat();	//打印生成树·稠密版 
		void PrintSegSys();	//打印基本割集系统 
		void PrintCirSys();	//打印基本回路系统 
		
		~G();
		
	private:
		int n, e, st_cnt;	//顶点个数和边数, 生成树个数 
		bool Adj, Rel, Spa, Seg, Cir;	//是否初始化 相邻矩阵，关联矩阵，生成树，基本割集系统，基本回路系统。 
		bool Connect;	//是否连通图 
		int **adjacent_matrix;	//相邻矩阵 
		int **relative_matrix;	//关联矩阵 
		int **seg_matrix;	//基本割集系统 
		int **cir_matrix;	//基本回路系统 
		int *simp_rel_mat[2];	//去除0的关联矩阵 
		int *spanning_tree;	//生成树 
		int *st_adj_mat[2];	//生成树去除0的关联矩阵 
};

G::G()
{
	n = st_cnt = 0;
	Adj = Rel = Spa = Seg = Cir = Connect = false;
	adjacent_matrix = NULL;
	relative_matrix = NULL;
	spanning_tree = NULL;
}

void G::InitGraph(int x)
{
	//如果已经创建，返回。否则，创建x * x的图，并判断连通性。 
	if (Adj) {
		cerr << "图已被创建。" << endl;
		return;
	}
	
	//初始化图 
	n = x;
	adjacent_matrix = new int*[n];
	for (int i = 0; i < n; ++i) {
		adjacent_matrix[i] = new int[n];
		memset(this->adjacent_matrix[i], 0, sizeof(this->adjacent_matrix[i])); 
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> adjacent_matrix[i][j];
		}
	}
	//相邻矩阵创建完毕。 
	Adj = true;
	
	//判断是否连通 
	UnionSet u(n);
	u.init();
	int cnt = 1;
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (!u.same(i, j)) {
				cnt++;
				u.unite(i, j);
			}
		} 
	}
	if (cnt == n)
		this->Connect = true;
	else
		this->Connect = false;
}

void G::InitRelMat()
{
	//	如果已经创建关联矩阵或未初始化图，返回；否则，创建n * e的关联矩阵，和去除0的稠密关联矩阵。 
	if (!Adj) 
		cout << "图未创建。" << endl;
	if (Rel) {
		cout << "关联矩阵已被创建。" << endl;
		return;
	}
	
	//握手定理确定边数 
	int degree = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			degree += adjacent_matrix[i][j];
		}
	}
	e = degree / 2;
	
	//创建关联矩阵 
	relative_matrix = new int*[n];
	for (int i = 0; i < n; ++i) {
		relative_matrix[i] = new int[e];
		memset(this->relative_matrix[i], 0, e * sizeof(int));
	}
	
	//创建稠密关联矩阵 
	for (int i = 0; i < 2; ++i) {
		this->simp_rel_mat[i] = new int[e];
		memset(this->simp_rel_mat[i], 0, e * sizeof(int));
	} 
	//初始化关联矩阵和稠密关联矩阵 
	int index = 0;
	for (int i = 0; i < n; ++i) { 
		for (int j = i + 1; j < n; ++j) {
			if (adjacent_matrix[i][j]) {
				this->relative_matrix[i][index] = 1;
				this->relative_matrix[j][index] = 1; 
				this->simp_rel_mat[0][index] = i;
				this->simp_rel_mat[1][index] = j;
				index++;
			}
		}
	}
	Rel = true;
}

int G::CalMatrix(int**Matrix, int n) {
	if (n == 1) {
		return Matrix[0][0];
	}
	int sum = 0;
	int*arr = new int[n];
	for (int i = 0; i < n; ++i) {
		arr[i] = i;
	}
	int fac = 1;
	for (int i = 1; i <= n; ++i) {
		fac *= i;
	}
	for (int i = 0; i < fac; ++i) {
		//逆序数
		int sign = 0;
		for (int j = 0; j < n; ++j) {
			for (int k = j; k < n; ++k) {
				if (arr[k] < arr[j]) sign++;
			}
		}
		sign = (sign % 2) ? -1 : 1;
		for (int j = 0; j < n; ++j) {
			sign *= Matrix[j][arr[j]]; 
			if (!sign) break;
		}
		sum += sign;
		next_permutation(arr, arr+n);
	}
	delete[] arr;
	return sum;
}

//使用矩阵树定理计算生成树个数 
int G::STCount()
{
	if (!Connect) return 0;
	if (st_cnt != 0) return st_cnt;
	int**D = new int*[n];
	for (int i = 0 ; i < n; ++i) {
		D[i] = new int[n];
		memset(D[i], 0, n * sizeof(int));
	}
	
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (this->adjacent_matrix[i][j]) {
				D[i][i]++;
				D[j][j]++;
			}
		}
	}
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			D[i][j] -= this->adjacent_matrix[i][j];
		}
	}
	
	int count = CalMatrix(D, n - 1);
	for (int i = 0; i < n; ++i) {
		delete[] D[i];
	}
	delete[] D;
	
	return st_cnt = count;
} 

void G::PrintSTCount()
{
	cout << "生成树个数: " << st_cnt << endl;
}

void G::InitSpanTree()
{
	//	如果没有创建关联矩阵，调用InitRelMat；如果创建了生成树 ，返回；否则，创建生成树和其稠密关联矩阵。
	if (!Adj) {
		cout << "图未创建" << endl;
		return ;
	}
	if (!Connect) {
		cout << "无生成树！" << endl;
		return ;
	}
	if (!Rel)
		InitRelMat();
	if (Spa) {
		cout << "生成树已被创建" << endl;
		return;
	}
	
	//创建生成树 和 生成树稠密关联矩阵 
	spanning_tree = new int[n - 1];
	this->st_adj_mat[0] = new int[n - 1];
	this->st_adj_mat[1] = new int[n - 1];
	memset(this->spanning_tree, 0, (n - 1) * sizeof(int));
	memset(this->st_adj_mat[0], 0, (n - 1) * sizeof(int));
	memset(this->st_adj_mat[1], 0, (n - 1) * sizeof(int));
	UnionSet u(n);
	u.init();
	//用稠密关联矩阵初始化生成树 和 生成树稠密关联矩阵 
	int index = 0;
	for (int i = 0; i < e; ++i) {
		int v1 = this->simp_rel_mat[0][i], v2 = this->simp_rel_mat[1][i];
		if (!u.same(v1, v2)) {
			u.unite(v1, v2);
			st_adj_mat[0][index] = this->simp_rel_mat[0][i];
			st_adj_mat[1][index] = this->simp_rel_mat[1][i];
			spanning_tree[index++] = i;
		}
	}
	Spa = true;
}

bool G::InitSegSys()
{
	//每次选择生成树稠密关联矩阵的一条边，删除它；对生成树剩下的两个连通分支求并查集，然后将端点属于不同连通分支的边加入。
	//创建基本割集系统 
	if (!Connect) {
		cout << "无割集系统！" << endl;
		return false; 
	}
	if (Seg) return true;
	this->seg_matrix = new int*[n - 1];
	for (int i = 0; i < n - 1; ++i) {
		seg_matrix[i] = new int[e];
		memset(seg_matrix[i], 0, e * sizeof(int));
	}
	
	for (int i = 0; i < n - 1; ++i) {
		UnionSet u(n);
		u.init();
		//对两个连通分支求并查集 
		for (int j = 0; j < n - 1; ++j) {
			if (i == j) continue;
			int v1 = this->st_adj_mat[0][j], v2 = this->st_adj_mat[1][j];
			u.unite(v1, v2);
		}
		//连接两个连通分支的边 
		for (int k = 0; k < e; ++k) {
			int v1 = this->simp_rel_mat[0][k], v2 = this->simp_rel_mat[1][k];
			if (!u.same(v1, v2))
				seg_matrix[i][k] = 1;
		}
	}
	
	return Seg = true;
}

void G::ShowDuanSet()
{
	if (!this->InitSegSys()) {
		cout << "没有断集" << endl;
		return;
	}
	
	cout << "断集空间: {empty, ";
	//使用位运算求出2^(n - 1)个断集 
	int iter = 1 << (n - 1);
	int *edge = new int[e];
	for (int i = 1; i < iter; ++ i) {
		memset(edge, 0, e * sizeof(int));
		int x = i;
		for (int j = 0; j < n - 1; ++j) {
			if ( (x >> j) & 0x1 ) {
				for (int k = 0; k < e; ++k) {
					edge[k] ^= this->seg_matrix[j][k];
				}
			}
		}
		cout << "{";
		bool flag = false;
		for (int j = 0; j < e; ++j) {
			if (edge[j]) {
				if (flag) cout << ",";
				flag = true;
				cout << "e" << j + 1;
			}
		}
		cout << "}";
		if (flag && i != iter - 1) cout << ", ";
	}
	cout << "}\n";
}

bool G::InitCirSys() {
	if (!Connect || (e == n - 1) ){
		cout << "无回路系统" << endl;
		return false;
	}
	
	if (Cir) return true;
	
	//初始化矩阵 
	this->cir_matrix = new int*[e - n + 1];
	for (int i = 0; i < e - n + 1; ++i) {
		this->cir_matrix[i] = new int[e];
		memset(cir_matrix[i], 0, e * sizeof(int));
	}
	//由于生成树的存储方式是使用长度为n-1的数组升序存储各边标号， 
	int ptr = 0;
	for (int i = 0; i < e; ++i) {
		if (ptr < n - 1) {
			if (i == this->spanning_tree[ptr]) {
				ptr++;
				continue;
			}
		}
		this->cir_matrix[i - ptr][i] = 1;
		//求出e - n + 1条边中一条的两边顶点标号 
		int p1 = 0, p2 = 0;
		p1 = this->simp_rel_mat[0][i];
		p2 = this->simp_rel_mat[1][i];
		for (int j = 0; j < n - 1; ++j) {
			UnionSet u(n);
			u.init();
			for (int k = 0; k < n - 1; ++k) {
				if (j != k) u.unite(this->st_adj_mat[0][k], this->st_adj_mat[1][k]);
			}
			if (!u.same(p1, p2)) {
				this->cir_matrix[i - ptr][j] = 1;
			}
		}
	} 
	return Cir = true;
}

void G::ShowHuanLuSys()
{
	if (!Cir) {
		cout << "无环路空间" << endl;
		return ; 
	}
	
	cout << "环路空间:{empty,";
	int iter = 1 << (e - n + 1);
	int *edge = new int[e];
	for (int i = 1; i < iter; ++i) {
		memset(edge, 0, e * sizeof(int));
		int x = i;
		for (int j = 0; j < e - n + 1; ++j) {
			if ( (x >> j) & 0x1) {
				for (int k = 0; k < e; ++k) {
					edge[k] ^= this->cir_matrix[j][k];
				}
			}
		}
		bool flag = false;
		for (int j = 0; j < e; ++j) {
			if (edge[j]) {
				flag = true;
				cout << "e" << j + 1;
			}
		}
		if (flag && i != iter - 1) cout << ", ";
	}
	cout << "}\n";
}

void G::PrintAdjMat()
{
	if (!Adj) {
		cout << "相邻矩阵未创建." << endl;
		return;
	}
	cout << "相邻矩阵: " << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << this->adjacent_matrix[i][j] << " ";
		}
		cout << "\n";
	} 
}

void G::PrintRelMat(){
	if (!Rel) {
		cout << "关联矩阵未创建.";
		return;
	}
	cout << "关联矩阵: " << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < e; ++j) {
			cout << this->relative_matrix[i][j] << " ";
		}
		cout << "\n";
	}
}

void G::PrintSpanTree(){
	if (!Spa) {
		cout << "生成树未创建.";
		return;
	}
	cout << "生成树: ";
	for(int i = 0; i < n - 1; ++i){
		cout << "e" << this->spanning_tree[i] + 1;
	}
	cout << endl;
}

void G::PrintSimpRelMat(){
	if (!Rel)
		return;
	cout << "稠密关联矩阵: " << endl;
	for (int i = 0; i < e; ++i) {
		cout << "e" << i << " " << this->simp_rel_mat[0][i] << " " << this->simp_rel_mat[1][i] << endl;
	}
}

void G::PrintStRelMat(){
	if (!Spa)
		return;
	cout << "生成树关联矩阵: " << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n - 1; ++j) {
			if (this->st_adj_mat[0][j] == i || this->st_adj_mat[1][j] == i) {
				cout << 1 << " ";
			} else {
				cout << 0 << " ";
			}
		}
		cout << endl;
	}
}

void G::PrintSegSys()
{
	cout << "基本割集系统: {";
	for (int i = 0; i < n - 1; ++i) {
		bool flag = false;
		cout << "{";
		for (int j = 0; j < e; ++j) {
			if (this->seg_matrix[i][j]) {
				if (flag) cout << ",";
				flag = true;
				cout << "e" << j + 1;
			}
		}
		cout << "}";
		if (i != n - 2) cout << ",";
	}
	cout << "}\n";
}

void G::PrintCirSys()
{
	
	cout << "基本回路系统：{";
	for (int i = 0; i < e - n + 1; ++i) {
		for (int j = 0; j < e; ++j) {
			if (this->cir_matrix[i][j]) {
				cout << "e" << j + 1;
			}
		}
		if (i != e - n) cout << ",";
	}
	cout << "}\n";
}

G::~G()
{
	for (int i = 0; i < n; ++i){
		if (Adj) delete[] adjacent_matrix[i];
		if (Rel) delete[] relative_matrix[i];
	}
	if (Seg) {
		for (int i = 0; i < n - 1; ++i) 
			delete[] seg_matrix[i];
	}
	if (Cir) {
		for (int i = 0; i < e - n + 1; ++i) 
			delete[] cir_matrix[i];
	}
	for (int i = 0; i < 2; ++i) {
		if (Spa) delete[] st_adj_mat[i];
		if (Rel) delete[] simp_rel_mat[i];
	}
	if (Adj) delete[] adjacent_matrix;
	if (Rel) delete[] relative_matrix;
	if (Spa) delete[] spanning_tree;
	if (Seg) delete[] seg_matrix;
	if (Cir) delete[] cir_matrix;
}
