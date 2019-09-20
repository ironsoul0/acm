#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 3e5 + 7;
const double EPS = (double) 1e-6;

#define fs first
#define sc second

////SOME MAGIC GOES HERE....

int u[N], v[N];
int* g[N];
int sz[N];
int pos[N];

const int SIZE = (1 << 24);
int64 value[SIZE];

int nextValue(int x) {
	return (x + 179239) & (SIZE - 1);
}

void add(int64 x) {
	int y = (x ^ (x >> 10) ^ 0xDEADBEEF) & (SIZE - 1);
	while (value[y] != 0) y = nextValue(y);
	value[y] = x;
}

bool have(int64 x) {
	int y = (x ^ (x >> 10) ^ 0xDEADBEEF) & (SIZE - 1);
	while (value[y] != 0 && value[y] != x) y = nextValue(y);
	return value[y] == x;
}

int64 hashEdge(int u, int v, int shift) {
	++u, ++v;
	if (u > v) swap(u, v);
	return ((int64) u << shift) + v;
}

int main() {
	int n, m;
	cin >> n >> m;
	int myLog = 1;
	while ((1 << myLog) <= n) ++myLog;
	for (int i = 0; i < m; i++) {
		cin >> u[i] >> v[i];
		--u[i], --v[i];
		++sz[u[i]], ++sz[v[i]];
	}
	for (int i = 0; i < n; i++) {
		g[i] = (int*) malloc(sz[i] * sizeof(int));
	}
	for (int i = 0; i < m; i++) {
		g[u[i]][pos[u[i]]] = v[i], ++pos[u[i]];
		g[v[i]][pos[v[i]]] = u[i], ++pos[v[i]];
	}
	for (int i = 0; i < n; i++) {
		if (sz[i] > 0) sort(g[i], g[i] + sz[i]);
	}
	int res = 0;
	for (int i = 0; i < m; i++)
		add(hashEdge(u[i], v[i], myLog));
	for (int i = 0; i < m; i++) {
		int uu = u[i], vv = v[i];
		if (sz[uu] < sz[vv]) swap(uu, vv);
		int mx = min(uu, vv);
		for (int j = 0; j < sz[vv] && g[vv][j] < mx; ++j) {
			if (have(hashEdge(uu, g[vv][j], myLog))) ++res;
		}	
	}
	cout << res;
	return 0;	
}     