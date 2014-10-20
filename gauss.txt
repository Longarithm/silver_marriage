vector<vector<long double> > a;
vi was, cid;

void gauss() {
	was.resize(n);
	cid.resize(n);
	forn(i, n)
		was[i] = 0;

	long double cf;
	forn(i, n) {
		cid[i] = -1;
		forn(j, n)
			if (!was[j] && fabs(a[j][i]) >= eps && (cid[i] == -1 || abs(a[j][i]) > abs(a[cid[i]][i])))
				cid[i] = j;

		if (cid[i] == -1)
			continue;
		was[cid[i]] = 1;

		cf = a[cid[i]][i];
		forn(j, n + 1)
			a[cid[i]][j] /= cf;
		forn(j, n) {
			if (j == cid[i] || fabs(a[j][i]) < eps)
				continue;

			cf = -a[j][i];
			forn(k, n + 1)
				a[j][k] += cf * a[cid[i]][k];
		}
	}

}
