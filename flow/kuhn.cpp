bool used[MAXN];
int l[MAXN], r[MAXN];
vector<int> graph[MAXN];

void init() {
	for (int i = 0; i < MAXN; i++) {
		l[i] = -1;
		r[i] = -1;
	}
}

bool dfs(int v) {
	if (used[v])
		return 0;
	used[v] = 1;

	int w;
	for (int i = 0; i < graph[v].size(); i++) {
		w = graph[v][i];
		if (r[w] == -1 || dfs(r[w])) {
			l[v] = w;
			r[w] = v;
			return 1;
		}
	}
	return 0;
}
