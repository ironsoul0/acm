#include <bits/stdc++.h>

typedef long long int64;

using namespace std;

const int N = (int) 2e5 + 7;
const int K = 26;
const int LOG = 20;

int n, c[N], p[N], h[N], np[N], nc[N], k;
int len[N], e[N], lcp[N];

int get(int x) {
	x %= n;
	if (x < 0) x += n;
	return x;
}

bool equals(int i, int j) {
	int x = get(i + (1 << (k - 1))), y = get(j + (1 << (k - 1)));
	return c[i] == c[j] && c[x] == c[y];
}

int main() {
	ios_base::sync_with_stdio(0);
	vector<pair<int, int>> v;
	string s;
	cin >> s;
	s += '#';
	n = s.length();
	for (int i = 0; i < n; ++i) {
		v.push_back(make_pair(s[i] - 'a', i));
	}
	sort(v.begin(), v.end());
	int z = 0;
	h[0] = 0;
	for (int i = 0; i < n; ++i) {
		if (i > 0 && v[i].first != v[i - 1].first) {
			z++;
			h[z] = i;
		}
		c[v[i].second] = z;
		p[i] = v[i].second;
	}
	for (int w = 1; w < LOG && z < n; ++w) {
		k = w;
		for (int i = 0; i < n; ++i) {
			int v = get(p[i] - (1 << (k - 1)));
			np[h[c[v]]++] = v;
		}
		z = 0;
		nc[np[0]] = 0;
		h[0] = 0;
		for (int i = 1; i < n; ++i) {
			if (!equals(np[i], np[i - 1])) {
				z++;
				h[z] = i;
			}
			nc[np[i]] = z;
		}
		for (int i = 0; i < n; i++)
			p[i] = np[i], c[i] = nc[i];
	}
	n--;
	for (int i = 0; i < n; i++) {
		p[i] = p[i + 1];
	}
	p[n] = 0;
	s.pop_back();
	int64 kth;
	cin >> kth;
    int r = 0;
	for (int i = 0; i < n; i++) {
		e[p[i]] = i;
	}
	for (int i = 0; i < n; i++) {
		len[i] = n - p[i];
	}
	for (int i = 0; i < n; i++) {
		if (e[i] == n - 1)
			continue;
		while (i + r < n && s[get(i + r)] == s[get(p[e[i] + 1] + r)])
			r++;
		lcp[e[i]] = r;
		r = max(0, r - 1);
	}
	if (len[0] >= kth) {
		cout << s.substr(0, kth);
		return 0;
	}
	kth -= len[0];
	for (int i = 1; i < n; ++i) {
		if (kth <= len[i] - lcp[i - 1]) {
			cout << s.substr(p[i], kth + lcp[i - 1]);
			return 0;
		}
		else {
			kth -= (len[i] - lcp[i - 1]);
		}
	}
	cout << s.substr(p[n - 1], len[n - 1]);
	return 0;
}