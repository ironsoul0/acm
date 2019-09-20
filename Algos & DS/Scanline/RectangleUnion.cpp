#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

const int INF = 2e9;
const int SIZE = 2e5;

#define sz(s) int(s.size())

#define pii pair<int, int>

#define mp make_pair
#define pb push_back

#define fi first
#define se second

#define all(c) c.begin(), c.end()

/*
На плоскости задано N прямоугольников с вершинами в точках с целыми координатами и сто-
ронами, параллельными осям координат. Необходимо найти площадь их объединения.
*/

struct point {
	ll val;
	int id, type;
	point(ll _val, int _id, int _type) {
		val = _val;
		id = _id;
		type = _type; 
 	}	
};

bool operator < (point one, point two) {
	return (one.val < two.val) ||
		(one.val == two.val && one.type < two.type)
			|| (one.val == two.val && one.type == two.type && one.id < two.id);
}

vector<point> x, y;
int n;
vector<bool> active(SIZE, false);

ll intersection() {
	ll ans = 0;
	ll here;
	int cnt = 0;
	for (int i = 0; i < sz(y); i++) {
		if (active[y[i].id]) {
			cnt -= y[i].type;
			if (cnt == 1 && y[i].type == -1) {
		     	here = y[i].val;
			}
			if (cnt == 0) {
				ans += y[i].val - here;
			}
		}
	}
	return ans;
}

int main() {
	freopen("union.in", "r", stdin);
	freopen("union.out", "w", stdout);

	cin >> n;

	for (int i = 0; i < n; i++) {
		ll x1, y1, x2, y2;  
		cin >> x1 >> y1 >> x2 >> y2;
		x.pb(point(x1, i, -1));
		x.pb(point(x2, i, 1));
		y.pb(point(y1, i, -1));
		y.pb(point(y2, i, 1));			
	}
	
	sort(all(x));
	sort(all(y));

	ll total = 0;

	for (int i = 0; i < sz(x) - 1; i++) {
		ll delta = x[i + 1].val - x[i].val;
		if (x[i].type == 1) {
			active[x[i].id] = 0;
		}
		if (x[i].type == -1) {
			active[x[i].id] = 1;
		}
		total += intersection() * delta;
	}
		
	cout << total;

	return 0;
} 