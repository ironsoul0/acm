#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 1e2 + 7;
const double EPS = (double) 1e-6;
const int P = (int) 1e4 + 7;

#define fs first
#define sc second

int dp[N][P], p[N][P];
int w[N], c[N];

int main() {
	int n, s;
	cin >> n >> s;
	for (int i = 1; i <= n; i++) {
		cin >> w[i] >> c[i];	
	}	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= s; j++) {
			dp[i][j] = dp[i - 1][j];
			p[i][j] = j;
			if (j - w[i] >= 0) {
				if (dp[i - 1][j - w[i]] + c[i] > dp[i][j]) {
					dp[i][j] = dp[i - 1][j - w[i]] + c[i];
					p[i][j] = j - w[i];
				}
			}
		}
	}
	int index = 0;
	for (int i = 1; i <= s; i++)
		if (dp[n][i] > dp[n][index]) index = i;
	cout << dp[n][index] << '\n';
	vector<int> result;
	for (int i = n; i >= 1; i--) {
		int get_w = p[i][index];
		if (get_w != index)
			result.push_back(i);		
		index = get_w;
	}
	cout << result.size() << '\n';
	for (auto x : result)
		cout << x << ' ';
	return 0;	
}   