#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 2e4 + 7;
const double EPS = (double) 1e-6;

///Требуется найти компоненты реберной двусвязности, достаточно удалить все мосты и посчитать компоненты связности в новом графе

#define fs first
#define sc second

int in[N], up[N];
int used[N], timer = 0;
vector<vector<int>> g(N);
map<int, int> ban[N], cnt[N];
int color[N], cur_color = 0;

void modify(int v) {
	color[v] = cur_color;
	used[v] = 1;
	for (auto to : g[v]) {
		if (!ban[v][to] && !used[to])
			modify(to);
	}
}

void ban_edge(int v, int u) {
	if (cnt[v][u] == 1) {
		ban[v][u] = ban[u][v] = 1;
	}
}

void dfs(int v, int p = -1) {
	used[v] = 1;
	in[v] = up[v] = timer++;
	for (auto to : g[v]) {
		if (to == p) continue;
		if (used[to]) {
			up[v] = min(up[v], in[to]);
		} else {
			dfs(to, v);
			up[v] = min(up[v], up[to]);
		}	
		if (up[to] > in[v]) {
			ban_edge(v, to);
		}
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v), g[v].push_back(u);
		cnt[u][v]++, cnt[v][u]++;
	}
	for (int i = 1; i <= n; i++) {
		if (!used[i]) {
			dfs(i);
		}
	}	
	for (int i = 1; i <= n; i++) {
		used[i] = 0;
	}
	for (int i = 1; i <= n; i++) {
		if (!used[i]) {
			cur_color++;
			modify(i);
		}	
	}
	cout << cur_color << '\n';
	for (int i = 1; i <= n; i++) {
		cout << color[i] << ' ';
	}
	return 0;	
}   