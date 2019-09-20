#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

const int INF = 2e9;
const int SIZE = 2e5;
const double EPS = 1e-8;

#define sz(s) int(s.size())

#define pii pair<int, int>

#define mp make_pair
#define pb push_back

#define fi first
#define se second

#define all(c) c.begin(), c.end()

/*
На прямой задано некоторое множество отрезков с целочисленными координатами концов.
Выберите среди данного множества подмножество отрезков, целиком покрывающее отрезок
[0, M], (M — натуральное число), содержащее наименьшее число отрезков.

*/

void incorrect() {
	puts("No solution");
	exit(0);
}

int main() {
	freopen("cover.in", "r", stdin);
	freopen("cover.out", "w", stdout);

	int m;
	cin >> m;
	vector<pii> seg, ans;
	pii segment;
	
	while(cin >> segment.fi >> segment.se) {
		seg.pb(segment);
	}

	sort(all(seg));

	int x = 0, i = 0;

	while(x < m && i < sz(seg)) {
		if (i > sz(seg) || seg[i].fi > x) {
			incorrect();
		}
		int pos = -1, cntMax = -INF;
		while(i < sz(seg) && seg[i].fi <= x) {
			if (seg[i].se >= cntMax) {
				pos = i;
				cntMax = seg[i].se;
			}
			++i;
		}
		--i;
		if (pos != -1 && i > -1 && cntMax >= x) {
			ans.pb(seg[pos]);
			x = seg[pos].se;
			if (x >= m) {
				break;
			}				
		} else {
			incorrect();
		}
		++i;
	}

	if (x < m) {
		incorrect();
	} else {
		cout << sz(ans) << '\n';
		for (auto elem : ans) {
			cout << elem.fi << " " << elem.se << '\n';
		}
	}

	return 0;
}