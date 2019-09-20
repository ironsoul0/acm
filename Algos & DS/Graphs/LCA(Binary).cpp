#include <bits/stdc++.h>
 
using namespace std;
 
#define fast_io ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define gold_on_respa 0
 
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define freopen(x) freopen(x".in", "r", stdin), freopen (x".out", "w", stdout);
#define ex exit(0)

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
 
typedef long long ll;
typedef pair<int, int> pii;

const int N = (int) 1e6 + 7; 
const ll MOD = (ll) 1e9 + 7;
const int INF = (int) 2e9;
const ll BIG = 1e18;
const int LG = 32;

int n;
vector<vector<int> > g(N);
int tin[N], tout[N], timer = 0;
int up[N][LG];

void dfs(int v = 1, int p = 1) {
	tin[v] = timer++;
	up[v][0] = p;
	for (int i = 1; i < LG; i++)
		up[v][i] = up[up[v][i - 1]][i - 1];
	for (auto to : g[v]) {
		if (to == p) continue;
		dfs(to, v);
	}
	tout[v] = timer++;
}

bool is_ancestor(int a, int b) {
	return (tin[a] <= tin[b] && tout[a] >= tout[b]);
}

int lca(int a, int b) {
	if (is_ancestor(a, b)) return a;
	if (is_ancestor(b, a)) return b;
	for (int i = LG - 1; i >= 0; i--) {
		if (!is_ancestor(up[a][i], b))
			a = up[a][i];
	}
	return up[a][0];
}

int main() {
	fast_io;
	int n;
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	dfs();
	int q;
	cin >> q;
	while(q--) {
		int a, b;
		cin >> a >> b;
		cout << lca(a, b) << '\n'; 
	}			
	return 0;
}
      