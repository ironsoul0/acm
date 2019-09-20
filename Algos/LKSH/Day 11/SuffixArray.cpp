#include <bits/stdc++.h>

typedef long long int64;

using namespace std;

const int N = (int) 4e5 + 7;
const int K = 26;
const int LOG = 20;

int n, c[N], p[N], h[N], np[N], nc[N], k;

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
	for (int i = 0; i < n; i++)
		cout << p[i] + 1 << ' ';
	return 0;
}