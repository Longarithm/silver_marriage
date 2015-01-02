int n;
ll a[2 * MAXK + 2], b[2 * MAXK + 2];
vector<pair<ld, int> > seg[2 * MAXK + 2], seg2[2 * MAXK + 2];

pair<ld, pii> cmp(int id1, int id2) {
	if (a[id1] == a[id2]) {
		if (b[id1] < b[id2])
			return mp(-1E51, mp(id1, id2));
		return mp(-1E51, mp(id2, id1));				
	}
	
	ld a1 = a[id1], a2 = a[id2];
	ld b1 = b[id1], b2 = b[id2];
	ld t = (b2 - b1) / (a1 - a2);
	if (a[id1] < a[id2])
		return mp(t, mp(id1, id2));
	return mp(t, mp(id2, id1));
}

int cmpId(int id1, int id2, ld t) {
	ld r1 = t * a[id1] + b[id1];
	ld r2 = t * a[id2] + b[id2];
	if (r1 >= r2)
		return id1;
	return id2;
}	

void build(int v, int l, int r) {
	if (l == r) {
		seg[v].clear();
		if (l <= n) {
			seg[v].pb(mp(-1E50, l));
			seg[v].pb(mp(1E50, l));
		}
		return;
	}
	
	build(v * 2, l, ((l + r) >> 1));
	build(v * 2 + 1, ((l + r) >> 1) + 1, r);
	
	if (seg[v * 2 + 1].size() == 0) {
		seg[v] = seg[v * 2];
		return;
	}
	
	seg[v].clear();
	seg[v].resize(seg[v * 2].size() + seg[v * 2 + 1].size());
	merge(all(seg[v * 2]), all(seg[v * 2 + 1]), seg[v].begin());
	
	seg2[v].clear();
	int ptr1 = 0, ptr2 = 0;
	for (int i = 0; i < (int)seg[v].size(); i++) {
		seg2[v].pb(seg[v][i]);
		
		if (seg2[v].back().X == 1E50)
			break;
			
		while (seg[v * 2][ptr1].X <= seg2[v].back().X + eps)
			ptr1++;
		ptr1--;
		while (seg[v * 2 + 1][ptr2].X <= seg2[v].back().X + eps)
			ptr2++;
		ptr2--;
		
		pair<ld, pii> cmpres = cmp(seg[v * 2][ptr1].Y, seg[v * 2 + 1][ptr2].Y);
		if (cmpres.X <= seg[v][i].X)
			seg2[v].back().Y = cmpres.Y.Y;
		else if (cmpres.X >= seg[v][i + 1].X)
			seg2[v].back().Y = cmpres.Y.X;
		else {
			seg2[v].back().Y = cmpres.Y.X;
			seg2[v].pb(mp(cmpres.X, cmpres.Y.Y));
		}
	}
	
	seg[v].clear();
	seg[v].pb(seg2[v][0]);
	forab(i, 1, seg2[v].size())
		if (fabs(seg2[v][i].X - seg2[v][i - 1].X) >= eps)
			seg[v].pb(seg2[v][i]);
	seg2[v].clear();
}        

int getMaxId(int v, int l, int r, int lx, int rx, ld t) {
	if (rx < l || r < lx)
		return lx;
	if (lx <= l && r <= rx) {
		int i = lower_bound(all(seg[v]), mp(t, n + 1)) - seg[v].begin();
		while (seg[v][i].X > t + eps)
			i--;
		return seg[v][i].Y;
	}
	
	int id1 = getMaxId(v * 2, l, ((l + r) >> 1), lx, rx, t);
	int id2 = getMaxId(v * 2 + 1, ((l + r) >> 1) + 1, r, lx, rx, t);
	return cmpId(id1, id2, t);	
}