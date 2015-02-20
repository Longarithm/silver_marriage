int n, m, k, vw, cf, h, t, v, vm;
vi c, f, q;
vector<vector<pii> > w; //to, id
vector<pii> from;
pii pr;

<...>

	//example:
	w[a].push_back(make_pair(b, c.size())); 
	c.push_back(weight);
	f.push_back(0);
	w[b].push_back(make_pair(a, c.size())); 
	c.push_back(0);
	f.push_back(0);

	from.resize(k);
	q.resize(k);
	for (;;) {		
		forn(i, k) from[i].fi = from[i].se = -1; //what, id

		h = 0;
		t = 0;
		q[t++] = 0;
		from[0].fi = 0;
		for (int cur; h < t;) {
			cur = q[h++];
			forn(i, w[cur].size()) {
				v = w[cur][i].fi;
				vm = w[cur][i].se;
				if (from[v].fi == -1 && c[vm] - f[vm] > 0) {
					q[t++] = v;
					from[v].fi = cur;
					from[v].se = vm;
				}
			}
		}

		if (from[k - 1].fi == -1)
			break;
		cf = INF;
		for (int cur = k - 1; cur != 0;) {
			pr = from[cur];
			cf = min(cf, c[pr.se] - f[pr.se]);
			cur = pr.fi;
		}
		for (int cur = k - 1; cur != 0;) {
			pr = from[cur];
			f[pr.se] += cf;
			f[pr.se ^ 1] -= cf;
			cur = pr.fi;
		}
	}

	int flow = 0;
	forn(i, w[0].size())
		if (c[w[0][i].se])
			flow += f[w[0][i].se];