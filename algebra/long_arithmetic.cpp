const int base = (int)1E9;    

struct lnum {
	vector<int> a;

	lnum() {
		a.clear();
		a.push_back(0);
	};
	lnum(int x) {
		a.clear();
		a.push_back(x);
	};
	lnum(vector<int> _a) {
		a = _a;
	};
	
	void read() {
		string buf;
		char s[MAXN];
		
		cin >> buf;
		strcpy(s, buf.c_str());
		int len = strlen(s);

		a.clear();
		for (int i = len; i > 0; i -= 9) {
			s[i] = 0;
			a.push_back(atoi(i >= 9 ? s + i - 9 : s));
		}
	}

	void print() {
		int len = a.size() - 1;
		printf("%d", a.empty() ? 0 : a.back());
		for (int i = len - 1; i >= 0; i--)
			printf("%09d", a[i]);
		printf("\n");
	}

	lnum operator+(lnum b) {
		lnum res;
		res.a.clear();
		int rest = 0, len = max(a.size(), b.a.size());
		for (int i = 0; i < len || rest; i++) {
			res.a.push_back(0);
			res.a[i] = (i < (int)a.size() ? a[i] : 0) + (i < (int)b.a.size() ? b.a[i] : 0) + rest;
			rest = res.a[i] >= base;
			if (rest) 
				res.a[i] -= base;
		}
		return res;
	}
	
	bool operator==(lnum b) {
		return a == b.a;	
	}
	
	bool operator<(lnum b) {
		if (a.size() != b.a.size())
			return a.size() < b.a.size();
		
		for (int i = (int)a.size() - 1; i >= 0; i--)
			if (a[i] != b.a[i])
				return a[i] < b.a[i];	
		return 0;
	}
	
	lnum operator-(lnum b) {
		lnum res(a);
		
		int rest = 0;
		for (int i = 0; i < (int)b.a.size() || rest; i++) {
			res.a[i] -= (i < (int)b.a.size() ? b.a[i] : 0) + rest;
			rest = res.a[i] < 0;
			if (rest) 
				res.a[i] += base;
		}
		while ((int)res.a.size() > 1 && res.a.back() == 0)
			res.a.pop_back();
		return res;
	}
	
	lnum operator*(lnum b) {
		lnum res;
		res.a.resize(a.size() + b.a.size(), 0);
		
		for (int i = 0; i < (int)a.size(); i++)
			for (int j = 0, rest = 0; j < (int)b.a.size() || rest; j++) {
				long long cur = res.a[i + j] + 
					1ll * a[i] * (j < (int)b.a.size() ? b.a[j] : 0) + rest;
				res.a[i + j] = cur % base;
				rest = cur / base;
			}
		while (res.a.size() > 1 && res.a.back() == 0)
			res.a.pop_back();
		return res;
	}
	
	lnum operator/(int b) {
		lnum res;
		res.a = a;
		
		int rest = 0;
		for (int i = (int)res.a.size() - 1; i >= 0; i--) {
			long long cur = res.a[i] + rest * 1ll * base;
			res.a[i] = cur / b;
			rest = cur % b;
		}
		
		while (res.a.size() > 1 && res.a.back() == 0)
			res.a.pop_back();
		return res;
	}
};

lnum gcd(lnum b1, lnum b2) { //STILL NOT TESTED! TRY TO FIND A TASK
	if ((b1.a.size() == 1) && (b1.a[0] == 0))
		return b2;
	if ((b2.a.size() == 1) && (b2.a[0] == 0))
		return b1;

	if ((b1.a[0] % 2 == 0) && (b2.a[0] % 2 == 0))
		return gcd(b1 / 2, b2 / 2) * lnum(2); 
	if (b1.a[0] % 2 == 0)
		return gcd(b1 / 2, b2);
	if (b2.a[0] % 2 == 0)
		return gcd(b1, b2 / 2);

	if (b2 < b1)
		return gcd(b1 - b2, b2);
	return gcd(b2 - b1, b1);
}
