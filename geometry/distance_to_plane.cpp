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