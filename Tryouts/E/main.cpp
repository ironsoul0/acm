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

typedef unsigned long long ll;
typedef pair<int, int> pii;

const int MOD = (int) 1e9 + 7;
const int N = (int) 31;
const ll INF = (ll) 1e18 + 7;

int main() {
	ios_base::sync_with_stdio(0);
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
	int n;
	cin >> n;
	vector<int> l(n);
	for (int i = 0; i < n; i++) {
		cin >> l[i];
	}
	for (int k = 2; k <= n; k++) {
		if (n % k) continue;
		int divs = n / k;
		unordered_map<int, int> rems;
		for (auto x : l) {
			rems[x % k]++;
		}
		bool valid = true;
		for (int i = 0; i < k; i++) {
			if (rems[i] != divs) {
				valid = false;
			}
		}
		if (valid) {
			cout << k;
			return 0;
		}
	}
	cout << -1;
	return 0;
}