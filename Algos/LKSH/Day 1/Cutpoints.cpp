#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 1e6 + 7;
const double EPS = (double) 1e-6;

#define fs first
#define sc second

int in[N], up[N];
int used[N], timer = 0;
set<int> b;
vector<vector<int>> g(N);

void dfs(int v, int p = -1) {
	int child = 0;
	used[v] = 1;
	in[v] = up[v] = timer++;
	for (auto to : g[v]) {
		if (to == p) continue;
		if (used[to]) {
			up[v] = min(up[v], in[to]);
		} else {
			child++;
			dfs(to, v);
			up[v] = min(up[v], up[to]);
			if (up[to] >= in[v] && p != -1) {
				b.insert(v);
			}
		}	
	}
	if (p == -1 && child > 1)
		b.insert(v);
}

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v), g[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
		if (!used[i]) {
			dfs(i);
		}
	}
	cout << b.size() << '\n';
	for (auto x : b)
		cout << x << ' ';
	return 0;	
}   