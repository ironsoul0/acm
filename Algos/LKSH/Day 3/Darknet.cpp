#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 5e5 + 7;
const double EPS = (double) 1e-6;
const int P = (int) 1e4 + 7;
const int MOD = (int) 1e9 + 7;

/**
ѕосчитать количество вершин, через которые проход€т все пути из 1 в n ровно по одному разу.
—конденсируем граф, отдельно рассмотрим петли, посчитаем динамику дл€ каждой вершины в конденсированном графе.
 оличество путей из 1 в v, а втора€ динамика количество путей из v в n.
**/

#define fs first
#define sc second

int n, m, color = 0, timer = 0;
vector<int> order, path, s;
vector<vector<int>> g(N), rev(N);
vector<vector<int>> t(N), rt(N);
int used[N], x[N], cnt[N], cl[N], bad[N];
int dp_f[N], dp_s[N];
vector<int> result;

void prepare() {
	color = 0, timer = 0;
	order.clear(), path.clear(), s.clear();
	result.clear();
	for (int i = 0; i <= n; i++) {
		dp_f[i] = 0, dp_s[i] = 0;
		g[i].clear(), rev[i].clear(), t[i].clear(), rt[i].clear();
		used[i] = 0, x[i] = 0, cnt[i] = 0, cl[i] = 0, bad[i] = 0;
	}
}

void topsort(int v) {
	used[v] = 1;
	for (auto to : g[v]) {
		if (!used[to]) topsort(to);
	}
	order.push_back(v);
}

void scc(int v, int color) {
	cl[v] = color, x[color] = v, cnt[color]++;
	for (auto to : rev[v]) {
		if (!cl[to]) scc(to, color);
	}
}

void dfs(int v) {
	used[v] = 1;
	for (auto to : g[v]) {
		if (cl[to] != cl[v]) {
			t[cl[v]].push_back(cl[to]);
			rt[cl[to]].push_back(cl[v]);
		}
		if (!used[to]) {
			dfs(to);
		}
	}
}

void top_rev(int v) {
	used[v] = 1;
	for (auto to : t[v]) {
		if (!used[to])
			top_rev(to);
	}
	order.push_back(v);
}

void rev_top(int v) {
	used[v] = 1;
	for (auto to : rt[v]) {
		if (!used[to])
			rev_top(to);
	}
	order.push_back(v);
}

void traverse(int v = 1) {
	used[v] = 1;
	if (!bad[v] && cnt[cl[v]] == 1) {
		int value = (dp_f[cl[v]] * 1ll * dp_s[cl[v]]) % MOD;
		if (value == dp_f[cl[n]]) result.push_back(v);
	}
	for (auto to : g[v]) {
		if (!used[to]) traverse(to);
	}
}

void solve() {
	cin >> n >> m;
	prepare();
	while (m--) {
		int u, v;
		cin >> u >> v;
		if (u != v)
			g[u].push_back(v), rev[v].push_back(u);
		if (u == v)
			bad[u] = 1;
	}	
	for (int i = 1; i <= n; i++)
		if (!used[i]) topsort(i);
	while (order.size()) {
		if (!cl[order.back()]) {
			scc(order.back(), ++color);
		}	
		order.pop_back();
	}
	if (cl[1] == cl[n]) {
		cout << 0 << '\n';
		return;
	}
	for (int i = 1; i <= n; i++) {
		used[i] = 0;
	}
	for (int i = 1; i <= n; i++) {
		if (!used[i]) dfs(i);
	}
	for (int i = 1; i <= color; i++)
		used[i] = 0;
	for (int i = 1; i <= color; i++) {
		if (!used[i]) top_rev(i);
	}
	reverse(order.begin(), order.end());
	dp_f[cl[1]] = 1;
	for (int i = 0; i < (int) order.size(); i++) {
		int to = order[i];
		for (auto from : rt[to]) {
			dp_f[to] += dp_f[from];
			dp_f[to] %= MOD;
		}	
	}
	if (dp_f[cl[n]] == 0) {
		cout << 0 << '\n';
		return;
	}
	for (int i = 1; i <= color; i++)
		used[i] = 0;	
	order.clear();
	for (int i = 1; i <= color; i++)
		if (!used[i]) rev_top(i);
	reverse(order.begin(), order.end());
	dp_s[cl[n]] = 1;
	for (int i = 0; i < (int) order.size(); i++) {
		int to = order[i];
		for (auto from : t[to]) {
			dp_s[to] += dp_s[from];
			dp_s[to] %= MOD;
		}	
	}
	for (int i = 1; i <= n; i++)
		used[i] = 0;
	order.clear();
	traverse();
	cout << result.size() << '\n';
	for (auto x : result)
		cout << x << ' ';
	cout << '\n';	
}

int main() {     
	ios_base::sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}	
	return 0;	
}   