//O(m log n)

struct edge {
	int from, to, w;
	
	edge(int _from = 0, int _to = 0, int _w = 0) {
		from = _from;
		to = _to;
		w = _w;
	}
};

int n;
ll d[MAXN];
vector<int> g[MAXN];
edge e[MAXM];

struct comp {
    bool operator () (int a, int b) {
        if (d[a] != d[b])
            return d[a] < d[b];
        return a < b;
    }
};

void dijkstra(int st) {
    for (int i = 0; i < n; i++) {
        d[i] = INF;
    }
    d[st] = 0;
    
    set<int, comp> s;
    s.insert(st);
    while (!s.empty()) {
        int cur = *s.begin();
        s.erase(s.begin());
        
        for (auto i : g[cur]) {
            edge ed = e[i];
            int to = ed.to;
            if (to == cur)
                to = ed.from;

            if (d[to] > d[cur] + ed.w) {
                s.erase(to);
                d[to] = d[cur] + ed.w;
                s.insert(to);
            }
        }
    }
}

//O(n^2)

int d[MAXN], par[MAXN], w[MAXN][MAXN];
bool used[MAXN];

void dijkstra(int x) {
    forn(i, n) 
		d[i] = INF / 2;
    d[x] = 0;
    par[x] = 0;

    int cmin;
    forn(i, n) {
        cmin = -1;
        forn(j, n)
            if (!used[j] && ((cmin == -1) || (d[j] < d[cmin])))
                cmin = j;
        used[cmin] = 1;

        forn(j, n)
            if ((w[cmin][j] != -1) && (d[j] > d[cmin] + w[cmin][j])) {
                d[j] = d[cmin] + w[cmin][j];
                par[j] = cmin;
            }
    }
}