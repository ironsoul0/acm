#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

const int INF = 2e9;
const int SIZE = 9;

#define sz(s) int(s.size())

#define pii pair<int, int>

#define mp make_pair
#define pb push_back

#define fi first
#define se second

#define all(c) c.begin(), c.end()

/*
Переведите каждого из двух коней из одной клетки в другую за наименьшее общее число ходов.
Два коня не могут одновременно находиться в одной клетке.
*/

struct horse {
	int l, r;
};

bool used[SIZE][SIZE][SIZE][SIZE];
pair<horse, horse> road[SIZE][SIZE][SIZE][SIZE];

int dx[] = {-1, -1, 1, 1, 2, 2, -2, -2}; 
int dy[] = {2, -2, 2, -2, 1, -1, 1, -1};

horse convert(char c, int x) {
	horse cnt;
	cnt.l = int(c - 'a' + 1);
	cnt.r = x;
	return cnt;
}

bool good(int x, int y) {
	return (x > 0 && x < SIZE && y > 0 && y < SIZE);
}

horse typ(int x, int y) {
	horse cnt;
	cnt.l = x;
	cnt.r = y;
	return cnt;
}

bool operator == (horse one, horse two) {
	return (one.l == two.l && one.r == two.r);
}

bool eq(int a, int b, int c, int d) {
	return (a == c && b == d); 
}

int main() {
	freopen("knight2.in", "r", stdin);
	freopen("knight2.out", "w", stdout);
	horse s1, s2, f1, f2;
	char c;
	int x;

	cin >> c >> x;
	s1 = convert(c, x);
	cin >> c >> x;
	s2 = convert(c, x);
	cin >> c >> x;
	f1 = convert(c, x);
	cin >> c >> x;
	f2 = convert(c, x);

	queue<pair<horse, horse> > q;
	q.push(make_pair(s1, s2));
	used[s1.l][s1.r][s2.l][s2.r] = 1;

	while(!q.empty()) {
		pair<horse, horse> p = q.front();
		horse k1 = p.fi, k2 = p.se; 
		q.pop();
		for (int i = 0; i < 8; i++) {
			int x = dx[i] + k1.l;
			int y = dy[i] + k1.r;
			if (good(x, y) && !eq(x, y, k2.l, k2.r) && !used[x][y][k2.l][k2.r]) {
				q.push(mp(typ(x, y), typ(k2.l, k2.r)));
				used[x][y][k2.l][k2.r] = 1;
				road[x][y][k2.l][k2.r] = mp(k1, k2);
			}
		}
		for (int i = 0; i < 8; i++) {
			int x = dx[i] + k2.l;
			int y = dy[i] + k2.r;
			if (good(x, y) && !eq(x, y, k1.l, k1.r) && !used[k1.l][k1.r][x][y]) {
				q.push(mp(typ(k1.l, k1.r), typ(x, y)));
				used[k1.l][k1.r][x][y] = 1;
				road[k1.l][k1.r][x][y] = mp(k1, k2);
			}		
		}
	}  


	vector<pair<char, int> > ans;

	for (pair<horse, horse> p = mp(f1, f2); p != mp(s1, s2); p = road[p.fi.l][p.fi.r][p.se.l][p.se.r]) {
		ans.pb(mp(p.se.l + 'a' - 1, p.se.r));
		ans.pb(mp(p.fi.l + 'a' - 1, p.fi.r));		
	}	

	reverse(all(ans));
	
	pair<char, int> horse1 = mp(s1.l + 'a' - 1, s1.r);
	pair<char, int> horse2 = mp(s2.l + 'a' - 1, s2.r);
     
     for (int i = 0; i < sz(ans); i += 2) {
		if (ans[i] != horse1) {
			cout << 1 << " " << ans[i].fi << ans[i].se << '\n';
			horse1 = ans[i];
		}
		if (ans[i + 1] != horse2) {
			cout << 2 << " " << ans[i + 1].fi << ans[i + 1].se << '\n';
			horse2 = ans[i + 1];
		}
	}
	return 0;
}