bool pointInRay(pt a, pt b, pt c) {
	return line(b, c).lay(a) && ((c - b) * (a - b)) >= 0;
}

bool pointInSegment(pt a, pt b, pt c) {
	pt bc = c - b, ba = a - b;
	pt cb = b - c, ca = a - c;
	return eq(bc % ba, 0) && (bc * ba >= 0) && (cb * ca >= 0);
}

bool intersectB(ld a, ld b, ld c, ld d) {
	return max(a, b) >= min(c, d) - eps && max(c, d) >= min(a, b) - eps;
}

int sign(ld x) {
	if (x >= eps)
		return 1;
	if (x <= -eps)
		return -1;
	return 0;	
}

bool segmentsIntersection(pt a, pt b, pt c, pt d) {
	ld v[4];
	int signV[4];
		
	v[0] = (b - a) % (c - a); //sin(ab, ac)
	v[1] = (b - a) % (d - a); //sin(ab, ad)
	v[2] = (d - c) % (a - c); //sin(cd, ca)
	v[3] = (d - c) % (b - c); //sin(cd, cb)
	
	int zeroes = 0;
	for (int i = 0; i < 4; i++) {
		signV[i] = sign(v[i]);
		zeroes += (signV[i] == 0);
	}
		
	if (zeroes == 4) { //same line?
		return intersectB(a.x, b.x, c.x, d.x) && intersectB(a.y, b.y, c.y, d.y); //projections
	} 
	return (signV[0] * signV[1] != 1) && (signV[2] * signV[3] != 1);	
}

int linesIntersection(line m, line n, pt &res) {
	if (m.parallel(n)) {
		if (m.equivalent(n))
			return 2;
		else
			return 0;
	}		
	ld sign = m.A * n.B - m.B * n.A;
	res.x = (m.B * n.C - m.C * n.B) / sign;
	res.y = (m.C * n.A - m.A * n.C) / sign;
	return 1;
}

int segmentsIntersection(pt a, pt b, pt c, pt d, pt &p1, pt &p2) {
	if (!segmentsIntersection(a, b, c, d))
		return 0;
	line l1(a, b), l2(c, d);
	if (!l1.equivalent(l2)) {
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
	line l1(a, b), l2(c, d);
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