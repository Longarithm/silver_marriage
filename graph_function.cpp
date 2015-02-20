int tt, t[MAXN], l[MAXN];
vector<vector<pair<int, int> > > graph(MAXN);
bool was[MAXN];

void dfs(int v, int pr) {
	t[v] = tt++;
	l[v] = t[v];
	was[v] = 1;
	forn(i, graph[v].size()) {
		int w = graph[v][i].first, id = graph[v][i].second;
		if (!was[w]) {
			dfs(w, id);
			//do something
			l[v] = min(l[v], l[w]);
		} else
			if (pr != id)
				l[v] = min(l[v], t[w]);
	}
}

<...>

forn(i, m) {
		scanf("%d%d\n", &x, &y);
		x--, y--;
		graph[x].push_back(make_pair(y, i));
		graph[y].push_back(make_pair(x, i));
	}