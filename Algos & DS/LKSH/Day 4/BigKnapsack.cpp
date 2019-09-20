#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 1e2 + 7;
const double EPS = (double) 1e-6;
const int P = (int) 1e4 + 7;
const int INF = (int) 1e9 + 7;

/**
Обычный рюкзак, но допустимый суммарный вес около 10^9. 
Однако, суммарная стоимость предметов не превышаем 10^4.
Поэтому заведем динамику dp[i][j] - минимальный вес, чтобы с помощью первых i предметов насобирать ценность j.
**/

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
	for (int i = 0; i < N; i++)
		for (int j = 0; j < P; j++)
			dp[i][j] = INF;
	for (int i = 0; i < N; i++)
		dp[i][0] = 0;	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < P; j++) {
			dp[i][j] = dp[i - 1][j];
			p[i][j] = j;
			if (j - c[i] >= 0) {
				int value = dp[i - 1][j - c[i]] + w[i];
				if (value < dp[i][j]) {
					dp[i][j] = value;
					p[i][j] = j - c[i];
				}
			}
		}
	}
	int index = 0;
	for (int j = 0; j < P; j++) {
		if (dp[n][j] <= s) {
			index = j;	
		}
	}
	cout << index << '\n';
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