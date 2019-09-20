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
const int BASE = 31;
const int N = (int) 1e6 + 7;
 
void print(vector<pair<int, int>>& res) {
	cout << res.size() << endl;
	for (auto x : res) {
		cout << x.first + 1 << ' ' << x.second + 1 << endl;
	}
	exit(0);
}
 
int main() {
	ios_base::sync_with_stdio(0);
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif			
	int n;
	string s, t;
	cin >> n >> s >> t;
	vector<int> firstB, firstA;
	for (int i = 0; i < n; i++) {
		if (s[i] == 'a' && t[i] == 'b') {
			firstA.push_back(i);
		}
		if (s[i] == 'b' && t[i] == 'a') {
			firstB.push_back(i);
		}
	}
	vector<pair<int, int>> res;
	for (int i = 0; i < (int) firstA.size(); i += 2) {
		if (i + 1 < (int) firstA.size())
			res.push_back({firstA[i], firstA[i + 1]});
	}
	for (int i = 0; i < (int) firstB.size(); i += 2) {
		if (i + 1 < (int) firstB.size())
			res.push_back({firstB[i], firstB[i + 1]});
	}
	if (firstA.size() % 2 == firstB.size() % 2) {
		if (firstA.size() % 2 == 0) print(res);
		res.push_back({firstA.back(), firstA.back()});
		res.push_back({firstA.back(), firstB.back()});
		print(res);
	}
	cout << -1;
	return 0;
}