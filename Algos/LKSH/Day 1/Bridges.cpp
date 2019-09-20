#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 1e6 + 7;
const double EPS = (double) 1e-6;

#define fs first
#define sc second

int in[N], up[N];
int used[N], timer = 0;
map<int, int> edge[N];
vector<int> b;
vector<vector<int>> g(N);

void bridge(int v, int u) {
	b.push_back(edge[v][u]);
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
			bridge(v, to);
		}	
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		edge[u][v] = edge[v][u] = i;
		g[u].push_back(v), g[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
		if (!used[i]) {
			dfs(i);
		}
	}
	cout << b.size() << '\n';
	sort(b.begin(), b.end());
	for (auto x : b)
		cout << x << ' ';
	return 0;	
}   