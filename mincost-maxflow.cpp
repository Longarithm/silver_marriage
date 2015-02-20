struct edge {
	int w, f, c, cost;
	int inv;
	
	edge(){};
	edge(int _w, int _f, int _c, int _cost, int _inv):
		w(_w), f(_f), c(_c), cost(_cost), inv(_inv) {};
};

int START, FINISH, SZ;
vector<vi> g(MAXN);
vector<edge> edges;
int d[MAXN], par[MAXN], parid[MAXN];
bool used[MAXN];

void addEdge(int v, int w, int capacity, int cost) {
	int cnt = edges.size();
	edges.push_back(edge(w, 0, capacity, cost, cnt + 1));
	edges.push_back(edge(v, 0, 0, -cost, cnt));
	g[v].push_back(cnt);
	g[w].push_back(cnt + 1);
}        

queue<int> q;
bool findWay() {
	while (!q.empty())
		q.pop();
		
	forn(i, SZ) {
		d[i] = INF;
		used[i] = 0;
	}
	
	q.push(START);
	d[START] = 0;
	par[START] = -1;
	used[START] = 1;

	int from, to;
	while (!q.empty()) {
		from = q.front();
		used[from] = 0;
		q.pop();

		for (auto eid: g[from]) {
			to = edges[eid].w;
			if (edges[eid].c > edges[eid].f && d[from] + edges[eid].cost < d[to]) {
				d[to] = d[from] + edges[eid].cost;
				par[to] = from;
				parid[to] = eid;
				
				if (!used[to]) {
					q.push(to);
					used[to] = 1;
				}
			}
		}
	}

	return (d[FINISH] < INF);
}

int totalFlow, totalCost;
void getWay(int v) {
	if (par[v] == -1)
		return;

	getWay(par[v]);
	totalCost += edges[parid[v]].cost;
	edges[parid[v]].f++;
	edges[parid[v] ^ 1].f--;
}

...

	totalFlow = totalCost = 0;
	while (findWay()) {
		totalFlow++;
		getWay(FINISH);	
	}