#pragma once
#include <iostream>
#include <vector>
using namespace std;

class UnionSet {
public:
	UnionSet(int n);
	int find(int x);
	bool same(int x, int y);
	void unite(int x, int y);
	~UnionSet();
private:
	vector<int> u;
};

UnionSet::UnionSet(int n) {
	u.resize(n);
	for (int i = 0; i < n; ++i) {
		u[i] = i;
	}
}

int UnionSet::find(int x) {
	if (u[x] == x) return x;
	return u[x] = find(u[x]);
}

bool UnionSet::Same(int x, int y) {
	return find(u[x]) == find(u[y]);
}

void unite(int x, int y) {
	u[find(x)] = find(y);
}