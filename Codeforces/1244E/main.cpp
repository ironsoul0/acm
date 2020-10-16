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

int n;
ll k;
map<int, int> cnt;

int main() {
	ios_base::sync_with_stdio(0);
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		cnt[x]++;
	}
	while (cnt.size() > 1) {
		auto it = cnt.begin(), nxt = it;
		nxt++;
		ll num_x = it->second, x = it->first, y = nxt->first;
		ll diff = y - x;
		ll t = min(diff, k / num_x);
		
		auto it2 = --cnt.end(), prev = it2;
		prev--;
		ll num_x2 = it2->second, x2 = it2->first, y2 = prev->first;
		ll diff2 = x2 - y2;
		ll t2 = min(diff2, k / num_x2);

		if (t == 0 && t2 == 0) break;

		if (t > t2) {
			cnt.erase(x);
			cnt[x + t] += num_x;
			k -= num_x * t;
		} else {
			cnt.erase(x2);
			cnt[x2 - t2] += num_x2;
			k -= num_x2 * t2;
		}
	}
	cout << ((--cnt.end())->first) - (cnt.begin()->first);
	return 0;
}