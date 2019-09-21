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

const int MOD = (int) 2e9 + 7;
const int N = (int) 1e6 + 7;
const ll INF = (ll) 1e18 + 7;

ll gcd (ll a, ll b) {
	if (b == 0)
		return a;
	else
		return gcd (b, a % b);
}

int calc(int x) {
	int ans = 0;
	while (x) {
		ans++;
		x /= 10;
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
	int q;
	cin >> q;
	vector<pair<int, int>> query;
	for (int i = 0; i < q; i++) {
		int k;
		cin >> k;
		query.push_back(make_pair(k, i));
	}
	vector<int> ans(q);
	sort(query.begin(), query.end());
	int cur_num = 0, digits_passed = 0, reach_max = 1, last_num = 0;
	for (int i = 0; i < q; i++) {
		while (digits_passed < query[i].first) {
			cur_num++;
			//cout << cur_num << endl;
			digits_passed += calc(cur_num);
			last_num = cur_num;
			if (cur_num == reach_max) {
				cur_num = 0;
				reach_max++;
			}
		}
		int index = calc(last_num) - (digits_passed - query[i].first) - 1;
		//cout << last_num << ' ' << digits_passed << ' ' << calc(last_num) << endl;
		string kek = to_string(last_num);
		ans[query[i].second] = kek[index] - '0';
	}
	for (int i = 0; i < q; i++)
		cout << ans[i] << '\n';
	return 0;
}