pt circleByPoints(pt a, pt b, pt c) { //certainly, returns centre of circle
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