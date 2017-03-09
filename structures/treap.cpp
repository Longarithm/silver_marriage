struct node {
	int key, pr, cnt;
	node *l, *r;
	node(int _key){
		key = _key;
		pr = rand();
		cnt = 1;
		l = r = NULL;
	}
};

int cnt(node *p) {
	return p ? p->cnt : 0;
}

void upd_cnt (node *&p) {
	if (p) {
		p->cnt = 1 + cnt(p->l) + cnt(p->r);
	}
}

void split(node *p, int key, node *&l, node *&r) {
	if (p == NULL) {
		l = r = NULL;
		return;
	}

	if (key <= p->key) {
		split(p->l, key, l, p->l);
		r = p;
	} else {
		split(p->r, key, p->r, r);
		l = p;
	}
	upd_cnt(p);
}

void merge(node *&p, node *l, node *r) {
	if (l == NULL)
		p = r;
	else if (r == NULL)
		p = l;
	else if (l->pr < r->pr) {
		p = l;
		merge(l->r, l->r, r);
	} else {
		p = r;
		merge(r->l, l, r->l);
	}
	upd_cnt(p);
}

void insert(node *&p, int key, int pr) {
	if (p == NULL) {
		p = new node(key);
		p->pr = pr;
		return;
	}
	if (pr > p->pr) {
		if (key > p->key)
			insert(p->r, key, pr);
		else
			insert(p->l, key, pr);
	} else {
		node *t = new node(key);
		t->pr = pr;
		split(p, key, t->l, t->r);
		p = t;
	}
	upd_cnt(p);
}

void erase(node *&p, int key) {
	if (p == NULL)
		return;
	if (p->key == key)
		merge (p, p->l, p->r);
	else {
		if (key < p->key)
			erase(p->l, key);
		else
			erase(p->r, key);
	}
	upd_cnt(p);
}

bool find(node *p, int key) {
	if (p == NULL)
		return 0;
	if (key < p->key)
		return find(p->l, key);
	else {
		if (key == p->key)
			return 1;
		else
			return find(p->r, key);
	}
}

node *t;