const int P = 12;
const ll a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

inline ll binmul(ll x, ll y, ll mod) {
	if (mod <= 1E9)
		return (x * y) % mod;

	ll res = 0;
	while (y > 0) {
		if (y & 1) {
			res += x;
			if (res >= mod)
				res -= mod;
		}
		y >>= 1;

		x += x;
		if (x >= mod)
			x -= mod;
	}
	return res;
}

inline bool miller_rabin(ll n) {
	for (int i = 0; i < P; i++)
		if (n == a[i])
			return 1;
	if (n == 1 || (n & 1) == 0)
		return 0;

	ll t, t1, temp, s, st;
	int k, prime;

	t = n - 1;
	s = 0;
	while ((t & 1) == 0) {
		t >>= 1;
		s++;
	}

	for (int j = 0; j < P; j++) {
		prime = 0;
		temp = 1;

		st = a[j] % n;
		t1 = t;

		while (t1 > 0) {
			if (t1 & 1)
				temp = binmul(temp, st, n);
			st = binmul(st, st, n);
			t1 >>= 1;
		}

		if ((n + temp - 1) % n == 0)
			prime = 1;

		k = 1;

		while ((temp != 1) && (k <= s) && !prime) {
			if ((temp + 1) % n == 0)
				prime = 1;
			k++;
			temp = binmul(temp, temp, n);
		}

		if (!prime)
			return 0;
	}

	return 1;
}