vi g[MAXN];
int parent[MAXN];
int level[MAXN];

int dfs(int v, int &center, int sz = 0, int p = -1) {
	int sum = 1;
	for (auto w: g[v])
		if (w != p && level[w] == -1)
			sum += dfs(w, center, sz, v);	

	if (center == -1 && 2 * sum >= sz)
		center = v;	
	return sum;
}

void build(int v, int L = 0, int p = -1) {
	int center;
	dfs(v, center = -1, dfs(v, center));

	parent[center] = p;
	level[center] = L;

	for (auto w: g[center])
		if (level[w] == -1)
			build(w, L + 1, center);		
}

//...

memset(level, -1, sizeof(level));
build(0);