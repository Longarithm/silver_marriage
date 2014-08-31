const int MAXN = (int)100000;
const int MAXK = (int)131072;

int n, a[MAXN], t[MAXK * 2 + 1];

void tree_build() {
    for (int i = 0; i < n; i++)
        t[MAXK + i] = a[i];
    for (int i = MAXK - 1; i >= 1; i--)
        t[i] = t[i * 2] + t[i * 2 + 1];
}

void update(int i, int value) {
    int v = MAXK + i - 1;
    t[v] = value;
    while (v > 1) {
        v /= 2;
        t[v] = t[2 * v] + t[2 * v + 1];
    }
}

int get(int v, int l, int r, int ll, int rr) {  //call with parametres (1, 1, MAXK, zL, zR)
    if ((r < ll) || (rr < l))
        return 0;
    if ((ll <= l) && (r <= rr))
        return t[v];
    return get(2 * v, l, (l + r) / 2, ll, rr) + get(2 * v + 1, (l + r) / 2 + 1, r, ll, rr);
}