#include <bits/stdc++.h>
  
using namespace std;

/*
Ќужно найти самый длинный путь в ориентированном ациклическом графе.
*/

const int N = 1e5 + 100;

vector<vector<int> > g(N);
bool used[N];
vector<int> ans;

void dfs(int v) {
	used[v] = 1;
	for (int i = 0; i < int(g[v].size()); i++) {
		int to = g[v][i];
		if (!used[to]) {
			dfs(to);
		}
	}
	ans.push_back(v);
}

int main() {
	freopen("longpath.in", "r", stdin);
	freopen("longpath.out", "w", stdout);
	int n, m;
	cin >> n >> m;
	while(m--) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);          
	}
	int dp[n + 1];
	for (int i = 1; i <= n; i++) {
		dp[i] = 0;
		if (!used[i]) {
			dfs(i);
		}
	}	
	reverse(ans.begin(), ans.end());
	for (int i = 0; i < n; i++) {
		int cnt = ans[i], d = dp[cnt];
		int now = 0;
		for (int j = 0; j < int(g[cnt].size()); j++) {
			int to = g[cnt][j];
			dp[to] = max(dp[to], d + 1);
		}
	}
	int all = 0;
	for (int i = 1; i <= n; i++) {
		all = max(all, dp[i]);
	}
	cout << all;
	return 0;
}