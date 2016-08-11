//Bron–Kerbosch algorithm with pivoting

const int MAXN = 50;

int n;
int g[MAXN][MAXN]; //matrix of adjacency; g[i][i] = 1
ll gmask[MAXN], FULL;

int getRank(ll p, int u) {
	return __builtin_popcountll(p & (FULL ^ gmask[u]));	
}

int findMax(ll r, ll p, ll x) {
    if (p == 0 && x == 0)
    	return __builtin_popcountll(r);
	
    ll unite = p | x;
	int u = -1;
	for (int i = 0; i < n; i++)
		if ((unite >> i) & 1) {
			if (u == -1 || getRank(p, u) > getRank(p, i))
				u = i;	
		}
    
	int ans = 0;
	ll curSet = p & (FULL ^ gmask[u]);
	for (int v = 0; v < n; v++)
		if ((curSet >> v) & 1) {
			ans = max(ans, findMax(r | (1ll << v), p & gmask[v], x & gmask[v]));
			
			p ^= (1ll << v);
			x |= (1ll << v);
		}
	
	return ans;
}

//...

FULL = (1ll << n) - 1;

for (int i = 0; i < n; i++) {
	gmask[i] = 0;
	for (int j = 0; j < n; j++)
		gmask[i] |= (ll)(g[i][j]) << j;
}

int ans = findMax(0, FULL, 0);