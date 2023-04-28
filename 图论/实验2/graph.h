#include "unionset.h"
using namespace std;

class G{
	friend class UnionSet;
	
	public:
		G();
		void InitGraph(int x);	//��ʼ��ͼ 
		void InitRelMat();	//���ھ���
		int CalMatrix(int**Matrix, int n);	//�����ά����ͽ�������������ʽ��ֵ 
		int STCount();	//���������� 
		void PrintSTCount();	//��ӡ���������� 
		void InitSpanTree();	//������ 
		bool InitSegSys();	//�����ϵͳ 
		void ShowDuanSet();	//�ϼ��ռ� 
		bool InitCirSys();	//������·ϵͳ 
		void ShowHuanLuSys();	//��·ϵͳ 
		void PrintAdjMat();	//��ӡ���ھ��� 
		void PrintRelMat();	//��ӡ�������� 
		void PrintSpanTree();	//��ӡ������ 
		void PrintSimpRelMat();	//��ӡ�������󡤳��ܰ� 
		void PrintStRelMat();	//��ӡ�����������ܰ� 
		void PrintSegSys();	//��ӡ�����ϵͳ 
		void PrintCirSys();	//��ӡ������·ϵͳ 
		
		~G();
		
	private:
		int n, e, st_cnt;	//��������ͱ���, ���������� 
		bool Adj, Rel, Spa, Seg, Cir;	//�Ƿ��ʼ�� ���ھ��󣬹��������������������ϵͳ��������·ϵͳ�� 
		bool Connect;	//�Ƿ���ͨͼ 
		int **adjacent_matrix;	//���ھ��� 
		int **relative_matrix;	//�������� 
		int **seg_matrix;	//�����ϵͳ 
		int **cir_matrix;	//������·ϵͳ 
		int *simp_rel_mat[2];	//ȥ��0�Ĺ������� 
		int *spanning_tree;	//������ 
		int *st_adj_mat[2];	//������ȥ��0�Ĺ������� 
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
	//����Ѿ����������ء����򣬴���x * x��ͼ�����ж���ͨ�ԡ� 
	if (Adj) {
		cerr << "ͼ�ѱ�������" << endl;
		return;
	}
	
	//��ʼ��ͼ 
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
	//���ھ��󴴽���ϡ� 
	Adj = true;
	
	//�ж��Ƿ���ͨ 
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
	//	����Ѿ��������������δ��ʼ��ͼ�����أ����򣬴���n * e�Ĺ������󣬺�ȥ��0�ĳ��ܹ������� 
	if (!Adj) 
		cout << "ͼδ������" << endl;
	if (Rel) {
		cout << "���������ѱ�������" << endl;
		return;
	}
	
	//���ֶ���ȷ������ 
	int degree = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			degree += adjacent_matrix[i][j];
		}
	}
	e = degree / 2;
	
	//������������ 
	relative_matrix = new int*[n];
	for (int i = 0; i < n; ++i) {
		relative_matrix[i] = new int[e];
		memset(this->relative_matrix[i], 0, e * sizeof(int));
	}
	
	//�������ܹ������� 
	for (int i = 0; i < 2; ++i) {
		this->simp_rel_mat[i] = new int[e];
		memset(this->simp_rel_mat[i], 0, e * sizeof(int));
	} 
	//��ʼ����������ͳ��ܹ������� 
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
		//������
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

//ʹ�þ���������������������� 
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
	cout << "����������: " << st_cnt << endl;
}

void G::InitSpanTree()
{
	//	���û�д����������󣬵���InitRelMat����������������� �����أ����򣬴���������������ܹ�������
	if (!Adj) {
		cout << "ͼδ����" << endl;
		return ;
	}
	if (!Connect) {
		cout << "����������" << endl;
		return ;
	}
	if (!Rel)
		InitRelMat();
	if (Spa) {
		cout << "�������ѱ�����" << endl;
		return;
	}
	
	//���������� �� ���������ܹ������� 
	spanning_tree = new int[n - 1];
	this->st_adj_mat[0] = new int[n - 1];
	this->st_adj_mat[1] = new int[n - 1];
	memset(this->spanning_tree, 0, (n - 1) * sizeof(int));
	memset(this->st_adj_mat[0], 0, (n - 1) * sizeof(int));
	memset(this->st_adj_mat[1], 0, (n - 1) * sizeof(int));
	UnionSet u(n);
	u.init();
	//�ó��ܹ��������ʼ�������� �� ���������ܹ������� 
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
	//ÿ��ѡ�����������ܹ��������һ���ߣ�ɾ��������������ʣ�µ�������ͨ��֧�󲢲鼯��Ȼ�󽫶˵����ڲ�ͬ��ͨ��֧�ı߼��롣
	//���������ϵͳ 
	if (!Connect) {
		cout << "�޸ϵͳ��" << endl;
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
		//��������ͨ��֧�󲢲鼯 
		for (int j = 0; j < n - 1; ++j) {
			if (i == j) continue;
			int v1 = this->st_adj_mat[0][j], v2 = this->st_adj_mat[1][j];
			u.unite(v1, v2);
		}
		//����������ͨ��֧�ı� 
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
		cout << "û�жϼ�" << endl;
		return;
	}
	
	cout << "�ϼ��ռ�: {empty, ";
	//ʹ��λ�������2^(n - 1)���ϼ� 
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
		cout << "�޻�·ϵͳ" << endl;
		return false;
	}
	
	if (Cir) return true;
	
	//��ʼ������ 
	this->cir_matrix = new int*[e - n + 1];
	for (int i = 0; i < e - n + 1; ++i) {
		this->cir_matrix[i] = new int[e];
		memset(cir_matrix[i], 0, e * sizeof(int));
	}
	//�����������Ĵ洢��ʽ��ʹ�ó���Ϊn-1����������洢���߱�ţ� 
	int ptr = 0;
	for (int i = 0; i < e; ++i) {
		if (ptr < n - 1) {
			if (i == this->spanning_tree[ptr]) {
				ptr++;
				continue;
			}
		}
		this->cir_matrix[i - ptr][i] = 1;
		//���e - n + 1������һ�������߶����� 
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
		cout << "�޻�·�ռ�" << endl;
		return ; 
	}
	
	cout << "��·�ռ�:{empty,";
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
		cout << "���ھ���δ����." << endl;
		return;
	}
	cout << "���ھ���: " << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << this->adjacent_matrix[i][j] << " ";
		}
		cout << "\n";
	} 
}

void G::PrintRelMat(){
	if (!Rel) {
		cout << "��������δ����.";
		return;
	}
	cout << "��������: " << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < e; ++j) {
			cout << this->relative_matrix[i][j] << " ";
		}
		cout << "\n";
	}
}

void G::PrintSpanTree(){
	if (!Spa) {
		cout << "������δ����.";
		return;
	}
	cout << "������: ";
	for(int i = 0; i < n - 1; ++i){
		cout << "e" << this->spanning_tree[i] + 1;
	}
	cout << endl;
}

void G::PrintSimpRelMat(){
	if (!Rel)
		return;
	cout << "���ܹ�������: " << endl;
	for (int i = 0; i < e; ++i) {
		cout << "e" << i << " " << this->simp_rel_mat[0][i] << " " << this->simp_rel_mat[1][i] << endl;
	}
}

void G::PrintStRelMat(){
	if (!Spa)
		return;
	cout << "��������������: " << endl;
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
	cout << "�����ϵͳ: {";
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
	
	cout << "������·ϵͳ��{";
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
