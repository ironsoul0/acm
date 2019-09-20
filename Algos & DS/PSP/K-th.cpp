#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

const int INF = 2e9;
const int SIZE = 2e5;

#define sz(s) int(s.size())

#define pii pair<int, int>

#define mp make_pair
#define pb push_back

#define fi first
#define se second

#define all(c) c.begin(), c.end()

/*
Помогите Генриетте написать программу, генерирующую k-ю в лексикографическом порядке
правильную скобочную последовательность, состоящую из 2n скобок.
*/

ll dp[150][150];

int main() {
	freopen("build.in", "r", stdin);
	freopen("build.out", "w", stdout);
	
	int n;
	ll k;

	cin >> n >> k;

	dp[0][0] = 1LL * 1;

	for (int i = 1; i <= n * 2; i++) {
		for (int j = 0; j <= n; j++) {
			dp[i][j] = dp[i - 1][j + 1];
			if (j > 0) {
				dp[i][j] += dp[i - 1][j - 1];
			}
		}			
	}

	string ans = "(";
	int part = 1, balance = 1;

	while(part != n * 2) {
		if (dp[n * 2 - part - 1][balance + 1] >= k) {
			ans += '(';
			++balance;	
		} else {
			k -= dp[n * 2 - part - 1][balance + 1];
			ans += ')';
			--balance;
		}
		++part;
	}

	cout << ans;

	return 0;
}    