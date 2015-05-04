const int MAXN = (int)100500;
const int MAXK = (int)131072;

struct vertex {
    int val, upd;
    bool flag;
    
    vertex() {val = upd = flag = 0;}
};

int n, a[MAXN];
vertex t[MAXK * 2 + 3];

//!!!
//tree: numeration from 1
//array: numeration from 0

void tree_build() {
    memset(t, 0, sizeof(t));
    for (int i = 0; i < n; i++) {
        t[MAXK + i].val = a[i];
        t[MAXK + i].flag = 0;
    }
    for (int i = n; i <= MAXK; i++) {
        t[MAXK + i].val = 0;
        t[MAXK + i].flag = 0;
    }
    
    for (int v = MAXK - 1; v >= 1; v--) {
        if (t[2 * v].val > t[2 * v + 1].val) {
            t[v].val = t[2 * v].val;
        } else {
            t[v].val = t[2 * v + 1].val;
        }
    }
}   

void push(int v, int l, int r) {
    if (t[v].flag) {
        if (v < MAXK) {
            t[2 * v].flag = t[2 * v + 1].flag = 1;
            t[2 * v].upd += t[v].upd;
            t[2 * v + 1].upd += t[v].upd;
            t[2 * v].val += t[v].upd;
            t[2 * v + 1].val += t[v].upd;
        }
        t[v].upd = 0;
        t[v].flag = 0;
    }
}

void update(int v, int l, int r, int lx, int rx, int x) { //[lx, rx)
    push(v, l, r);
    if ((r <= lx) || (rx <= l))
        return;
    if ((lx <= l) && (r <= rx)) {
        t[v].flag = 1;
        t[v].upd += x;
        t[v].val += x;
        return;
    }
    
    update(2 * v, l, (l + r) >> 1, lx, rx, x);
    update(2 * v + 1, (l + r) >> 1, r, lx, rx, x);
    if (t[2 * v].val > t[2 * v + 1].val)
        t[v].val = t[2 * v].val;
    else
        t[v].val = t[2 * v + 1].val;
}

int get(int v, int l, int r, int lx, int rx) { //[lx, rx)
    push(v, l, r);
    if ((r <= lx) || (rx <= l))
        return 0;
    if ((lx <= l) && (r <= rx))
        return t[v].val;

    int t1 = get(2 * v, l, (l + r) >> 1, lx, rx);
    int t2 = get(2 * v + 1, (l + r) >> 1, r, lx, rx);
    if (t1 > t2)
        return t1;
    return t2;
}

void update(int l, int r, int x) { //[l, r]
    return update(1, 1, MAXK + 1, l + 1, r + 2, x);
}

int get(int l, int r) { //[l, r]
    return get(1, 1, MAXK + 1, l + 1, r + 2);
}