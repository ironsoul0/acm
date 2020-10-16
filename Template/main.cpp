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
	int t;
	cin >> t;
	while (t--) {
		int n, x, a, b;
		cin >> n >> x >> a >> b;
		if (a > b) swap(a, b);
		int shift = min(x, a - 1);
		a -= shift;
		x -= shift;
		shift = min(x, n - b);
		b += shift;
		x -= shift;
		cout << b - a << endl;
	}
	return 0;
}
