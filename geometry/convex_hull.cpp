pt o;
bool cmp(pt a, pt b) {
	ll x = (a - o) % (b - o);
	if (x != 0)
		return x > 0;
	return len(a - o) < len(b - o);
}

vector<pt> convexHull(vector<pt> a) {
	int n = a.size();
    
	for (int i = 1; i < n; i++)
		if (a[i] < a[0])
			swap(a[0], a[i]);
	
    o = a[0];
	sort(a.begin() + 1, a.end(), cmp); 
	n = unique(a.begin(), a.end()) - a.begin();
	a.resize(n);
	
	vector<pt> res;
	res.pb(a[0]);
	for (int i = 1; i < n; i++) {
		while (res.size() > 1 && (res.back() - res[res.size() - 2]) % (a[i] - res.back()) <= 0)
			res.pop_back();
		res.pb(a[i]);	
	}
		
	return res;
}
