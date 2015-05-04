ll f[MAXN];

ll rsq(int rx) {
	ll ans = 0;
	for (int a = rx; a > 0; a -= a & -a)
		ans += f[a];
	return ans;
}

void add(int rx, ll k) {
	for (int a = rx; a < MAXN; a += a & -a)
		f[a] += k;
}
