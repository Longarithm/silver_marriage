#include <bits/stdc++.h>

using namespace std;

typedef float ld;

const ld eps = 1e-7;
const int maxn = 100000;

struct pt
{
	ld x;
	ld y;
	pt(){}
	pt(ld _x, ld _y)
	{
		x = _x;
		y = _y;		
	}	
};

struct segment
{
	ld A;
	ld B;
	ld C;
	pt left;
	pt right;
	segment()
	{
		A = B = C = 0;
		left = pt(0,0);
		right = pt(0,0);
	}
	segment(const pt &a, const pt &b)
	{
		A = a.y - b.y;
		B = b.x - a.x;
		C = a.x * b.y - b.x * a.y;				
		left = a;
		right = b;

		if (a.x > b.x)
		{
			swap(left, right); 
		}
	}

	bool isOnSegment(const pt &a)
	{
		return (fabs(A * a.x + B * a.y + C) < eps && min(left.x,right.x) <= a.x + eps && a.x <= max(right.x,left.x) + eps &&
				min(left.y, right.y) <= a.y + eps && a.y <= max(left.y, right.y) + eps);
	}

	bool isIntersect(const pt &a, ld alpha, ld beta)
	{
		ld u = -C - A * a.x - B * a.y;
		ld v = A * alpha + B * beta;
		if (fabs(v) < eps)
			return false;
	    ld t = u / v;
	    if (t < eps)
	    	return false;
	    bool fl = isOnSegment(pt(a.x + t * alpha, a.y + t * beta));
	    return fl;
	}
};

pt P[maxn * 3];
segment Segment[maxn * 3];


int main()
{
	freopen ("point.in", "r", stdin);
	freopen ("point.out", "w", stdout);
	int n = 0;
        scanf("%d", &n);
	ld x, y;
        scanf("%f%f", &x, &y);
	pt A = pt(x, y);
	for (int i = 0; i < n; i++)
	{
                scanf("%f%f", &x, &y);
		P[i] = pt(x, y);
		P[i + n] = P[i];
	}
	for (int i = 0; i < n; i++)
	{
		Segment[i] = segment(P[i], P[i + 1]);
	}
	for (int i = 0; i < n; i++)
	{
		if (Segment[i].isOnSegment(A))
		{
			cout << "YES";
			return 0;
		}
	}
	int success = 0;
	for (int i = 0; i < 5; i++)
	{
		ld alpha = (rand() - rand()) / 1000000.;
		ld beta = (rand() - rand()) / 1000000.;
		int cnt = 0;
		for (int j = 0; j < n; j++)
		if (Segment[j].isIntersect(A, alpha, beta))
			cnt++;
		success += (cnt & 1);
		
	}
	if (success > 2)
	{
		cout << "YES";
		return 0;
	}
	cout << "NO";
	return 0;
}