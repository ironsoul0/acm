#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 1e3 + 7;
const int INF = (int) 1e9 + 7;

#define fs first
#define sc second

/**
Можно удалить некоторые ребра из дерева, дерево распадается на компоненты связности. Требуется удалить
наименьшее количество ребер, чтобы осталось поддерево размером p.

Считаем динамику на дереве: dp[v][j] - минимальное количество ребер, которое нужно удалить в поддереве вершины v, чтобы
осталась компонента размером j с корнем в вершине v.

Будем использовать рюкзак и наилучшим образом набирать вес j через наших сыновей.

DP on Tree.	
**/

int dp[N][N], all[N], d[N][N];
vector<vector<int>> g(N);

void calc_dp(int v, int son, int s, int p) {
	for (int i = 0; i <= son; ++i)
		for (int j = 0; j <= s; ++j)
			d[i][j] = INF;     
	int i = 0;
	d[0][1] = 0;
	i = 0;
	for (auto to : g[v]) {
		if (to == p) continue;
		++i;
		for (int j = 1; j <= s; ++j) {
			d[i][j] = d[i - 1][j] + 1;
			for (int k = 1; k <= all[to] && j - k >= 0; ++k) {
				d[i][j] = min(d[i][j], d[i - 1][j - k] + dp[to][k]);
			}
			if (i == son)
				dp[v][j] = d[i][j];
		}
	}
}

void dfs(int v = 1, int p = -1) {
	int son = 0;
	all[v] = 1;
	for (auto to : g[v]) {
		if (to == p) continue;
		dfs(to, v);
		son++;
		all[v] += all[to];
	}
	if (son == 0) {
		dp[v][1] = 0;		
	} else {
		calc_dp(v, son, all[v], p);	
	}
}

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].push_back(v), g[v].push_back(u);
	}
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			dp[i][j] = INF;
	dfs();
	int ans = INF;
	for (int i = 1; i <= n; ++i) {
		if (i != 1)
			ans = min(ans, dp[i][k] + 1);
		else
			ans = min(ans, dp[i][k]);
	}
	printf("%d", ans);	
	return 0;	
}  