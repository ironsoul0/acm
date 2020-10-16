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
const int N = (int) 1e5 + 7;
const ll INF = (ll) 1e18 + 7;

int fit[N], sp[N], now[N], was[N];
vector<vector<pair<int, int>>> restrict[N];

int main() {
	ios_base::sync_with_stdio(0);
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++) {
		cin >> fit[i] >> sp[i];
	}
	int r;
	cin >> r;
	for (int i = 1; i <= r; i++) {
		int fitID, numSp;
		cin >> fitID >> numSp;
		for (int j = 1; j <= numSp; j++) {
			cin >> now[j];
		}	
		int limit;
		cin >> limit;
		restrict[fitID].push_back({});
		for (int j = 1; j <= numSp; j++) {
			restrict[fitID].back().push_back(make_pair(now[j], limit));
		}
	}
	int q;
	cin >> q;
	for (int i = 1; i <= q; i++) {
		int x;
		cin >> x;
		if (was[x]) {
			cout << "no\n";
			continue;
		}
		was[x] = true;
		bool valid = false;
		for (auto &rule : restrict[fit[x]]) {
			for (auto &fitInfo : rule) {
				if (fitInfo.first == sp[x]) {
					if (fitInfo.second > 0) {
						valid = true;
						for (auto &x : rule) {
							x.second--;
						}
					} else if (fitInfo.second == -1) {
						valid = true;
					} 
				}
			}
		}
		if (valid) {
			cout << "yes\n";
		} else {
			cout << "no\n";
		}
	}
	return 0;
}
