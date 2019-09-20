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

vector<vector<int> > g(N);

int tin[N], fup[N], timer = 0;
int used[N];
map<pair<int, int>, int> cnt;
set<pair<int, int> > bridges;

void is_bridge(int u, int v) {
	if (cnt[mp(u, v)] == 1) {
		bridges.insert(mp(u, v));
		bridges.insert(mp(v, u));
	}
}

void dfs(int v, int p = -1) {
	tin[v] = fup[v] = timer++;
	used[v] = 1;
	for (auto to : g[v]) {
		if (to == p) continue;
		if (used[to]) {
			fup[v] = min(fup[v], tin[to]);
		} else {
			dfs(to, v);
			fup[v] = min(fup[v], fup[to]);
			if (fup[to] > tin[v])
				is_bridge(v, to);
		}
	}				
}

int main() {
	fast_io;
	int n, m;
	cin >> n >> m;
	vector<pair<int, int> > edge;
	while(m--) {
		int u, v;
		cin >> u >> v;
		edge.pb(mp(u, v));
		cnt[mp(u, v)]++, cnt[mp(v, u)]++;
		g[u].pb(v), g[v].pb(u);
	}								 
	for (int i = 1; i <= n; i++) {
		if (!used[i])
			dfs(i);
	}
	vector<int> ans;
	for (int i = 0; i < sz(edge); i++) { 
		if (bridges.count(edge[i])) ans.pb(i + 1);
	}
	cout << sz(ans) << '\n';
	for (auto x : ans)
		cout << x << ' ';
	return 0;
} 