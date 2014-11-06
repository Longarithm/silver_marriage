struct node {
	node *l, *r;
	int key, pr, cnt;
	node(int _key) {
		l = r = NULL;
		key = _key;
		pr = rand();
		cnt = 1;
	}
};

int cnt(node *v) {
	return (v ? v->cnt : 0);
}

inline void upd_cnt(node *&v) {
	if (v) {
		v->cnt = cnt(v->l) + 1 + cnt(v->r);
	}
}

void split(node *v, int key, node *&l, node *&r) {
	if (!v) {
		l = r = NULL;
		return;
	}

	int cur_key = cnt(v->l);
	if (key <= cur_key) {
		split(v->l, key, l, v->l);
		r = v;
	} else {
		split(v->r, key - cnt(v->l) - 1, v->r, r);
		l = v; 
	}
	upd_cnt(v);
} 

void merge(node *&v, node *l, node *r) {
	if (!l)
		v = r;
	else if (!r)
		v = l;
	else if (l->pr < r->pr) {
		v = l;
		merge(v->r, v->r, r);
	} else {
		v = r;
		merge(v->l, l, v->l);
	}
	upd_cnt(v);
}

void print(node *v) {
	if (!v)
		return;

	print(v->l);
	printf("%d ", v->key);
	print(v->r);
}

void insert(node *&p, int value, int pr, int key) {
	node *p1, *p2;
	split(p, key, p1, p2);
	node *item = new node(value);
	merge(p, p1, item);
	merge(p, p, p2);
}

void erase(node *&p, int key) {
	if (p == NULL)
		return;
			
	int cur_key = cnt(p->l);
	if (cur_key == key)
		merge(p, p->l, p->r);
	else {
		if (key < cur_key)
			erase(p->l, key);
		else
			erase(p->r, key - cnt(p->l) - 1);
	}
	upd_cnt(p);
}

int find(node *p, int key) {
	if (p == NULL)
		return -1;
	int cur_key = cnt(p->l);
	if (key == cur_key)
		return p->key;
	else {
		if (key < cur_key)
			return find(p->l, key);
		else
			return find(p->r, key - cnt(p->l) - 1);
	}
}

node *t;