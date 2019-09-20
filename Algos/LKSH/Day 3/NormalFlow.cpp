#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 5e2 + 7;

#define fs first
#define sc second

struct edge {
	int to, f, c;
	edge(int _to, int _f, int _c) {
		to = _to, f = _f, c = _c;
	}
};

int used[N];
vector<vector<int>> g(N);
int s, t;
vector<edge> all;

int dfs(int v, int c_min, int it) {
	if (v == t)
		return c_min;
	used[v] = 1;
	for (auto i : g[v]) {
		edge x = all[i];
		int to = x.to;
		if (!used[to] && x.f < x.c && x.c - x.f >= it) {
			int delta = dfs(to, min(c_min, x.c - x.f), it);
			if (delta > 0) {
				all[i].f += delta;
				all[i ^ 1].f -= delta;
				return delta;
			}
		}	
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		g[u].push_back(all.size());	
		all.push_back(edge(v, 0, c));
		g[v].push_back(all.size());
		all.push_back(edge(u, 0, 0));
	}
	s = 1, t = n;
	int it = (1 << 30);
	while (it > 0) {
		for (int i = 0; i < N; i++)
			used[i] = 0;
		while (dfs(s, INT_MAX, it) > 0) {
			for (int i = 0; i < N; i++)
				used[i] = 0;	
		}
		it >>= 1;	
	}
	int64 flow = 0;
	for (auto i : g[s]) {
		if (i % 2 == 0) {
			flow += all[i].f;
		}	
	}
	cout << flow;
	return 0;	
}