int d[MAXN], par[MAXN], w[MAXN][MAXN];
bool used[MAXN];

void dijkstra(int x) {
    forn(i, n) d[i] = INF / 2;
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

set<pair<int, int> > q;
vector<pair<int, int> > g[MAXN];

void dijkstra(int s, int f) {
    pair<int, int> temp;
    int a, b;

    par[s] = s;
    for (int i = 1; i <= n; i++) {
        d[i] = (i != s) * INF;
        q.insert(make_pair(d[i], i));
    }

    while (!q.empty()) {
        temp = *q.begin();
        if (temp.first == INF)
            return;
        q.erase(q.begin());
        a = temp.second;
        for (int i = 0; i < g[a].size(); i++) {
            b = g[a][i].second;
            if (d[b] > d[a] + g[a][i].first) {
                q.erase(make_pair(d[b], b));
                d[b] = d[a] + g[a][i].first;
                q.insert(make_pair(d[b], b));
                par[b] = a;
            }
        }
    }
}