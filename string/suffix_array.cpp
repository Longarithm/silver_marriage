//SUFFIX ARRAY

string s;
int n, curLen, classes;
int cnt[MAXN], start[MAXN], p[MAXN], c[MAXN], oldP[MAXN], oldC[MAXN];

int pos[MAXN], lcp[MAXN], curLCP;

<...>

	cin >> s;
	n = s.size();
	
	for (int i = 0; i < n; i++)
		cnt[(int)s[i]]++;
	
	start[0] = 0;
	for (int i = 1; i < MAXN; i++)
		start[i] = start[i - 1] + cnt[i - 1];
	
	for (int i = 0; i < n; i++) 
		p[start[(int)s[i]]++] = i;

	c[p[0]] = 0;
	classes = 1;
	for (int i = 1; i < n; i++) {
		if (s[p[i - 1]] != s[p[i]])
			classes++;
		c[p[i]] = classes - 1;	
	}

	curLen = 1;
	while (curLen < n) {
	    swap(p, oldP);
		for (int i = 0; i < n; i++)
		   	oldP[i] = (oldP[i] - curLen + 2 * n) % n;
	    forn(i, classes)
	    	cnt[i] = 0;
	    for (int i = 0; i < n; i++)
	    	cnt[c[i]]++;	
	    	
	    start[0] = 0;
	    for (int i = 1; i < classes; i++)	
	    	start[i] = start[i - 1] + cnt[i - 1];
	    	
	    for (int i = 0; i < n; i++)
	    	p[start[c[oldP[i]]]++] = oldP[i];
	    	
	    swap(c, oldC);
	    classes = 1;
	    c[p[0]] = 0;
	    for (int i = 1; i < n; i++) {
	    	if (oldC[p[i - 1]] != oldC[p[i]] || oldC[(p[i - 1] + curLen) % n] != oldC[(p[i] + curLen) % n])
	    		classes++;
	    	c[p[i]] = classes - 1;
	    }
	    
	    curLen <<= 1;
	}
	
//LCP
//THIS PART IS NECESSARY FOR FINDING LCP OF CYCLIC SHIFTS!!!
	int lf = 0;
	forab(i, 1, n + 1)
		if (i == n || c[p[i - 1]] != c[p[i]]) {
			int rg = i;
			sort(p + lf, p + rg);
			reverse(p + lf, p + rg);			
			lf = i;
		}    
//CASAI ALGORITHM		
	for (int i = 0; i < n; i++)
		pos[p[i]] = i;
	
	curLCP = 0;
	for (int i = 0; i < n; i++) {
		int j = pos[i];
		if (curLCP > 0)
			curLCP--;

		if (j == n - 1) {
			lcp[j] = -1;
			curLCP = 0;
		} else {
			int k = p[j + 1];
			while (curLCP < n && s[(i + curLCP) % n] == s[(k + curLCP) % n])
				curLCP++;
			lcp[j] = curLCP;
		}		
	}
	