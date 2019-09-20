#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

///Даны две строки. требуется найти их НОП

const ll BASE1 = 2017;
const ll BASE2 = 107;
const ll MOD1 = 1e9 + 7;
const ll MOD2 = 2e9 + 7;

const int SIZE = 30001;

ll prefix1[SIZE], power1[SIZE], prefix2[SIZE], power2[SIZE];
string a, b;

void get_hash(string &s) {	
	prefix1[0] = prefix2[0] = ll(s[0] - 'a' + 1);
	int n = int(s.size());
	for (int i = 1; i < n; i++) {
		prefix1[i] = ((ll)prefix1[i - 1] * BASE1 + ll(s[i] - 'a' + 1)) % MOD1;
		prefix2[i] = ((ll)prefix2[i - 1] * BASE2 + ll(s[i] - 'a' + 1)) % MOD2;
	}
}

void calc_pow(int n) {
	power1[0] = power2[0] = 1LL;
	for (int i = 1; i <= n; i++) {
		power1[i] = ((ll)power1[i - 1] * BASE1) % MOD1;
		power2[i] = ((ll)power2[i - 1] * BASE2) % MOD2;
	}
}

pair<ll, ll> get_segment(int l, int r) {
	int len = r - l + 1;
	ll fst = ((prefix1[r] - (ll)prefix1[l - 1] * power1[len]) % MOD1 + MOD1) % MOD1;
	ll snd = ((prefix2[r] - (ll)prefix2[l - 1] * power2[len]) % MOD2 + MOD2) % MOD2;
	return make_pair(fst, snd);
}

bool possible(int len) {
	for (int i = 0; i < SIZE; i++) {
		prefix1[i] = 0LL;
		prefix2[i] = 0LL;
	}
	int n = int(a.size()), m = int(b.size());
	if (len > n || len > m) {
		return 0;
	}
	set<pair<ll, ll> > q;
	get_hash(b);
	for (int l = 0; l <= n - len; l++) {
		int r = l + len - 1;
		q.insert(get_segment(l, r));		
	}
	get_hash(a);
	for (int l = 0; l <= n - len; l++) {
		int r = l + len - 1;
		if (q.count(get_segment(l, r))) {
			return 1;
		}
	}
	return 0;
}

int main() {
	cin >> a >> b;
	int n = int(a.size()), m = int(b.size());
	int mx = max(n, m) + 1;
	calc_pow(mx);
	int l = 0, r = min(n, m) + 1, ans = 0;
	while(r - l > 1) {
		int mid = (r + l) >> 1;
		if (possible(mid)) {
			l = mid;
			ans = max(ans, mid);
		} else {
			r = mid;
		}
	}		
	cout << ans;
	return 0;
}