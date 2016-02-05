int d[MAXN], edges[MAXW][2], par[MAXN], w[MAXN][MAXN];
bool used[MAXN];

int way(int x) {
	if (x == START) {
		printf("%d", x + 1);
		return 0;
	}
	way(par[x]);
	printf(" %d", x + 1);
}

void relax(int v, int u) {
	if (d[u] > d[v] + w[v][u]) {
		d[u] = d[v] + w[v][u];
		par[u] = v;
	}
}

void FordBellman(int x) {
	forn(i, n) 
		d[i] = INF / 2;
	d[x] = 0;
	par[x] = 0;
	forn(i, n)
		forn(j, m) {
			relax(edges[j][0], edges[j][1]);
			relax(edges[j][1], edges[j][0]);
		}
}