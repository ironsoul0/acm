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
	string s;
	cin >> n >> s;
	ll all = n * 1ll * (n + 1) / 2, bad = 0;
	s = "#" + s;
	int last_a = 0, last_b = 0;
	for (int i = 1; i <= n; i++) {
		if (s[i] == 'A') {
			if (s[i - 1] != 'A') {
				bad += i - last_a;
			} else {
				bad++;
				if (last_b > 0) bad++;
			}
			last_a = i;
		} else {
			if (s[i - 1] != 'B') {
				bad += i - last_b;
			} else {
				bad++;
				if (last_a > 0) bad++;
			}
			last_b = i;
		}
	}	
	cout << all - bad;
	return 0;
}