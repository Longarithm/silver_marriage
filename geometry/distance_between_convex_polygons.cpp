const int MAXI = 200; //iterations of binary and ternary searches
const int MAXN = 100500; //maximal number of points

//two polygons
int n[2];
pt a[2][MAXN];

//main code
pt f(int id, ld x) { //returns point on border of polygon
	int pos[2];
	pos[0] = int(x);
	pos[1] = (pos[0] + 1) % n[id];
	ld fr = x - pos[0];
	
	pt res = a[id][pos[0]] + (a[id][pos[1]] - a[id][pos[0]]) * fr;
	return res;
}

ld binsearch(pt P, ld x, bool is_up) {
	ld l, r, mid;
	
	l = 0;
	r = n[1];
	
	forn(it, MAXI) {
		mid = (l + r) / 2;
		if (is_up) {
			if (dist(P, f(1, mid)) > x)
				r = mid;
			else
				l = mid;
		} else {
			if (dist(P, f(1, mid)) > x)
				l = mid;
			else
				r = mid;
		}
	}
	return (l + r) / 2;
}

ld tsearch(pt P) {
	ld minVal = dist(P, f(1, 0)), ptex, l, r, mid[2];
	
	//f: /\/ ?
	bool grow = !(dist(P, f(1, eps * MAXN)) > minVal); 
	ptex = binsearch(P, minVal, grow);
	
	if (grow) {
		//[0..ptex)
		l = 0;
		r = ptex - eps;
		forn(it, MAXI) {
			mid[0] = l + (r - l) / 3;
			mid[1] = r - (r - l) / 3;
			if (dist(P, f(1, mid[0])) < dist(P, f(1, mid[1])))
				r = mid[1];
			else
				l = mid[0];
		}
		if (minVal > dist(P, f(1, (l + r) / 2))) {
			minVal = dist(P, f(1, (l + r) / 2));
		}
	} else {
		//[ptex..n)
		l = ptex;
		r = n[1] + 0.0 - eps;
		forn(it, MAXI) {
			mid[0] = l + (r - l) / 3;
			mid[1] = r - (r - l) / 3;
			if (dist(P, f(1, mid[0])) < dist(P, f(1, mid[1])))
				r = mid[1];
			else
				l = mid[0];
		}
		if (minVal > dist(P, f(1, (l + r) / 2))) {
			minVal = dist(P, f(1, (l + r) / 2));
		}
	}
	
	return minVal;
}

//<...>
//int main() {
//<...>

	ld answer, curAns;
	answer = 1E100;
	forn(i, 2) {
		forn(j, n[0]) {
			curAns = tsearch(a[0][j]);
			if (curAns < answer) {
				answer = curAns;
			}
		}
		
		forn(j, max(n[0], n[1]))
			swap(a[0][j], a[1][j]);
		swap(n[0], n[1]);
	}