#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;
const ll BASE = 2017;
const int SZ = 1e6;

ll power[SZ], hash[SZ];

void precalc(string s) {
	power[0] = 1LL;
	int n = int(s.size());
	for (int i = 1; i <= n + 1; i++) {
		power[i] = power[i - 1] * BASE;
		power[i] %= MOD;
	}
}

void get_hash(string s) {
	hash[0] = ll(s[0] - 'a' + 1);
	for (int i = 1; i < n; i++) {
		hash[i] = hash[i - 1] * BASE + ll(s[i] - 'a' + 1);
		hash[i] %= MOD;
	}
}

ll get(int l, int r) {
	if (l == 0) {
		return hash[r];
	}
	return (hash[r] - hash[l - 1] * power[r - l + 1] % MOD + MOD) % MOD;
}

int main() {
	
	return 0;
}