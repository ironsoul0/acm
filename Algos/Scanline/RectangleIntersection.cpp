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
ронами, параллельными осям координат. Необходимо найти прямоугольник, являющийся их пере-
сечением.
То, что это прямоугольник, докажите самостоятельно
*/

int n;

pair<int, int> scanline(vector<pair<int, int> >& p) {
	int cnt = 0;
	bool f = 0;
	pair<int, int> ans = mp(-1, -1);
	sort(all(p));
	
	for (int i = 0; i < sz(p); i++) {
		cnt -= p[i].se;
		if (cnt == n) {
			ans.fi = p[i].fi;
			f = 1;
		} else if (cnt == n - 1 && p[i].se == 1 && f) {
			ans.se = p[i].fi;
		}
	}
	return ans;
}

int main() {
	freopen("rect.in", "r", stdin);
	freopen("rect.out", "w", stdout);

	vector<pair<int, int> > x, y;

	cin >> n;

	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		x.pb(mp(x1, -1));
		x.pb(mp(x2, 1));
		y.pb(mp(y1, -1));
		y.pb(mp(y2, 1));		
	}

	pair<int, int> a = scanline(x), b = scanline(y);
	
	if (a == mp(-1, -1) || b == mp(-1, -1)) {
		cout << -1;
		return 0;
	}

	cout << a.fi << " " << b.fi << " " << a.se << " " << b.se;

	return 0;
}