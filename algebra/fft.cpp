//COMPLEX NUMBERS STRUCTURE (begin)
struct comp {
	ld x, y;
	
	comp(ld _x = 0, ld _y = 0) {
		x = _x;
		y = _y;	
	}
	
	ld real() {
		return x;	
	}
	
	comp operator+(comp a) {
		return comp(x + a.x, y + a.y);	
	}
	
	comp operator-(comp a) {
		return comp(x - a.x, y - a.y);	
	}
	
	comp operator*(comp a) {
		return comp(x * a.x - y * a.y, x * a.y + y * a.x);	
	}
	
	comp operator/(ld k) {
		return comp(x / k, y / k);	
	}
};

comp conj(comp a) {
	return comp(a.x, -a.y);
}
//COMPLEX NUMBERS STRUCTURE (end)

const int MAXN = 250100;

int res[4 * MAXN];
comp a0[4 * MAXN], b0[4 * MAXN], c0[4 * MAXN];
int MAXSZ, POWER;

int inv(int x) {
	int res = 0;
	forn(i, POWER)
		res += ((x >> i) & 1) << (POWER - 1 - i);
	return res;
}

void fft(comp *a, bool invert) {
	forn(i, MAXSZ)
		if (i < inv(i))
			swap(a[i], a[inv(i)]);
			
	for (int len = 2; len <= MAXSZ; len <<= 1) {
		ld angle = 2.0 * pi / len * (invert ? -1 : 1);
		comp wn(cos(angle), sin(angle));
		for (int i = 0; i < MAXSZ; i += len) {
			comp w(1), u, v;
			for (int j = 0; j < len / 2; j++) {
				u = a[i + j];
				v = a[i + j + len / 2];
				a[i + j] = u + w * v;
				a[i + j + len / 2] = u - w * v;
				w = w * wn;	
			}
		}
	}
	
	if (invert)
		forn(i, MAXSZ)
			a[i] = a[i] / MAXSZ;
}

void multiply(int *a, int asz, int *b, int bsz) {
	POWER = 1;
	while ((1 << POWER) < max(asz, bsz))
		POWER++;
	POWER++;
	MAXSZ = 1 << POWER;

	forn(i, MAXSZ) {
		c0[i].x = a[i];
		c0[i].y = b[i];
	}
	
	fft(c0, 0);
	c0[MAXSZ] = c0[0];
	forn(i, MAXSZ) {
		a0[i] = (c0[i] + conj(c0[MAXSZ - i])) / 2.0;
		b0[i] = (c0[i] - conj(c0[MAXSZ - i])) * comp(0, -1.0) / 2.0;
	}
	
	forn(i, MAXSZ) 
		a0[i] = a0[i] * b0[i];
	
	fft(a0, 1);

	forn(i, MAXSZ)
		res[i] = int(a0[i].real() + 0.5); //DOES NOT WORK FOR NEGATIVE INTS!
}
