const int MAXK = 131072;

struct vertex {
	vertex *l, *r;
	int x;

	vertex(vertex *L = NULL, vertex *R = NULL, int _x = 0) {
		l = L;
		r = R;
		x = _x;
	}
};

vertex *build(int L, int R) {
	if (L + 1 == R) {
		return new vertex(NULL, NULL, 0);
	}
	
	int M = (L + R) >> 1;
	return new vertex(build(L, M), build(M, R));
}

vertex *update(vertex *v, int L, int R, int pos, int val) {
	if (L + 1 == R) {
		return new vertex(NULL, NULL, val);
	}
	
	int M = (L + R) >> 1;
	vertex *nv = new vertex();	

	if (pos < M) {
		nv->l = update(v->l, L, M, pos, val);
		nv->r = v->r;
	} else {
		nv->l = v->l;
		nv->r = update(v->r, M, R, pos, val);
	}
	
	return nv;
}

int get(vertex *v, int L, int R, int pos) {
	if (L + 1 == R)
		return v->x;

	int M = (L + R) >> 1;
	if (pos < M)
		return get(v->l, L, M, pos);
	return get(v->r, M, R, pos);	
}

vertex *update(vertex *v, int pos, int val) {
	return update(v, 1, MAXK + 1, pos + 1, val);	
}

int get(vertex *v, int pos) {
	return get(v, 1, MAXK + 1, pos + 1);	
}      

vertex* root[MAXK];

//...

root[0] = build(1, MAXK + 1);