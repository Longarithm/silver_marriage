//the most important code!
//other codes will not work without it

struct pt {
	ld x, y;
	pt(): x(0), y(0) {}
	pt(ld _x, ld _y) {
		x = _x, y = _y;
	}
};

struct line {
	ld a, b, c;
	line(): a(0), b(0), c(0) {}
	line(ld x, ld y, ld z) {
		a = x, b = y, c = z;
	}
};

bool eq(ld a, ld b) {
	return (fabs(a - b) < eps);
}

bool eq(pt a, pt b) {
	return eq(a.x, b.x) && eq(a.y, b.y);
}

pt read_pt() {
	ld a, b;
	cin >> a >> b;
	return pt(a, b);
}

bool operator==(pt a, pt b) {
	return a.x == b.x && a.y == b.y;
}

inline bool operator<(pt a, pt b) {
	return (a.x < b.x) || ((a.x == b.x) && (a.y < b.y));
}

pt operator-(pt p1, pt p2) {
	return pt(p1.x - p2.x, p1.y - p2.y);
}

pt operator+(pt p1, pt p2) {
	return pt(p1.x + p2.x, p1.y + p2.y);
}

pt operator*(pt a, ld b) {
	return pt(a.x * b, a.y * b);
}

pt operator/(pt a, ld b) {
	return pt(a.x / b, a.y / b);
}

ld len(pt a) {
	return sqrt(.0 + a.x * a.x + a.y * a.y);
}

ld dist(pt p1, pt p2) {
	return len(p1 - p2);
}

ld operator*(pt p1, pt p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

ld operator%(pt p1, pt p2) {
	return p1.x * p2.y - p2.x * p1.y;
}

ld corner(pt p1, pt p2) {
	return abs(atan2(p1 % p2, p1 * p2));
}

ld polar_corner(pt p1) {
	ld res = atan2(p1.y, p1.x);
	return (res < 0) ? res + 2 * pi : res;
}

pt rotate(pt a, ld w) {
	return pt(a.x * cos(w) - a.y * sin(w), a.x * sin(w) + a.y * cos(w));
}

bool cw(pt a, pt b, pt c) {
	return ((c - a) % (b - a)) > 0;
}

bool ccw(pt a, pt b, pt c) {
	return ((c - a) % (b - a)) < 0;
}

line segment2line(pt p1, pt p2) {
	ld a = p1.y - p2.y, b = p2.x - p1.x;
	return line(a, b, -(a * p1.x + b * p1.y));
}

bool pt_in_line(line l, pt c) {
	return eq(l.a * c.x + l.b * c.y + l.c, 0);
}

bool pt_in_arrow(pt a, pt b, pt c) {
	return pt_in_line(segment2line(a, b), c) && ((b - a) * (c - a)) >= 0;
}

bool pt_in_segment(pt a, pt b, pt c) {
	pt ab = b - a, ac = c - a;
	pt ba = a - b, bc = c - b;
	return eq(ab % ac, 0) && (ab * ac >= 0) && (bc * ba >= 0);
}

ld polygonArea(vector<pt> a) {
	ld ans = 0;
	for (int i = 1; i < (int)a.size(); i++)
		ans += (a[i - 1] % a[i]);
	ans += (a.back() % a[0]);
	return fabs(ans) / 2;
}