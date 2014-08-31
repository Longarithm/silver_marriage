struct segment_tree {
    int value, number;
    bool colour;
};

segment_tree t[MAXK * 2 + 1];

void tree_build(vector<int> a) {
	int sz = a.size();
	for (int i = 0; i < sz; i++) {
        t[MAXK + i].value = a[i];
        t[MAXK + i].colour = 0;
    }
    for (int i = sz; i <= MAXK; i++) {
        t[MAXK + i].value = INF;
        t[MAXK + i].colour = 0;
    }
    for (int i = MAXK - 1; i >= 1; i--) {
        t[i].value = min(t[i * 2].value, t[i * 2 + 1].value);
        t[i].colour = 0;
    }
}

void push(int v, int l, int r) {
    if (t[v].colour) {
        if (v < MAXK) {
            t[2 * v].colour = t[2 * v + 1].colour = 1;
			t[2 * v].number += t[v].number;
			t[2 * v + 1].number += t[v].number;
			t[2 * v].value += t[v].number;
			t[2 * v + 1].value += t[v].number;
        }
        t[v].colour = 0;
		t[v].number = 0;
    }
}

void update(int v, int l, int r, int a, int b, int x) {
    push(v, l, r);
    if ((r < a) || (b < l))
        return;
    if ((a <= l) && (r <= b)) {
        t[v].colour = 1;
        t[v].number += x;
        t[v].value += x;
        return;
    }

    update(2 * v, l, (l + r) / 2, a, b, x);
    update(2 * v + 1, (l + r) / 2 + 1, r, a, b, x);
    t[v].value = min(t[2 * v].value, t[2 * v + 1].value);
}

int get(int v, int l, int r, int a, int b) {
    push(v, l, r);
    if ((r < a) || (b < l))
        return 0;
    if ((a <= l) && (r <= b))
        return t[v].value;
    return min(get(2 * v, l, (l + r) / 2, a, b), get(2 * v + 1, (l + r) / 2 + 1, r, a, b));
}
