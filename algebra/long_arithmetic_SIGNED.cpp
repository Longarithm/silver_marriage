const int base = (int)1E9;    

struct lnum {
	vector<int> a;
	bool sign;
	
	lnum() {
		a.clear();
		a.push_back(0);
		sign = 1;
	};
	lnum(int x) {
		a.clear();
		a.push_back(abs(x));
		sign = (x >= 0);
	};
	lnum(vector<int> _a) {
		a = _a;
		sign = 1;
	};
	
	bool operator==(lnum b) {
		return a == b.a && (sign == b.sign || (a.size() == 1 && a[0] == 0));	
	}
	
	bool operator<(lnum b) {
		if (!sign && b.sign && !(*this == b))
			return 1;
		if (sign && !b.sign)
			return 0;
		if (!sign && !b.sign) {
			lnum a1 = *this;
			lnum a2 = b;
			a1.sign ^= 1;
			a2.sign ^= 1;
			return a2 < a1;	
		}
				
		if (a.size() != b.a.size())
			return a.size() < b.a.size();
		
		for (int i = (int)a.size() - 1; i >= 0; i--)
			if (a[i] != b.a[i])
				return a[i] < b.a[i];	
		return 0;
	}
	
	bool operator<=(lnum b) {
		lnum a1 = *this;
		return (a1 < b) || (a1 == b);
	}
	
	void read() {
		string buf;
		char s[MAXN];
		sign = 1;
		
		cin >> buf;
		if (buf[0] == '-') {
			sign = 0;
			buf = buf.substr(1, buf.size() - 1);
		}
		
		strcpy(s, buf.c_str());
		int len = strlen(s);

		a.clear();
		for (int i = len; i > 0; i -= 9) {
			s[i] = 0;
			a.push_back(atoi(i >= 9 ? s + i - 9 : s));
		}
	}

	void print() {
		if (!sign)
			cout << '-';
		int len = a.size() - 1;
		printf("%d", a.empty() ? 0 : a.back());
		for (int i = len - 1; i >= 0; i--)
			printf("%09d", a[i]);
		cout << endl;
	}

	lnum operator+(lnum b) {
		lnum a1 = *this;
		lnum a2 = b;
		a1.sign = 1;
		a2.sign = 1;
		if (a1 < a2)
			return b + *this;
			
		lnum res;
		res.a.clear();
		
		if (sign ^ b.sign) {
			res = a1 - a2;
			res.sign = sign;
			return res;
		}
		
		res.sign = sign;		
			
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
	
	lnum operator-(lnum b) {
		lnum res(a);
		
		lnum a1 = *this;
		lnum a2 = b;
		a1.sign = 1;
		a2.sign = 1;
		
		if (a1 < a2) {
			res = b - *this;
			res.sign ^= 1;
			return res;
		}
			
		if (sign ^ b.sign) {
			res = a1 + a2;
			res.sign = sign;
			return res;
		}
		
		res.sign = sign;		
		
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
			
		res.sign = (sign == b.sign);
		
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
			
		res.sign = sign ^ (b >= 0);
		
		return res;
	} 
	
	lnum operator/(lnum b) {
		//!!!!!!!!!!
		assert(sign);
		assert(b.sign);
		//!!!!!!!!!!
		lnum res, curVal, cur;
		
		res.a.resize(a.size(), 0);
		res.sign = 1;
		
		for (int i = (int)a.size() - 1; i >= 0; i--) {
			curVal.a.pb(0);
			for (int j = (int)curVal.a.size() - 1; j > 0; j--)
				curVal.a[j] = curVal.a[j - 1];
			while (curVal.a.size() > 1 && curVal.a.back() == 0)
				curVal.a.pop_back();
			curVal.a[0] = a[i];
		
			//binary search
			int l = 0, r = base, mid;
			while (r - l > 1) {
				mid = (l + r) >> 1;
				cur = b * lnum(mid);
				
				if (cur < curVal || cur == curVal)
					l = mid;
				else
					r = mid;
			}
			
			res.a[i] = l;
			curVal = curVal - b * lnum(l);  		
		}
		
		while (res.a.size() > 1 && res.a.back() == 0)
			res.a.pop_back();
			
		res.sign = (sign == b.sign);
		
		return res;		
	}           
	
	lnum operator%(lnum b) { //always returns value in [0, b)
		bool f = sign;
		sign = 1;
		
		lnum curVal, cur;
		curVal.sign = 1;
		
		for (int i = (int)a.size() - 1; i >= 0; i--) {
			curVal.a.pb(0);
			for (int j = (int)curVal.a.size() - 1; j > 0; j--)
				curVal.a[j] = curVal.a[j - 1];
			while (curVal.a.size() > 1 && curVal.a.back() == 0)
				curVal.a.pop_back();
			curVal.a[0] = a[i];
		
			int l = 0, r = base, mid;
			while (r - l > 1) {
				mid = (l + r) >> 1;
				cur = b * lnum(mid);
				
				if (cur <= curVal)
					l = mid;
				else
					r = mid;
			}
			      
			curVal = curVal - b * lnum(l);  		
		}
		
		if (!f)
			curVal = b - curVal;
		sign = f;
			
		assert(lnum(0) <= curVal && curVal < b);
		return curVal;		
	}
};
