bool intersect_p(ld a, ld b, ld c, ld d) {
	return max(a, b) >= min(c, d) && max(c, d) >= min(a, b);
}

line segmentToLine(pt p1, pt p2) {
	ld a = p1.y - p2.y, b = p2.x - p1.x;
	return line(a, b, -(a * p1.x + b * p1.y));
}

bool intersect(pt a, pt b, pt c, pt d) {
	ld v1 = (b - a) % (c - a); //sin(ab, ac)
	ld v2 = (b - a) % (d - a); //sin(ab, ad)
	ld v3 = (d - c) % (a - c); //sin(cd, ca)
	ld v4 = (d - c) % (b - c); //sin(cd, cb)
	if (eq(v1, 0) && eq(v2, 0) && eq(v3, 0) && eq(v4, 0)) //in the same line?
		return intersect_p(a.x, b.x, c.x, d.x) && intersect_p(a.y, b.y, c.y, d.y); //proections
	else
		return (v1 * v2 <= 0) && (v3 * v4 <= 0);
}

bool parallel(line m, line n) {
	return eq(m.a * n.b - m.b * n.a, 0);
}

bool equivalent(line m, line n) {
	return parallel(m, n) && eq(m.a * n.c - m.c * n.a, 0) && eq(m.b * n.c - m.c * n.b, 0);
}

int linesIntersection(line m, line n, pt &res) {
	if (parallel(m, n)) {
		if (equivalent(m, n))
			return 2;
		else
			return 0;
	}		
	ld sign = m.a * n.b - m.b * n.a;
	res.x = (m.b * n.c - m.c * n.b) / sign;
	res.y = (m.c * n.a - m.a * n.c) / sign;
	return 1;
}

int segmentsIntersection(pt a, pt b, pt c, pt d, pt &p1, pt &p2) {
	if (!intersect(a, b, c, d))
		return 0;
	line l1 = segmentToLine(a, b), l2 = segmentToLine(c, d);
	if (!equivalent(l1, l2)) {
		linesIntersection(l1, l2, p1);
		return 1;
	}
	vector<pt> p;
	p.push_back(a);
	p.push_back(b);
	p.push_back(c);
	p.push_back(d);
	sort(p.begin(), p.end());
	p1 = p[1], p2 = p[2];
	if (eq(p1, p2))
		return 1;
	return 2;
}

int arrowsIntersection(pt a, pt b, pt c, pt d, pt &res) {
	line l1 = segmentToLine(a, b), l2 = segmentToLine(c, d);
	switch(linesIntersection(l1, l2, res)) {
		case 1: {
			if (((b - a) * (res - a)) >= -eps && ((d - c) * (res - c)) >= -eps)
				return 1;
			break;
		}
		case 2: {
			if (((b - a) * (d - c)) >= -eps || ((b - a) * (c - a)) >= -eps)
				return 2;
			break;
		}
	}
	return 0;
}