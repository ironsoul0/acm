#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 1e5 + 7;
const double EPS = (double) 1e-6;

/**
Сколько чисел на отрезке l, r лежат между p, q;
**/

#define fs first
#define sc second

int a[N];
vector<int> t[N * 4];

void build(int v, int tl, int tr) {
	if (tl == tr) {
		t[v].push_back(a[tl]);
	} else {
		int tm = (tl + tr) >> 1;
		build(v + v, tl, tm);
		build(v + v + 1, tm + 1, tr);
		t[v].resize(t[v + v].size() + t[v + v + 1].size());
		merge(t[v + v].begin(), t[v + v].end(), t[v + v + 1].begin(), t[v + v + 1].end(), t[v].begin());
	}
}

int get(int v, int tl, int tr, int l, int r, int x, int y) {
	if (l <= tl && r >= tr) {
		int from_x = lower_bound(t[v].begin(), t[v].end(), x) - t[v].begin();
		int end_y = upper_bound(t[v].begin(), t[v].end(), y) - t[v].begin() - 1;
		if (from_x == (int) t[v].size() || end_y < 0)
			return 0;
		else
			return end_y - from_x + 1;
	}
	if (l > tr || r < tl)
		return 0;
	int tm = (tl + tr) >> 1;
	return get(v + v, tl, tm, l, r, x, y) + get(v + v + 1, tm + 1, tr, l, r, x, y);
}

int main() {
	ios_base::sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	build(1, 1, n);
	while (m--) {
		int l, r, x, y;
		cin >> l >> r >> x >> y;
		cout << get(1, 1, n, l, r, x, y) << '\n';
	}	
	return 0;	
}  