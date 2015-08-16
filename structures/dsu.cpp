int rt[MAXN], rk[MAXN];

void makeSets(int v) {
	rt[v] = v;
	rk[v] = 0;
}

int findSet(int v) {
	if (rt[v] != v)
		rt[v] = findSet(rt[v]);
	return rt[v];
}

void unionSets(int a, int b) {
	int x = findSet(a);
	int y = findSet(b);
	if (x != y) {
		if (rk[x] > rk[y])
			rt[y] = x;
		else
			rt[x] = y;
		if (rk[x] == rk[y])
			rk[y]++;
	}
}