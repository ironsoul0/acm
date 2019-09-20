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
ƒарь€ обнаружила ошибку в своей программе, котора€ удал€ет все символы из строки кроме
У(Ф и У)Ф. ќказываетс€, некоторые символы замен€ютс€ на что-то нечитаемое.
“еперь еЄ заинтересовал вопрос, сколько различных правильных скобочных последовательностей
длины 2N могут €вл€тьс€ результатом исправленного алгоритма, то есть не будут противоречить
данным, которые она таки не потер€ла.

*/

const int MOD = 1e9 + 7;

int dp[2][15001];

int main() {
	freopen("recover.in", "r", stdin);
	freopen("recover.out", "w", stdout);

	char s[10001];
	scanf("%s", &s);
	int n = strlen(s), balance;
	if (n % 2 != 0) {
		balance = n / 2;
	} else {
		balance = n / 2 + 1;
	}

	dp[0][0] = 1;

	for (int i = 1; i <= n; ++i) {
		int idx = i % 2;
		for (int j = 0; j <= balance; j++) {
			dp[idx][j] = 0;
		}
		if (s[i - 1] == '(') {
			for (int j = 1; j <= balance; ++j) {
				dp[idx][j] = dp[idx ^ 1][j - 1];
			}						
		}
		if (s[i - 1] == ')') {
			for (int j = 0; j <= balance; ++j) {
				dp[idx][j] = dp[idx ^ 1][j + 1];
			}						
		}
		if (s[i - 1] == '?') {
			for (int j = 0; j <= balance; ++j) {
				dp[idx][j] = dp[idx ^ 1][j + 1];
				if (j > 0) {
					dp[idx][j] += dp[idx ^ 1][j - 1];
					dp[idx][j] %= MOD;
				}
			}			
		}
	}
	               
	printf("%d", dp[n % 2][0]);
	
	return 0;
}