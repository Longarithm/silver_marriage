int a, b, c, g, k, x, y;

int gcd(int a, int b, int &x, int &y) {
	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}
	int x1, y1;
	int d = gcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

<...>

	cin >> a >> b >> c;
	g = gcd(a, b, x, y);
	if (c % g != 0)
		cout << "Impossible" << endl;
	else {
		a /= g;
		b /= g;
		c /= g;
		x *= c;
		y *= c;

		//here we get minimal x >= 0
		k = -x / b;
		if (x + k * b < 0)
			k++;
		x += k * b;
		y -= k * a;

		cout << x << ' ' << y << endl;
	}