class UnionSet{
	public:
		UnionSet(){length = 0;}
		UnionSet(int l){length = l;};
		void init();
		bool check(int v);
		int find(int v);
		bool same(int v1, int v2);
		void unite(int v1, int v2);
		~UnionSet(){delete[] par;};
	private:
		int length;
		int *par;
};

bool UnionSet::check(int v){
	if (v < length && v >= 0){
		return true;
	}
	return false;
}

void UnionSet::init()
{
	if (length) {
		par = new int[length];
		for (int i = 0; i < length; ++i) {
			par[i] = i;
		}
	}
}

int UnionSet::find(int v)
{
	if (check(v)) {
		if (par[v] == v) {
			return v;
		}
		return par[v] = find(par[v]);
	}
	return -1;
}

bool UnionSet::same(int v1, int v2)
{
	if (check(v1) && check(v2)) 
		return find(v1) == find(v2);
	return false;
}

void UnionSet::unite(int v1, int v2)
{
	if (check(v1) && check(v2)) 
		par[find(v1)] = find(v2);
}
