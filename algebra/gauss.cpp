vector<pair<ld, int> > gauss(vector<vector<ld> > a) {
	vector<pair<ld, int> > res; //res[i].X = x[i];
	                            //res[i].Y = 1, if value if fixed, and 0 otherwise
	
	int n = a.size();
	if (n == 0)
		return res;
	int m = (int)a[0].size() - 1;
	
	vector<int> where;
	res.resize(m, {0, 0});
	where.resize(m, -1);	
	
	for (int col = 0, row = 0; col < m && row < n; col++) {
		int id = row;
		for (int j = row; j < n; j++)
			if (fabs(a[j][col]) > fabs(a[id][col]))
				id = j;

		if (fabs(a[id][col]) < eps)
			continue;

		for (int j = 0; j <= m; j++)
			swap(a[row][j], a[id][j]);
		where[col] = row;	
		
		for (int j = 0; j < n; j++)
			if (j != row) {
				ld C = -a[j][col] / a[row][col];
				for (int k = 0; k <= m; k++)
					a[j][k] += a[row][k] * C;	
			}
			
		row++;
	}
	/*
	forn(i, n)
		forn(j, m + 1)
			cout << a[i][j] << " \n"[j == m];
	*/		
	//assigning
	for (int i = 0; i < m; i++)
		if (where[i] != -1) {
			res[i].X = a[where[i]][m] / a[where[i]][i];
			res[i].Y = 1;	
		}
		
	//checking
	for (int i = 0; i < n; i++) {
		ld sum = 0;
		for (int j = 0; j < m; j++)
			sum += res[j].X * a[i][j];
		if (fabs(sum - a[i][m]) >= eps) {
			res.clear();
			return res;
		}
	}
	
	return res;
}