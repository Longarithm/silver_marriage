bool eq(ld a, ld b) {
	return (fabs(a - b) < eps);
}

struct pt {
	ld x, y;
	pt(): x(0), y(0) {}
	pt(ld _x, ld _y) {
		x = _x, y = _y;
	}
	
	void read() {
		cin >> x >> y;
	}
	
	void print() {
		cout << x << ' ' << y << endl;	
	}
	
	friend bool eq(pt a, pt b) {
		return eq(a.x, b.x) && eq(a.y, b.y);
	}
	
	friend bool operator==(pt a, pt b) {
		return a.x == b.x && a.y == b.y;
	}
	
	friend bool operator<(pt a, pt b) {
		return (a.x < b.x) || (eq(a.x, b.x) && (a.y < b.y));
	}
	
	friend pt operator-(pt p1, pt p2) {
		return pt(p1.x - p2.x, p1.y - p2.y);
	}

	friend pt operator+(pt p1, pt p2) {
		return pt(p1.x + p2.x, p1.y + p2.y);
	}

	friend pt operator*(pt a, ld b) {
		return pt(a.x * b, a.y * b);
	}

	friend pt operator/(pt a, ld b) {
		return pt(a.x / b, a.y / b);
	}

	ld len() {
		return sqrt(.0 + x * x + y * y);
	}
	
	ld dist(pt p) {
		return (*this - p).len();
	}

	pt norm() {
		pt v = *this;
		ld L = v.len();
		assert(L >= eps);
		v.x /= L;
		v.y /= L;
		return v;
	}
	
	friend ld operator*(pt p1, pt p2) {
		return p1.x * p2.x + p1.y * p2.y;
	}

	friend ld operator%(pt p1, pt p2) {
		return p1.x * p2.y - p2.x * p1.y;
	}

	friend ld angle(pt p1, pt p2) {
		return abs(atan2(p1 % p2, p1 * p2));
	}

	ld polarAngle() {
		ld res = atan2(y, x);
		return (res < 0) ? res + 2 * pi : res;
	}

	pt rotate(ld w) {
		return pt(x * cos(w) - y * sin(w), x * sin(w) + y * cos(w));
	}   
	
	friend bool cw(pt a, pt b, pt c) {
		return ((c - a) % (b - a)) > 0;
	}

	friend bool ccw(pt a, pt b, pt c) {
		return ((c - a) % (b - a)) < 0;
	}
};

struct line {
	ld A, B, C;
	line(): A(0), B(0), C(0) {}
	line(ld _A, ld _B, ld _C) {
		A = _A, B = _B, C = _C;
	}
	
	bool lay(pt p) {
		return eq(A * p.x + B * p.y + C, 0);	
	}
	
	line(pt p1, pt p2) {
		A = p1.y - p2.y;
		B = p2.x - p1.x;
		C = -(A * p1.x + B * p1.y);	
		assert(lay(p1));
		assert(lay(p2));
	}
	
	bool parallel(line n) {
		return eq(A * n.B - B * n.A, 0);
	}
	
	bool equivalent(line n) {
		return parallel(n) && eq(A * n.C - C * n.A, 0) && eq(B * n.C - C * n.B, 0);
	}
};

ld polygonArea(vector<pt> a) {
	ld ans = 0;
	for (int i = 1; i < (int)a.size(); i++)
		ans += (a[i - 1] % a[i]);
	ans += (a.back() % a[0]);
	return fabs(ans) / 2;
}