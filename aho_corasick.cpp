struct vertex {
    int next[ALPHABET];
    bool leaf;
    int parent;
    int parch;
    int link, superlink;
    int go[ALPHABET];
};

vertex t[MAXN];
int c;

void init() {
    t[0].parent = t[0].link = t[0].superlink = -1;
    memset(t[0].next, -1, sizeof(t[0].next));
    memset(t[0].go, -1, sizeof(t[0].go));
    c = 1;
}

void add(string s) {
    int v = 0, nextch;
    forn(i, s.size()) {
        nextch = s[i] - 'A';
        if (t[v].next[nextch] == -1) {
            memset(t[c].next, -1, sizeof(t[c].next));
            memset(t[c].go, -1, sizeof(t[c].go));
            t[c].leaf = 0;
            t[c].parent = v;
            t[c].parch = nextch;
            t[c].link = -1;
            t[c].superlink = -1;
            t[v].next[nextch] = c;
            c++;
        }
        v = t[v].next[nextch];
    }
    t[v].leaf = 1;
}

int go(int v, int c);

int failure_f(int v) {
    if (t[v].link == -1) {
        if (v == 0 || t[v].parent == 0)
            t[v].link = 0;
        else
            t[v].link = go(failure_f(t[v].parent), t[v].parch);
    }
    return t[v].link;
}

int go(int v, int c) {
    if (t[v].go[c] == -1) {
        if (t[v].next[c] != -1)
            t[v].go[c] = t[v].next[c];
        else
            t[v].go[c] = (v == 0 ? 0 : go(failure_f(v), c));
    }
    return t[v].go[c];
}

int get_super(int v) {
    if (t[v].superlink == -1) {
        if (v == 0)
            t[v].superlink = 0;
        else if (t[v].leaf)
            t[v].superlink = v;
        else
            t[v].superlink = get_super(failure_f(v));
    }
    return t[v].superlink;
}