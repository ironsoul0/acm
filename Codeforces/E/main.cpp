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

ll dp[N][2], t[N * 4][2];
int n, k;

void upd(int v, int tl, int tr, int idx, ll val, int type) {
	if (tl == tr) {
		t[v][type] = val;
	} else {
		int tm = (tl + tr) >> 1;
		if (idx <= tm)
			upd(v + v, tl, tm, idx, val, type);
		else
			upd(v + v + 1, tm + 1, tr, idx, val, type);
		t[v][type] = min(t[v + v][type], t[v + v + 1][type]);
	}
}

ll get(int v, int tl, int tr, int l, int r, int type) {
	if (l <= tl && r >= tr) {
		return t[v][type];
	}
	if (l > tr || r < tl) {
		return INF;
	}
	int tm = (tl + tr) >> 1;
	return min(get(v + v, tl, tm, l, r, type), get(v + v + 1, tm + 1, tr, l, r, type));
}

ll calc(int idx, int param = 0) {
	if (idx == 0) return 0ll;
	int l = max(idx - k, 1), r = idx - 1;
	return get(1, 1, n, l, r, param);
}

int main() {
	ios_base::sync_with_stdio(0);
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
	string s;
	cin >> n >> k >> s;
	for (int i = 1; i <= n; i++) {
		dp[i][0] = dp[i][1] = INF;
		upd(1, 1, n, i, INF, 0);
		upd(1, 1, n, i, INF, 1);
	}
	dp[1][0] = 1;
	dp[1][1] = (s[0] == '0') ? INF : 1;
	upd(1, 1, n, 1, dp[1][1], 0);
	upd(1, 1, n, 1, 1, 1);
	for (int i = 2; i <= n; i++) {
		dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]) + i;
		dp[i][0] = min(dp[i][0], calc(i));
		if (s[i - 1] == '1') {
			if (i - k - 1 > 0) {
				dp[i][1] = calc(i - 1, 1) + i;
			} else {
				dp[i][1] = i;
			}
		}
		upd(1, 1, n, i, dp[i][1], 0);
		upd(1, 1, n, i, min(dp[i][0], dp[i][1]), 1);
	}
	cout << min(dp[n][0], dp[n][1]); 
	return 0;
}