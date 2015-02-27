struct edge {
	int v, w, f, c, id, inv;
	edge() {};
	edge(int _v, int _w, int _f, int _c, int _id, int _inv): 
			v(_v), w(_w), f(_f), c(_c), id(_id), inv(_inv) {};
};

int n, m, BEGIN, END, tmr;
ll ans;
int used[MAXN], level[MAXN], ptr[MAXN];
vector<edge> edges;
vi g[MAXN];

void addEdge(int v, int w, int c) {
	int id = edges.size();
	edges.pb(edge(v, w, 0, c, id, id + 1));
	edges.pb(edge(w, v, 0, 0, id + 1, id));
	g[v].pb(id);
	g[w].pb(id + 1);
}

int q[MAXN], ql, qr;
         
bool bfs(int f) {
	tmr++;
	ql = qr = 0;
	used[BEGIN] = tmr;
	level[BEGIN] = 0;
	q[qr++] = BEGIN;
	
	while (qr - ql > 0) {
		int v = q[ql++];
		
		for (auto eid: g[v]) {
			int w = edges[eid].w;
			if (used[w] != tmr && edges[eid].c - edges[eid].f >= f) {
				used[w] = tmr;
				level[w] = level[v] + 1;
				q[qr++] = w;            				
			}
		}
	}
	
	return used[END] == tmr;
}

bool dfs(int v, int f) {
	if (v == BEGIN)
		tmr++;
	if (v == END)
		return 1;
	used[v] = tmr;
	
	for (; ptr[v] < (int)g[v].size(); ptr[v]++) {
		int eid = g[v][ptr[v]];
		if (level[v] + 1 == level[edges[eid].w] && edges[eid].c - edges[eid].f >= f && dfs(edges[eid].w, f)) {
			edges[eid].f += f;
			edges[edges[eid].inv].f -= f;
			return 1; 
		}
	}
	
	return 0;
}

<...>
	
	BEGIN = 0;
	END = n - 1;
	ans = 0;
	for (int flow = (1 << 30); flow > 0; flow >>= 1) {
		while (bfs(flow)) {
			for (int i = 0; i < n; i++)
				ptr[i] = 0;
			while (dfs(0, flow))
				ans += flow;
		}	
	}