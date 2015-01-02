ld polygonArea(vector<pt> a) {
	ld ans = 0;
	for (unsigned int i = 1; i < a.size(); i++)
		ans += (a[i - 1] % a[i]);
	ans += (a.back() % a[0]);
	return fabs(ans) / 2;
}

//convex hull

pt o;
bool cmp(pt a, pt b) {
	ll x = (a - o) % (b - o);
	if (fabs(x) >= eps)
		return x > 0;
	return len(a - o) < len(b - o);
}

vector<pt> convex(vector<pt> a) {
	int n = a.size();
    
	sort(all(a));
	n = unique(all(a)) - a.begin();
	a.resize(n);
    
    o = a[0];
	sort(a.begin() + 1, a.end(), cmp); 
	
	vector<pt> res;
	res.pb(a[0]);
	for (int i = 1; i < n; i++) {
		while (res.size() > 1 && (res.back() - res[res.size() - 2]) % (a[i] - res.back()) <= 0)
			res.pop_back();
		res.pb(a[i]);	
	}
		
	return res;
}

//distance from point to plane
ld distToPlane(pt p0, pt p1, pt p2, pt p3) {
	ld A, B, C, D = 0;
	A = (p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y);
	D -= p1.x * A;
	B = -(p2.x - p1.x) * (p3.z - p1.z) + (p2.z - p1.z) * (p3.x - p1.x);
	D -= p1.y * B;
	C = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
	D -= p1.z * C;
	
	return fabs(A * p0.x + B * p0.y + C * p0.z + D) / sqrt(sqr(A) + sqr(B) + sqr(C));	
}

//build circle by three points
pt circleByPoints(pt a, pt b, pt c) {
	pt a1 = (a + b) * 0.5;
	pt a2 = (a + c) * 0.5;
	pt v1 = b - a;
	v1 = pt(-v1.y, v1.x);
	pt v2 = c - a;
	v2 = pt(-v2.y, v2.x);
	
	if (fabs(v1.x * v2.y - v1.y * v2.x) < eps)
		return pt(-1, -1);
		
	ld t = (a2.x * v2.y - a2.y * v2.x - a1.x * v2.y + a1.y * v2.x) / (v1.x * v2.y - v1.y * v2.x);
	pt res = a1 + v1 * t;
	
	return res;
}