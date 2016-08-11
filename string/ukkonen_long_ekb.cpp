const int MAXN = 200500;
const int ALPH = 26;

struct pos {
	int v, up;

	pos(int _v = 0, int _up = 0): v(_v), up(_up) {};	
};

struct node {
	int par, l, r;
	int link;
	int go[ALPH];
	
	node(int _par = 0, int _l = 0, int _r = 0, int _link = -1):  par(_par), l(_l), r(_r), link(_link) {
		memset(go, -1, sizeof(go));	
	};	
};

string s;
int sz = 0, root;
pos p;
node a[MAXN];

int right(int v) {
	return (a[v].r == INF ? (int)s.size() : a[v].r);	
}

int length(int v) {
	return right(v) - a[v].l;	
}

pos go(pos p, char c) {
	assert(p.v != -1);
		
	int v = p.v, up = p.up;
	if (up != 0) {
		int i = right(v) - up;
		if (s[i] == c)
			return pos(v, up - 1);
			
		return pos(-1, -1);		
	} else {
		if (a[v].go[c - 'a'] != -1) {
			int to = a[v].go[c - 'a'];
			return pos(to, length(to) - 1);
		}
		
		return pos(-1, -1);
	}
}

int addChild(int v, int l, int r) {
	a[sz] = node(v, l, r);
	a[v].go[s[l] - 'a']	= sz;
	return sz++;
}

int split(pos p) {
	int v = p.v, up = p.up, down = length(v) - up;
	if (up == 0)
		return v;
	if (down == 0)
		return a[v].par;

	int mid = addChild(a[v].par, a[v].l, a[v].l + down);
	a[v].l += down;
	a[v].par = mid;
	a[mid].go[s[a[v].l] - 'a'] = v;
	return mid;	
}

pos fastGo(int v, int l, int r) {
	while (true) {
		if (l == r)
			return pos(v, 0);
		int to = a[v].go[s[l] - 'a'];
		if (l + length(to) > r)
			return pos(to, length(to) - r + l);
			
		v = to;
		l += length(to);
	}
}

int getLink(int v) {
	if (a[v].link == -1) {
		int par = a[v].par;
		a[v].link = split(fastGo(getLink(par), a[v].l + (par == 0 ? 1 : 0), right(v)));
	}
	return a[v].link;
}

pos extend(pos p, int i) {
	while (true) {
		pos to = go(p, s[i]);
		if (to.v != -1)
			return to;
			
		int v = split(p);
		addChild(v, i, INF);
		p = pos(getLink(v), 0);
		
		if (v == 0)
			return p;
	}
}

void addString(string t) {
	int L = s.size();
	s += t;
	int R = s.size();
	
	if (a[p.v].r == INF)
		p.up += R - L;
		
	for (int i = L; i < R; i++) {
		p = extend(p, i);	
	}			
}

void initSuffixTree() {
	root = 0;
	sz = 1;
	a[root].link = 0;
	p = pos(0, 0);	
}

int main() {
	
	initSuffixTree();
	
	return 0;
}