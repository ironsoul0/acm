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

int a[N], b[N], v[N];
int n, m, ans = 0;

void brute(int idx = 1) {
	if (idx == n + 1) {
		map<pair<int, int>, int> cnt;
		int cur = 0;
		for (int i = 1; i <= m; i++) {
			int cf = v[a[i]], cs = v[b[i]];
			if (cf > cs) swap(cf, cs);
			cnt[{cf, cs}]++;
			cur += (cnt[{cf, cs}] == 1);	
		}	
		ans = max(ans, cur);
	} else {
		for (int i = 1; i <= 6; i++) {
			v[idx] = i;
			brute(idx + 1);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> a[i] >> b[i];
	}
	brute();
	cout << ans;
	return 0;
}