ll mul(ll a, ll b, ll MOD) {
	a %= MOD;
	b %= MOD;
	
	ll res = 0;
	while (b > 0) {
		if (b & 1) {
			res += a;
			if (res >= MOD)
				res -= MOD;
		}
		
		a += a;
		if (a >= MOD)
			a -= MOD;
			
		b >>= 1;
	}	
	return res;
}

ll pollard(ll n, int add) {
	if (n == 2)
		return 0;
		
	ll x = rand() % n;
	if (x == 0)
		x++;
	ll y = 1, d = x - y;
	ll g = __gcd(n, d);
	
	for (int i = 0, step = 2; i < MAXI && (g == 1 || g == n); i++) {
		if (i == step) {
			y = x;	
			step *= 2;
		}
		x = (mul(x, x, n) + add) % n;
		
		//cerr << x << endl;
		
		if (x > y)
			d = x - y;
		else
			d = y - x;
		g = __gcd(n, d);
	}
	
	if (g != 1 && g != n)
		return g;
	return 0;	
}

...

	ll n;
	cin >> n;
	ll d = max(pollard(n, 1), pollard(n, n - 1));
	if (d == 0)
		cout << "IMPOSSIBLE";
	else
		cout << d << ' ' << n / d;