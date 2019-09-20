#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

/**
Посетить n городов по одному разу за минимальное время
**/

const int N = (int) 18;
const int INF = (int) 1e9 + 7;

#define fs first
#define sc second

int a[N][N];
int dp[1 << N][N], p[1 << N][N];

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cin >> a[i][j];
	}
	int all = (1 << n);
	for (int i = 0; i <= all; i++)
		for (int j = 0; j < n; j++)
			dp[i][j] = INF;
	dp[1][0] = 0;
	for (int mask = 2; mask < all; mask++) {
		for (int j = 0; j < n; j++) {
			if (mask & (1 << j)) {
				int new_mask = (mask ^ (1 << j));
				for (int k = 0; k < n; k++) {
					if (new_mask & (1 << k)) {
						if (a[k][j] > 0) {
							int new_value = dp[new_mask][k] + a[k][j];
							if (dp[mask][j] > new_value) {
								dp[mask][j] = new_value;
								p[mask][j] = k;
							}
						}
					}
				}
			}
		}
	}
	int finish = 0;
	for (int i = 0; i < n; i++)
		if (dp[all - 1][i] < dp[all - 1][finish]) finish = i;
	if (dp[all - 1][finish] == INF) {
		cout << -1;
		exit(0);
	}
	cout << dp[all - 1][finish] << '\n';
	vector<int> path;
	int mask = all - 1;
	while (mask > 0) {
		path.push_back(finish);
		int last = finish;
		finish = p[mask][last];	
		mask ^= (1 << last);
	}
	reverse(path.begin(), path.end());
	for (auto x : path)
		cout << x + 1 << ' ';
	return 0;	
}