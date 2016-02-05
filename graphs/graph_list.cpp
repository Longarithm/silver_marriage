int head[MAXN], nxt[MAXM], id[MAXM], val[MAXM];

void addEdge(int a, int b, int w) {
	id[c] = b;
	val[c] = w;
	nxt[c] = head[a];
	head[a] = c++;
}

void getAll(int v) {
	for (int i = head[v]; i >= 0; i = nxt[i]) {
		to = id[i];
		//do something
	}
}

