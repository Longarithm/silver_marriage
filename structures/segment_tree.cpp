const int MAXN = (int)100500;
const int MAXK = (int)131072;

int n, a[MAXN], t[MAXK * 2 + 3];

//!!!
//tree: numeration from 1
//array: numeration from 0

void tree_build() {
    memset(t, 0, sizeof(t));
    for (int i = 0; i < n; i++)
        t[MAXK + i] = a[i];
    
    for (int v = MAXK - 1; v >= 1; v--) {
        if (t[2 * v] > t[2 * v + 1]) {
            t[v] = t[2 * v];
        } else {
            t[v] = t[2 * v + 1];
        }
    }
}

void update(int i, int value) {
    int v = MAXK + i;
    t[v] = value;
    while (v > 1) {
        v /= 2;
        if (t[2 * v] > t[2 * v + 1]) {
            t[v] = t[2 * v];
        } else {
            t[v] = t[2 * v + 1];
        }
    }
}

int get(int v, int l, int r, int lx, int rx) { //[lx, rx)
    if ((r <= lx) || (rx <= l))
        return 0;
    if ((lx <= l) && (r <= rx))
        return t[v];

    int t1 = get(2 * v, l, (l + r) >> 1, lx, rx);
    int t2 = get(2 * v + 1, (l + r) >> 1, r, lx, rx);
    if (t1 > t2)
        return t1;
    return t2;
}

int get(int l, int r) { //[l, r]
    return get(1, 1, MAXK + 1, l + 1, r + 2);
}
