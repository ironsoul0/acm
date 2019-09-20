#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 1e5 + 7;

/**
Есть две улитки, нужно построить два пореберно непересекающися пути.
Запустим нахождение максимального потока, где у всех ребер пропускная способность равна 1.

**/

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

int dfs(int v, int c_min) {
	if (v == t)
		return c_min;
	used[v] = 1;
	for (auto i : g[v]) {
		edge x = all[i];
		int to = x.to;
		if (!used[to] && x.f < x.c) {
			int delta = dfs(to, min(c_min, x.c - x.f));
			if (delta > 0) {
				all[i].f += delta;
				all[i ^ 1].f -= delta;
				return delta;
			}
		}	
	}
	return 0;
}

vector<int> path;

void find_path(int v) {
	path.push_back(v);
	if (v == t)
		return;
	for (auto i : g[v]) {
		if (all[i].f == 1) {
			all[i].f = 0;
			find_path(all[i].to);
			break;		
		}
	}	
}

void get_path(int v) {
	path.clear();
	find_path(v);
	for (auto x : path)
		cout << x << ' ';
	cout << '\n';
}

int main() {
	ios_base::sync_with_stdio(0);
	int n, m;
	cin >> n >> m >> s >> t;
	for (int i = 1; i <= m; i++) {
		int u, v, c = 1;
		cin >> u >> v;
		g[u].push_back(all.size());	
		all.push_back(edge(v, 0, c));
		g[v].push_back(all.size());
		all.push_back(edge(u, 0, 0));
	}
	dfs(s, INT_MAX);
	for (int i = 0; i < N; i++)
		used[i] = 0;
	dfs(s, INT_MAX);
	int flow = 0;
	for (auto x : g[s]) {
		if (x % 2 == 0 && all[x].f > 0)
			flow += all[x].f;	
	}
	if (flow != 2) {
		cout << "NO";
		exit(0);
	}
	cout << "YES\n";
	get_path(s), get_path(s);
	return 0;	
}