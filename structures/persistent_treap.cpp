unsigned int rnd() {
	return (rand() << 15) + rand();
}

struct node {
	int val, cnt;
	node *L, *R;

	node (int _val = 0) {
		val = _val;
		cnt = 1;
		L = R = NULL;
	}
};

int cnt(node *v) {
	return v ? v->cnt : 0;	
}

void update(node *&v) {
	if (v) {
		v->cnt = cnt(v->L) + 1 + cnt(v->R);
	}
}

void print(node *v) {
	if (!v)
		return;

	print(v->L);
	cout <<	v->val << ' ';
	print(v->R);
}

node *copyNode(node *v) {
	if (!v)
		return NULL;

	node* w = new node(v->val);
	w->L = v->L;
	w->R = v->R;
	update(w);

	return w;	
}

void split(node *v, node *&L, node *&R, int key) {
	if (!v) {
		L = R = NULL;
		return;
	}
	
	if (cnt(v->L) < key) {
		L = copyNode(v);
		split(v->R, L->R, R, key - cnt(v->L) - 1);		
	} else {
		R = copyNode(v);
		split(v->L, L, R->L, key);		
	}
	
	update(L);
	update(R);
}

void merge(node *&v, node *L, node *R) {
	if (!L) {
		v = copyNode(R);
	} else if (!R) {
		v = copyNode(L);
	} else {
		int cL = cnt(L);
		int cR = cnt(R);
		int pr = (int)(rnd() % (cL + cR));
		
		if (pr < cL) {
			v = copyNode(L);
			v->L = L->L;
			merge(v->R, L->R, R);	
		} else {
			v = copyNode(R);
			v->R = R->R;
			merge(v->L, L, R->L);
		}
	}
	
	update(v);
}

node *t;
