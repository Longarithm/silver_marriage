int k, ilen, jlen;
int p[MAXN], id[MAXM], last;

void divide(short int a, short int len) {
	short int clen = (len >> 1);
	id[k++] = last;
	forn(i, clen) forn(j, clen)
		p[last + i * clen + j] = p[id[a] + i * len + j];
	last += len * len;
	id[k++] = last;
	forn(i, clen) forn(j, clen)
		p[last + i * clen + j] = p[id[a] + i * len + j + clen];
	last += len * len;
	id[k++] = last;
	forn(i, clen) forn(j, clen)
		p[last + i * clen + j] = p[id[a] + (i + clen) * len + j];
	last += len * len;
	id[k++] = last;
	forn(i, clen) forn(j, clen)
		p[last + i * clen + j] = p[id[a] + (i + clen) * len + j + clen];
	last += len * len;
}

short int add(short int a, short int b, short int len) {
	id[k] = last;
	forn(i, len * len)
		p[last + i] = p[id[a] + i] + p[id[b] + i];
	last += len * len;
	k++;
	return k - 1;
}

short int sub(short int a, short int b, short int len) {
	id[k] = last;
	forn(i, len * len)
		p[last + i] = p[id[a] + i] - p[id[b] + i];
	last += len * len;
	k++;
	return k - 1;
}

short int shtrassen(short int a, short int b, short int len) {
	int ck = k++, clen = (len >> 1);
	if (len <= 128) {
		id[ck] = last;
		last += len * len;
		ilen = 0;
		forn(i, len) {
			jlen = 0;
			forn(j, len) {
				forn(k, len)
					p[id[ck] + ilen + k] += p[id[a] + ilen + j] * p[id[b] + jlen + k];
				jlen += len;
			}
			ilen += len;
		}
		return ck;
	}
	id[ck] = last;
	last += len * len;
	divide(a, len);
	int a11 = ck + 1, a12 = ck + 2, a21 = ck + 3, a22 = ck + 4;
	divide(b, len);
	int b11 = ck + 5, b12 = ck + 6, b21 = ck + 7, b22 = ck + 8;
	int s1 = add(a21, a22, clen),
		s2 = sub(s1, a11, clen),
		s3 = sub(a11, a21, clen),
		s4 = sub(a12, s2, clen),
		s5 = sub(b12, b11, clen),
		s6 = sub(b22, s5, clen),
		s7 = sub(b22, b12, clen),
		s8 = sub(s6, b21, clen),
		p1 = shtrassen(s2, s6, clen),
		p2 = shtrassen(a11, b11, clen),
		p3 = shtrassen(a12, b21, clen),
		p4 = shtrassen(s3, s7, clen),
		p5 = shtrassen(s1, s5, clen),
		p6 = shtrassen(s4, b22, clen),
		p7 = shtrassen(a22, s8, clen),
		t1 = add(p1, p2, clen),
		t2 = add(t1, p4, clen);

	forn(i, clen) forn(j, clen)
		p[id[ck] + i * len + j] = p[id[p2] + i * clen + j] + p[id[p3] + i * clen + j];
	forn(i, clen) forn(j, clen)
		p[id[ck] + i * len + j + clen] = p[id[t1] + i * clen + j] + p[id[p5] + i * clen + j] + p[id[p6] + i * clen + j];
	forn(i, clen) forn(j, clen)
		p[id[ck] + (i + clen) * len + j] = p[id[t2] + i * clen + j] - p[id[p7] + i * clen + j];
	forn(i, clen) forn(j, clen)
		p[id[ck] + (i + clen) * len + j + clen] = p[id[t2] + i * clen + j] + p[id[p5] + i * clen + j];
	
	return ck;
}

<...>

id[0] = 0;
id[1] = n * n;
//write to p[0] and p[1]
shtrassen(0, 1, nn);
//answer is in p[2]