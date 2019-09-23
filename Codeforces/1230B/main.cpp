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
	int n, k;
	string s;
	cin >> n >> k >> s;
	if (s.size() == 1) {
		if (k == 1) cout << 0; else cout << s;
		return 0;
	}
	if (s[0] != '1' && k != 0) {
		s[0] = '1';
		k--;
	}
	for (int i = 1; i < n && k > 0; i++) {
		if (s[i] != '0') {
			s[i] = '0';
			k--;
		}
	}
	cout << s;
	return 0;
}