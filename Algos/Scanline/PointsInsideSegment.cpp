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
Дано n отрезков на числовой прямой и m точек на этой же прямой. Для каждой из данных
точек определите, скольким отрезкам она принадлежит. Точка x считается принадлежащей отрезку
с концами a и b, если выполняется двойное неравенство min(a, b) <= x <= max(a, b).
*/

int main() {
	freopen("segments.in", "r", stdin);
	freopen("segments.out", "w", stdout);
	
	map<int, int> query;
	pair<int, int> some;
	vector<int> question;
	vector<pair<int, int> > p;
	int n, m;
	cin >> n >> m;
	
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		if (a > b) {
			swap(a, b);
		}
		p.pb(mp(a, -1));
		p.pb(mp(b, 1));
	}

	for (int i = 0; i < m; i++) {
		cin >> some.fi;
		some.se = 0;
		p.pb(some);
		question.pb(some.fi);
	}
	int cnt = 0;
	sort(all(p));

	for (int i = 0; i < sz(p); i++) {
		cnt -= p[i].se;
		if (p[i].se == 0) {
			query[p[i].fi] = cnt;
		}
	}
	for (auto ask : question) {
		cout << query[ask] << " ";
	}
	return 0;
}            