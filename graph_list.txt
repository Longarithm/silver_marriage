int fir[MAXN], nxt[MAXM], id[MAXM], z[MAXM];

void addEdge(int a, int b, int w) {
	id[c] = b;
	z[c] = w;
	nxt[c] = fir[a];
	fir[a] = c++;
}

void getAll(int v) {
	for (int i = fir[v]; i >= 0; i = nxt[i]) {
		to = id[i];
		//do something
	}
}

