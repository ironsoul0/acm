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

pair<double, double> was[N];
int a[N], dp[N];
string s;

int main() {
	ios_base::sync_with_stdio(0);
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
	clock_t start = clock();
	int n, st;
	cin >> n >> st >> s;
	for (int i = 1; i <= n; i++) a[i] = s[i - 1] - '0';
	for (int i = n + 1; i <= n + n && (clock() - start) / 1.0 / CLOCKS_PER_SEC < 1.0; i++) a[i] = a[i - n];
	double ans = 0.0;
	for (int k = st; k <= n && (clock() - start) / 1.0 / CLOCKS_PER_SEC < 1.0; k++) {
		double cur = 0.0;
		for (int i = 1; i <= k; i++) cur += a[i];
		double maxi = cur;
		for (int i = k + 1; i <= n + n && (clock() - start) / 1.0 / CLOCKS_PER_SEC < 1.0; i++) {
			cur += a[i];
			cur -= a[i - k];
			maxi = max(maxi, cur);
		}
		ans = max(ans, maxi / (double) k);
	}
	cout.precision(9);
	cout << fixed << ans;
	// int curA = 0, curB = 0, m = n * 2;
	// for (int i = 1; i <= m; i++) {
	// 	was[i] = {curA, curB};
	// 	int right = i - k + 1, left = max(1, i - n + 1);
	// 	if (left <= right) {
	// 		double minFrac = INF, minX = 0, minY = 0;
	// 		double nxtA = curA + a[i], nxtB = curB + 1;
	// 		for (int j = left; j <= right; j++) {
	// 			double curFrac = was[j].first / was[j].second;
	// 		}
	// 	}
	// 	curA += a[i];
	// 	curB += 1;
	// }
	return 0;
}
