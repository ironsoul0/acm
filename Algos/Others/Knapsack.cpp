#include <bits/stdc++.h>
  
using namespace std;

int main() {
	int s, n;
	cin >> s >> n;
	int dp[n + 1][s + 1], a[n + 1]; ///ןונגûו i ןנוהלועמג. נ‏ךחאך גלוסעטלמסעט j
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= s; j++) {
			if (j >= a[i]) {
				int cost = a[i];
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - cost] + cost);	
			} else {
				dp[i][j] = dp[i - 1][j];
			}
		}
	}
	cout << dp[n][s];
	return 0;
}

