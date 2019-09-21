#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <queue>
#include <set>
#include <map>
#include <cassert> 

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int MOD = (int) 1e9 + 7;
const int N = (int) 1e6 + 7;
const ll INF = (ll) 1e18 + 7;

int t[N * 4][2];

void setVal(int v, int mini) {
	if (mini == 0) {
		t[v][mini] = min(t[v + v][mini], t[v + v + 1][mini]);
	} else {
		t[v][mini] = max(t[v + v][mini], t[v + v + 1][mini]);
	}
}

void upd(int v, int tl, int tr, int idx, int val, int mini) {
	if (tl == tr) {
		t[v][mini] = val;
	} else {
		int tm = (tl + tr) >> 1;
		if (idx <= tm) {
			upd(v + v, tl, tm, idx, val, mini);
		}	else {
			upd(v + v + 1, tm + 1, tr, idx, val, mini);
		}
		setVal(v, mini);
	}
}

int get(int v, int tl, int tr, int l, int r, int mini) {
	if (l <= tl && r >= tr) {
		return t[v][mini];
	}
	if (l > tr || r < tl) {
		if (mini == 0) return INT_MAX; else return INT_MIN;
	}
	int tm = (tl + tr) >> 1;
	if (mini == 0) {
		return min(get(v + v, tl, tm, l, r, mini), get(v + v + 1, tm + 1, tr, l, r, mini));
	} else {
		return max(get(v + v, tl, tm, l, r, mini), get(v + v + 1, tm + 1, tr, l, r, mini));
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		upd(1, 1, n, i, +MOD, 0);
		upd(1, 1, n, i, -MOD, 1);
	}
	for (int i = 1; i <= n; i++) {
		int l, r;
		cin >> l >> r;
		upd(1, 1, n, i, r, 0);
		upd(1, 1, n, i, l, 1);
	}
	while (q--) {
		char c;
		cin >> c;
		if (c == '?') {
			int l, r;
			cin >> l >> r;
			int maxi_l = get(1, 1, n, l, r, 1), mini_r = get(1, 1, n, l, r, 0);
			cout << max(0, mini_r - maxi_l + 1) << '\n';
		} else {
			int idx, l, r;
			cin >> idx >> l >> r;
			upd(1, 1, n, idx, r, 0);
			upd(1, 1, n, idx, l, 1);
		}
	}
	return 0;
}