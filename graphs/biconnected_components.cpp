<<<<<<< HEAD
//get biconnected components (a.k.a. blocks) in undirected graph

const int MAXN = 400500;

int n, m; //G = (V, E), n = |V|, m = |E|
pii edges[MAXN]; //list of all edges in graph
vector<pii> g[MAXN]; //g[v] = {e_i = {w, index}}_i
vi childs[MAXN]; //childs of vertex in DFS tree traversal
int comps; //number of components
vi comp[MAXN]; //comp[i] = list of edges in ith component
bool isPt[MAXN]; //isPt[v] <=> v is an articulation point
int used[MAXN], tmr, tin[MAXN], fup[MAXN]; //arrays for dfs

void dfs(int v, int pid) {
    used[v] = 1;
    tin[v] = tmr++;
    fup[v] = tin[v];

    for (auto e: g[v]) {
        int w = e.X;
        int id = e.Y;
        
        if (id == pid) {
            continue;
        }
        
        if (!used[w]) {
            dfs(w, id);
            
            childs[v].pb(w);
            fup[v] = min(fup[v], fup[w]);
        } else {
            fup[v] = min(fup[v], tin[w]);
        }
    }

    if (pid == -1) {
        isPt[v] = ((int)childs[v].size() >= 2);
    } else {
        for (auto w: childs[v]) {
            if (fup[w] >= tin[v]) {
                isPt[v] = 1;
            }
        }
    }
}

void getComponents(int v, int num, int pid) {
    used[v] = 1;
    
    for (auto e: g[v]) {
        int w = e.X;
        int id = e.Y;
        
        if (id == pid) {
            continue;
        }
        
        if (used[w]) {
            if (tin[w] < tin[v]) {
                comp[num].push_back(id);
            }
            continue;
        }

        if (isPt[v] && fup[w] >= tin[v]) {
            comps++;
            comp[comps - 1].push_back(id);
            getComponents(w, comps - 1, id);
        } else {
            comp[num].push_back(id);
            getComponents(w, num, id);
        }
    }
}

int main() {
    
    scanf("%d%d", &n, &m);
    
    forn(i, m) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--, b--;

        edges[i] = {a, b};
        
        g[a].pb({b, i});
        g[b].pb({a, i});
    }

    memset(used, 0, sizeof(used));
    memset(isPt, 0, sizeof(isPt));
    tmr = 0;
    dfs(0, -1);

    memset(used, 0, sizeof(used));

    if (!isPt[0]) {
        comps = 1;
        getComponents(0, 0, -1);
    } else {
        comps = 0;
        getComponents(0, -1, -1);
    }

    return 0;
}
=======
//get biconnected components (a.k.a. blocks) in undirected graph

const int MAXN = 400500;

int n, m; //G = (V, E), n = |V|, m = |E|
pii edges[MAXN]; //list of all edges in graph
vector<pii> g[MAXN]; //g[v] = {e_i = {w, index}}_i
vi childs[MAXN]; //childs of vertex in DFS tree traversal
int comps; //number of components
vi comp[MAXN]; //comp[i] = list of edges in ith component
bool isPt[MAXN]; //isPt[v] <=> v is an articulation point
int used[MAXN], tmr, tin[MAXN], fup[MAXN]; //arrays for dfs

void dfs(int v, int pid) {
    used[v] = 1;
    tin[v] = tmr++;
    fup[v] = tin[v];

    for (auto e: g[v]) {
        int w = e.X;
        int id = e.Y;
        
        if (id == pid) {
            continue;
        }
        
        if (!used[w]) {
            dfs(w, id);
            
            childs[v].pb(w);
            fup[v] = min(fup[v], fup[w]);
        } else {
            fup[v] = min(fup[v], tin[w]);
        }
    }

    if (pid == -1) {
        isPt[v] = ((int)childs[v].size() >= 2);
    } else {
        for (auto w: childs[v]) {
            if (fup[w] >= tin[v]) {
                isPt[v] = 1;
            }
        }
    }
}

void getComponents(int v, int num, int pid) {
    used[v] = 1;
    
    for (auto e: g[v]) {
        int w = e.X;
        int id = e.Y;
        
        if (id == pid) {
            continue;
        }
        
        if (used[w]) {
            if (tin[w] < tin[v]) {
                comp[num].push_back(id);
            }
            continue;
        }

        if (isPt[v] && fup[w] >= tin[v]) {
            comps++;
            comp[comps - 1].push_back(id);
            getComponents(w, comps - 1, id);
        } else {
            comp[num].push_back(id);
            getComponents(w, num, id);
        }
    }
}

int main() {
    
    scanf("%d%d", &n, &m);
    
    forn(i, m) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--, b--;

        edges[i] = {a, b};
        
        g[a].pb({b, i});
        g[b].pb({a, i});
    }

    memset(used, 0, sizeof(used));
    memset(isPt, 0, sizeof(isPt));
    tmr = 0;
    dfs(0, -1);

    memset(used, 0, sizeof(used));

    if (!isPt[0]) {
        comps = 1;
        getComponents(0, 0, -1);
    } else {
        comps = 0;
        getComponents(0, -1, -1);
    }

    return 0;
}
>>>>>>> origin/master
