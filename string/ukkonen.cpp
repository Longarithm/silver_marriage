const int MAXN = 100000;
const int ALPH = 26;

struct node {
	int L, len, link;
	int go[ALPH];	
	
	node(int _L = 0, int _len = 0) {
		L = _L;
		len = _len;
		link = 0;
		memset(go, 0, sizeof(go));	
	}
};

int sz;
node a[MAXN];
int n;
char s[MAXN];
int curV, curPos; //current position in suffix tree
 
int addNode(int L, int len) {
	a[sz] = node(L, len);
	return sz++;
}

void goDown() {
	while (curPos > a[a[curV].go[s[n - curPos] - 'a']].len) {
		curV = a[curV].go[s[n - curPos] - 'a'];
		curPos -= a[curV].len;		
	}
}

void extend(char c) {
	s[n++] = c;	
	curPos++;
	
	int last = 0;
	while (curPos > 0) {
		goDown();

		int edge = s[n - curPos] - 'a';
		int &v = a[curV].go[edge];
		char d = s[a[v].L + curPos - 1];

		if (v == 0) {
			v = addNode(n - curPos, INF);
			a[last].link = curV;    
			last = 0;
		} else if (c == d) {
			a[last].link = curV; 
			return;
		} else {
			int u = addNode(a[v].L, curPos - 1);
			a[u].go[c - 'a'] = addNode(n - 1, INF);
			a[u].go[d - 'a'] = v;
			
			a[v].L += curPos - 1;
			if (a[v].len != INF)
				a[v].len -= curPos - 1;
			
			v = u;
			
			a[last].link = u;
			last = u;
		}
		
		if (curV == 0)
			curPos--;
		else
			curV = a[curV].link;
	}
}

void addString(string t) {
	for (int i = 0; i < (int)t.size(); i++)
		extend(t[i]);	
}

bool findString(string t) {
	int v = 0, up = 0;
	
	for (int i = 0; i < (int)t.size(); i++) {
		if (up == 0) {
			if (a[v].go[t[i] - 'a'] == 0)
				return 0;
			v = a[v].go[t[i] - 'a'];
			up = a[v].len - 1;
		} else {
			if (s[a[v].L + a[v].len - up] != t[i])
				return 0;

			up--;
		}
	}
	
	return 1;
}

void initSuffixTree() {
	sz = 1;	
	a[0] = node(0, INF);
	n = 0;
	
	curV = curPos = 0;
}

int main() {
	
	initSuffixTree();
	
	return 0;
