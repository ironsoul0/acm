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
Посчитайте количество правильных скобочных последовательностей длины 2N (N открываю-
щихся скобок и N закрывающихся), составленных из круглых и квадратных скобок так, что внутри
любой пары круглых скобок нет квадратных скобок
*/

const ll MOD = 1e9 + 7;

ll C[1001], D[1001];

ll K(int n) {
	ll res = 0;
	for (int i = 0; i < n; i++) {
		res += C[i] * C[n - i - 1];
		res %= MOD;
	}
	return res;
}

ll A(int n) {
	ll res = 0;
	for (int i = 0; i < n; i++) {
		res += D[i] * D[n - i - 1];
		res %= MOD;
		res += C[i] * D[n - i - 1];
		res %= MOD;
	}
	return res;
}

int main() {
	freopen("quant.in", "r", stdin);
	freopen("quant.out", "w", stdout);
	
	C[0] = 1LL * 1;
	int n;

	cin >> n;
	
	for (int i = 1; i <= 1000; ++i) {
		C[i] = K(i);
	}
	
	D[0] = 1LL * 1;

	for (int i = 1; i <= n; ++i) {
		D[i] = A(i);
	} 

	cout << D[n];

	return 0;
}                    