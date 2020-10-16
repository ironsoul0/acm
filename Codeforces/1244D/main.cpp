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
const int N = (int) 2e5 + 7;
const ll INF = (ll) 1e18 + 7;

int n;
ll a[N][4];
int final[N];

vector<int> g[N], order;

void dfs(int v, int p = -1) {
	if (g[v].size() > 2) {
		cout << -1;
		exit(0);
	}
	order.push_back(v);
	for (auto to : g[v]) {
		if (to == p) continue;
		dfs(to, v);
	}
}

class Solution {
	int height;

public:
	int getHeight() {
		return height;
	}

	void increaseByOne() {
		height += 1;
	}
};

bool canTake(int cokes) {
	int result = 0;
	for (int amount : amounts) {
		if (amount >= cokes) {
			result++;
		}
	}
	return result >= cokes / 2;
}

void find() {
	int left = 1, right = n, bestTake = 0;
	while (left <= right) {
		int middle = (left + right) / 2;
		if (canTake(middle)) {
			bestTake = middle;
			left = middle + 1;
		} else {
			right = middle - 1;
		}
	}
}

class Solution {
	int amount;
	vector<int> array;h

public:
	void push(int x, int y, int z) {

	}



private:

};

int main() {
	ios_base::sync_with_stdio(0);
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
	Solution *s = new Solution();
	cout << s->getHeight();
	return 0;
	// cin >> n;
	// for (int j = 1; j <= 3; j++) {
	// 	for (int i = 1; i <= n; i++) {
	// 		cin >> a[i][j];
	// 	}
	// }
	// for (int i = 0; i < n - 1; i++) {
	// 	int u, v;
	// 	cin >> u >> v;
	// 	g[v].push_back(u);
	// 	g[u].push_back(v);
	// }
	// int leaf = 0;
	// for (int i = 1; i <= n; i++) {
	// 	if (g[i].size() == 1) leaf = i;
	// }
	// dfs(leaf);
	// vector<int> color = {1, 2, 3};
	// ll ans = LLONG_MAX;
	// vector<int> res;
	// do {
	// 	ll cur = 0ll;
	// 	int i = 0;
	// 	for (auto v : order) {
	// 		cur += a[v][color[i % 3]];
	// 		i++;
	// 	}
	// 	if (cur < ans) {
	// 		ans = cur;
	// 		res = color;
	// 	}
	// } while (next_permutation(color.begin(), color.end()));
	// cout << ans << '\n';
	// for (int i = 0; i < order.size(); i++) {
	// 	final[order[i]] = res[i % 3];
	// }
	// for (int i = 1; i <= n; i++) {
	// 	cout << final[i] << ' ';
	// }
	return 0;
}