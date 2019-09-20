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

const int M = 2049;

ll a[N], b[N];
ll dp[N][3];

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
	int half = n / 2;
	int sumF = 0, numF = 0, sumS = 0, numS = 0;
	for (int i = 0; i < half; i++) {
		if (s[i] != '?') {
			sumF += s[i] - '0';
			numF++;
		}
	}
	for (int i = half; i < n; i++) {
		if (s[i] != '?') {
			sumS += s[i] - '0';
			numS++;
		}
	}
	
	return 0;
}