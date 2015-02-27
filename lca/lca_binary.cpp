int tmr, l;
int tin[MAXN], tout[MAXN], par[MAXN][21];
vi graph[MAXN];

void dfs(int v, int from) {
	tin[v] = tmr++;
	par[v][0] = from;
	forab(i, 1, l + 1)
		par[v][i] = par[par[v][i - 1]][i - 1];

	int to;
	forn(i, graph[v].size()) {
		to = graph[v][i];
		if (from != to)
			dfs(to, v);
	}
	tout[v] = tmr++;
}

bool parent(int a, int b) {
	return (tin[a] <= tin[b] && tin[b] <= tout[a]);
}

int lca(int a, int b) {
	if (parent(a, b)) return a;
	if (parent(b, a)) return b;
	for (int i = l; i >= 0; i--)
		if (!parent(par[a][i], b))
			a = par[a][i];
	return par[a][0];
}

<...>

	l = 0;
	while ((1 << l) <= n) l++;
	dfs(0, 0);