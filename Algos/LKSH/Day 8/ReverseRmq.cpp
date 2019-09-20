#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 1e5 + 7;
const double EPS = (double) 1e-6;
const long long BIG = (long long) 1e18 + 7;

/**
По RMQ на отрезках восстноавить исходный массив.
**/

#define fs first
#define sc second

int z[N * 4], t[N * 4];

void push(int v, int tl, int tr) {
	if (v + v + 1 < N * 4 && z[v] != INT_MAX) {
		t[v + v] = t[v + v + 1] = t[v];
		z[v + v] = z[v + v + 1] = z[v];
		z[v] = INT_MAX;
	}
}

void modify(int v, int tl, int tr, int l, int r, int value) {
	if (l <= tl && r >= tr) {
		t[v] = value;
		z[v] = value;
	} else if (l > tr || r < tl) {
		return;
	} else {
		int tm = (tl + tr) >> 1;
		push(v, tl, tr);
		modify(v + v, tl, tm, l, r, value);
		modify(v + v + 1, tm + 1, tr, l, r, value);
		t[v] = min(t[v + v], t[v + v + 1]);
	}
}

int get(int v, int tl, int tr, int l, int r) {
	if (l <= tl && r >= tr)
		return t[v];
	if (l > tr || r < tl)
		return INT_MAX;
	int tm = (tl + tr) >> 1;
	push(v, tl, tr);
	return min(get(v + v, tl, tm, l, r), get(v + v + 1, tm + 1, tr, l, r));
}

int main() {
	for (int i = 0; i < N * 4; i++)
		z[i] = t[i] = INT_MAX;
	int n, m;
	cin >> n >> m;
	vector<pair<int, pair<int, int>>> query;
	for (int i = 0; i < m; i++) {
		int l, r, q;
		cin >> l >> r >> q;
		query.push_back(make_pair(q, make_pair(l, r)));
	}
	sort(query.begin(), query.end());
	for (auto x : query) {
		modify(1, 1, n, x.second.first, x.second.second, x.first);
	}
	for (auto x : query) {
		if (get(1, 1, n, x.second.first, x.second.second) != x.first) {
			cout << "inconsistent";
			return 0;
		}
	}
	cout << "consistent" << '\n';
	for (int i = 1; i <= n; i++)
		cout << get(1, 1, n, i, i) << ' ';
	return 0;	
}  