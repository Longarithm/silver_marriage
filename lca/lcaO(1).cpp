#include <bits/stdc++.h>
// Should be a direct tree G.!!!
// 10^7 querry 1,5 sec.
using namespace std;

const int MAXN = (int)2e5;
const int MAXMASK = 1 << 18;

vector<int> g[MAXN];
int LBIT[MAXMASK], RBIT[MAXMASK];
int preorder[MAXN], I[MAXN], lead[MAXN], A[MAXN], par[MAXN], timer;

void dfs1(int v, int p) {
    par[v] = p;
    I[v] = preorder[v] = ++timer;
    for(int to : g[v]) {
        dfs1(to, v);
        if(RBIT[I[to]] > RBIT[I[v]])
            I[v] = I[to];
    }
    lead[I[v]] = v;
}

void dfs2(int v, int up) {
    A[v] = up | RBIT[I[v]];
    for(int to : g[v])
        dfs2(to, A[v]);
}

void precalc(int root) {
    for(int i = 1; i < MAXMASK; i <<= 1)
        fill(LBIT + i, LBIT + i + i, i);
    for(int i = 1; i < MAXMASK; RBIT[i] = i, i <<= 1)
        copy(RBIT + 1, RBIT + i, RBIT + i + 1);
    dfs1(root, -1);
    dfs2(root, 0);
}

inline int enter_into_strip(int x, int hz) {
    if(RBIT[I[x]] == hz)
        return x;
    int hw = LBIT[A[x] & (hz - 1)];
    return par[lead[I[x] & (~hw + 1) | hw]];
}

inline int lca(int x, int y) {
    int hb = I[x] == I[y] ? RBIT[I[x]] : LBIT[I[x] ^ I[y]];
    int hz = RBIT[A[x] & A[y] & (~hb + 1)];
    int ex = enter_into_strip(x, hz);
    int ey = enter_into_strip(y, hz);
    return preorder[ex] < preorder[ey] ? ex : ey;
}

int a[100000000 + 5];

int main()
{

	int n = 0;
	int m = 0;
	scanf("%d %d", &n, &m);
	for (int i = 1; i < n; i++)
	{
		int x;
		scanf("%d", &x);
		g[x].push_back(i);
	}
	int xx, yy;
	scanf("%d %d", &a[1], &a[2]);
	int aa, bb, cc;
	scanf("%d %d %d", &aa, &bb, &cc);

	aa %= n;
	bb %= n;
	cc %= n;

	for (int i = 3; i <= m + m; i++)
		a[i] = (aa * 1ll * a[i - 2] + bb * 1ll * a[i - 1] + cc) % n;

	precalc(0);
	long long ans = 0;
	xx = a[1];
	yy = a[2];
	for (int i = 1; i <= m; i++)
	{
		int lc = lca(xx, yy);
		ans += (long long)lc;
		if (i == m)
			break;
		xx = (a[i + i + 1] + lc) % n;
		yy = a[i + i + 2];
	}	
	cout << ans << endl;
	return 0;
}