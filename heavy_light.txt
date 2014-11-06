const int MAXN = 100500;
const int MAXK = 131072;

int a, b;
int n, m, tmr, ways, wsz;
vi g[MAXN];
int sz[MAXN], tin[MAXN], tout[MAXN], heavyparent[MAXN], heavychild[MAXN], value[MAXN];
int par[MAXN][20];
int vpos[MAXN], idway[MAXN], head[MAXN];
int tree[2 * MAXK + 2];

void dfs(int v, int p) {
	tin[v] = tmr++;
	sz[v] = 1;
	
	par[v][0] = p;
	forab(i, 1, 20)
		par[v][i] = par[par[v][i - 1]][i - 1];
		
	for (auto w: g[v])
		if (w != p) {
			dfs(w, v);
			sz[v] += sz[w];
		}
		
	for (auto w: g[v])
		if (w != p) {
			if (2 * sz[w] >= sz[v]) {
				heavyparent[w] = v;
				heavychild[v] = w;
			}
		}	
		
	tout[v] = tmr++;
}

void dfs2(int v, int p) {
	for (auto w: g[v])
		if (w != p)
			dfs2(w, v);
		
	if (heavychild[v] == -1) {
		int vv = v;
		idway[vv] = ways;
		vpos[vv] = wsz;
		wsz++;
		
		while (heavyparent[vv] != -1) {
			vv = heavyparent[vv];
			idway[vv] = ways;
			vpos[vv] = wsz;
			wsz++;
		}
		
		head[ways] = vv;	 
		ways++;
	}
}

bool parent(int v, int w) {
	return tin[v] <= tin[w] && tout[w] <= tout[v];
}

int lca(int v, int w) {
	if (parent(v, w))
		return v;
	if (parent(w, v))
		return w;
	
	for (int i = 19; i >= 0; i--)
		if (!parent(par[v][i], w))
			v = par[v][i];
	return par[v][0];
}	 

void buildTree() {
	forn(i, 2 * MAXK + 2)
		tree[i] = 0;
	forn(i, n)
		tree[MAXK + i] = value[i];
	for (int i = MAXK - 1; i > 0; i--)
		tree[i] = max(tree[2 * i], tree[2 * i + 1]);
}

void setVal(int k, int x) {
	int id = MAXK + k;
	tree[id] = x;
	
	while (id > 1) {
		id >>= 1;
		tree[id] = max(tree[2 * id], tree[2 * id + 1]);	
	}
}

int getMax(int v, int l, int r, int lx, int rx) {
	if (rx < l || r < lx)
		return 0;
	if (lx <= l && r <= rx)
		return tree[v];
	return max(getMax(v * 2, l, (l + r) >> 1, lx, rx), getMax(v * 2 + 1, ((l + r) >> 1) + 1, r, lx, rx));
}

int getMax(int l, int r) {
	return getMax(1, 1, MAXK, l + 1, r + 1);
}

int getPath(int a, int b) {
	if (idway[a] == idway[b])
		return getMax(vpos[a], vpos[b]);
	
	int id = idway[a], ha = head[id];
	int ans = getMax(vpos[a], vpos[ha]);
	a = par[head[id]][0];
	
	while (true) {
		id = idway[a];
		ha = head[id];

		if (id == idway[b])
			return max(ans, getMax(vpos[a], vpos[b]));
		
		ans = max(ans, getMax(vpos[a], vpos[ha]));
		a = par[ha][0];	
	}
}

<...>

memset(heavyparent, -1, sizeof(heavyparent));
memset(heavychild, -1, sizeof(heavychild));

dfs(0, 0);
	
ways = 0;
wsz = 0;
dfs2(0, 0);	

int ans = max(getPath(a, lca(a, b)), getPath(b, lca(a, b)))