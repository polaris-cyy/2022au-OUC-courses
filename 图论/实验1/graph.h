#include "unionset.h"
using namespace std;

class DegreeArray {
	public:
		DegreeArray(){is_graph=is_simple_graph=is_connect=false, is_euler=true;}
		void ReadDegree();
		bool IsGraph();
		bool IsSimpleGraph();
		void PrintGraph();
		bool IsConnect();
		bool IsEuler();
		void FindEulerCycle();
		void GraphTest();
		~DegreeArray();
	private:
		bool is_graph, is_simple_graph, is_connect, is_euler;
		vector< pair<int, int> > degree_array;
		int**graph;
};

void DegreeArray::ReadDegree() {
	char c;
	int d = 0, cnt = 0;
	cin >> c;
	while (c != ')') {
		cin >> d >> c;
		degree_array.push_back(make_pair(d, cnt++));
	}
}

bool DegreeArray::IsGraph() {
	if (is_graph) return true;
	int d = 0;
	for (auto degree : degree_array) {
		d = d + degree.first;
		if (degree.first % 2) is_euler = false;
	}
	if (d % 2) return false;
	return is_graph = true;
}

bool DegreeArray::IsSimpleGraph() {
	if (is_simple_graph) return true;
	if (!is_graph) return false;
	sort(this->degree_array.begin(), this->degree_array.end(),
		[](pair<int, int> a, pair<int, int> b)->bool{return a.first > b.first;}	);

	int size = degree_array.size();
	graph = new int*[size];
	for (int i = 0; i < size; ++i) {
		graph[i] = new int[size];
		memset(graph[i], 0, size * sizeof(int));
	}
	for (int i = 0; i < size; ++i) {
		if (degree_array[i].first >= size - i) {
			for (int i = 0; i < size; ++i)
				delete[] graph[i];
			delete[] graph;
			return false;
		} else {
			for (int j = 1; j <= degree_array[i].first; ++j) {
				if (degree_array[i + j].first == 0) {
					for (int i = 0; i < size; ++i)
						delete[] graph[i];
					delete[] graph;
					return false;
				} else {
					graph[degree_array[i].second][degree_array[i + j].second] = graph[degree_array[i + j].second][degree_array[i].second] = 1;
					degree_array[i + j].first--;
				}
			}
			sort(this->degree_array.begin() + i + 1, this->degree_array.end(),
				[](pair<int, int> a, pair<int, int> b)->bool{return a.first > b.first;}	);
		}
	}

	return is_simple_graph = true;
}

void DegreeArray::PrintGraph() {
	if (!is_simple_graph) return;

	for (int i = 0; i < degree_array.size(); ++i) {
		for (int j = 0; j < degree_array.size(); ++j) {
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
}

bool DegreeArray::IsConnect() {
	if (is_connect) return true;
	if (!is_simple_graph) return false;

	int size = degree_array.size();
	UnionSet u(size);
	u.init();
	for (int i = 0; i < size; ++i) {
		for (int j = i + 1; j < size; ++j) {
			if (graph[i][j]) {
				u.unite(i, j);
			}
		}
	}

	for (int i = 1; i < size; ++i) {
		if (!u.same(0, i)) return false;
	}

	return is_connect = true;
}

bool DegreeArray::IsEuler() {
	if (!is_connect) return false;
	return is_euler;
}

void DegreeArray::GraphTest() {
	long long int a = 2147483647;
	unsigned b = 2147483647;
	cout << a * b << endl;
	this->ReadDegree();
	if (this->IsGraph() ) {
		cout << "可图化" << endl;
	} else {
		cout << "不可图化" << endl;
		return;
	}
	if (this->IsSimpleGraph() ) {
		cout << "可简单图化" << endl;
	} else {
		cout << "不可简单图化" << endl;
		return;
	}
	if ( this->IsConnect() ) {
		cout << "连通图" << endl;
	} else {
		cout << "非连通图" << endl;
		return;
	}
	if ( this->IsEuler() ){
		cout << "是欧拉图" << endl;
	} else {
		cout << "不是欧拉图" << endl;
		return;
	}
	cout << "邻接矩阵: " << endl;
	this->PrintGraph();
}

DegreeArray::~DegreeArray(){
	int size = degree_array.size();
	if(size > 0) {
		for (int i = 0; i < size; ++i) {
			delete[] graph[i];
		}
	}
	delete[] graph;
}