#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int MOD = (int) 1e9 + 7;
const int N = (int) 1e6 + 7;
 
ll a[N];

int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	int m;
	ll n;
	cin >> n >> m;	
	ll all = 0;
	vector<ll> b;
	for (int i = 0; i < m; i++) {
		cin >> a[i];
		all += a[i] * 2;
		b.push_back(a[i]);
	}
	if (all < n) {
		cout << -1;
		return 0;
	}
	for (int i = 0; i < m; i++) {
		b.push_back(a[i]);
	}
	int full = (int)b.size(), pt = MOD;
	for (int mask = 0; mask < (1 << full); mask++) {
		ll sum = 0;
		for (int i = 0; i < full; i++)
			if (mask & (1 << i)) sum += b[i];
		if (sum == n)
			pt = min(pt, __builtin_popcount(mask));
	}
	if (pt == MOD)
		cout << 0;
	else
		cout << pt;
	return 0;
}