// Very special case of Lenstra's algorithm: elliptic curve y^2=x^3+ax-a
// It tries to factorize "big" number N.
// Aleksandr Logunov, 2015

#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; i--)
#define forab(i, k, n) for (int i = (int)(k); i < (int)(n); i++)
#define forba(i, n, k) for (int i = (int)(n) - 1; i >= (int)(k); i--)

#define vi vector<int>
#define pii pair<int, int>
#define all(x) (x).begin(), (x).end()
#define sqr(x) ((x)*(x))
#define X first
#define Y second                    
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef long double ld; 

const ld pi = acos(-1.0);
const ld eps = 1e-9;
const int INF = 1E9;        
const int MAXN = 200500;

struct point {
	ll x, y;
	
	point() {x = y = 0;}
	point(ll _x, ll _y): x(_x), y(_y) {};
};

bool operator==(point A, point B) {
	return A.x == B.x && A.y == B.y;
}

ll N, a, X;

ll gcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;	
	}
	ll x1, y1, g;
	g = gcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - (a / b) * y1;	
	return g;
}

ll inv(ll a) {
	ll g = __gcd(a, N);
	if (g == N) {
		X = -1;
		return 0;
	}
	if (g > 1) {
		X = g;
		return 0;
	}
	ll x, y;
	a %= N;
	gcd(a, N, x, y);
	x %= N;
	return x;	
}

point operator+(point A, point B) {
	point res;
	
	if (A == B) {            
		ll z = (3 * A.x * A.x + a) * inv(A.y * 2) % N;
		res.x = (z * z - 2 * A.x) % N;
		res.x = (N + res.x) % N;
		res.y = (-A.y + z * (A.x - res.x)) % N;
		res.y = (N + res.y) % N;
	} else {
		ll z = (B.y - A.y) * inv(B.x - A.x) % N;
		res.x = (z * z - A.x - B.x) % N;
		res.x = (N + res.x) % N;
		res.y = (-A.y + z * (A.x - res.x)) % N;
		res.y = (N + res.y) % N;
	}
	
	return res;
}

vector<pii> mul; 
point P, P2;

int main() {

	mul.pb({2, 6});
	mul.pb({3, 4});
	mul.pb({5, 2});

	cin >> N;
	X = 0;
	for (a = 1; a <= 100; a++) {
		P = point(1, 1);
		forn(id, mul.size()) {
			pii c = mul[id];
			forn(i, c.Y) {
				P2 = P;
				forn(j, c.X - 1) {
					P2 = P2 + P;
					if (X != 0) {
						printf("Base: %I64d\n", a);
						printf("Position: %d^%d*P_%d\n", c.X, i + 1, id + 1);
						printf("Multiplier: %I64d\n", X);
						return 0;
					}
				}
				P = P2;
			}
		}
	}
	cout << "Bad luck. Maybe N is prime?\n";
	
	return 0;
}
