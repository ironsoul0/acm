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

int main() {
	ios_base::sync_with_stdio(0);
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
	int n;
	cin >> n;
	map<int, int> even, odd;
	odd[0] = 1;
	ll ans = 0;
	int cur = 0;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		cur ^= x;
		if (i & 1) {
			ans += odd[cur];
			odd[cur]++;
		} else {
			ans += even[cur];
			even[cur]++;
		}
	}
	cout << ans;
	return 0;
}