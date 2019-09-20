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
������ �������� ���������, ��������� �� ������ ��� ������� ����� �(� � �)�. ������ � ��-
����������� ������, ������� ��������� ���������� ��������� ������������������� ����� 2n ���
����� ��������.
��������, ��� ������ �� ������������ ���������� ��������� ���� ��������� ������ �� ���-
������� �������������� ����������, ������������ ����������� ������ � ������� ���������� �
�������� k.
*/

const int MOD = 1e9 + 7;

int dp[150][150];

void zero() {
	for (int i = 0; i < 150; i++) {
		for (int j = 0; j < 150; j++) {
			dp[i][j] = 0;
		}
	}
}

int dynamic(int n, int k) {
	zero();
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= k; j++) {
			dp[i][j] = dp[i - 1][j + 1];
			if (j > 0) {
				dp[i][j] += dp[i - 1][j - 1];
				dp[i][j] %= MOD;
			}
		}
	}
	return dp[n][0];
}

int main() {
	freopen("deep.in", "r", stdin);
	freopen("deep.out", "w", stdout);

	int n, k;
	cin >> n >> k;
	cout << (dynamic(n * 2, k)  - dynamic(n * 2, k - 1) + MOD) % MOD;
	
	return 0;
}