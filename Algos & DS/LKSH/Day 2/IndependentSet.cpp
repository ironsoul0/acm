#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 3e2 + 7;
const int P = (int) 1e2 + 7;
const double EPS = (double) 1e-6;

/**
Есть n девушек и m парней, взять некоторых девушек и парней, чтобы все были знакомы друг с другом.
Нужно найти независимое множество.

Независимое множество - множество, в которые входят все вершины кроме вершин из минимального покрытия.

Чтобы найти минимальное покрытие найдем максимальное паросочетание. Направим
ребра в графе, принадлежащие паросочетанию влево, остальные вправо. Запустим обход из вершин левой доли,
которые не принадлежат паросочетанию. Этим непосещенные вершины левой доли и посещенные вершины
правой доли являются минимальным покрытием.

Минимальное покрытие - множество вершин, что абсолютно все ребра инциденты хотя бы одной вершине из этого множества.
*//

int n, m;
vector<vector<int>> g(N);
int used[N], p[N];

bool help_kuhn(int v) {
	if (used[v])
		return false;	
	used[v] = 1;
	for (auto to : g[v]) {
		if (p[to] == -1 || help_kuhn(p[to])) {
			p[to] = v;
			return true;
		}
	}
	return false;
}

void build_graph() {
	for (int i = 0; i < N; i++)
		g[i].clear();
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		vector<int> girl;
		while (true) {
			int to;
			cin >> to;
			if (to > 0)
				girl.push_back(to);
			else
				break;
		}	
		for (int j = 1; j <= m; j++) {
			if (find(girl.begin(), girl.end(), j) == girl.end())
				g[i].push_back(j);
		}
	}	
}

vector<vector<int>> relax(N);
vector<int> mark;

void dfs(int v) {
	used[v] = 1;
	for (auto to : relax[v])
		if (!used[to]) dfs(to);
	mark.push_back(v);
}

void solve() {
	mark.clear();
	for (int i = 0; i < N; i++)
		p[i] = -1, relax[i].clear(), used[i] = 0;
	for (int i = 1; i <= n; i++) {
		help_kuhn(i);
		for (int j = 0; j < N; j++)
			used[j] = 0;
	}	
	set<pair<int, int>> edge;
	set<int> s;
	for (int j = 1; j <= m; j++) {
		if (p[j] != -1) s.insert(p[j]), edge.insert(make_pair(p[j], n + j));
	}
	for (int i = 1; i <= n; i++) {
		for (auto to : g[i]) {
			to += n;
			if (edge.count(make_pair(i, to))) {
				relax[to].push_back(i);
			} else {
				relax[i].push_back(to);
			}
		}
	}
	for (int i = 1; i <= n; i++)
		if (!used[i] && !s.count(i)) dfs(i);				
	vector<int> l, r, t;
	for (auto x : mark) {
		if (x <= n)
			l.push_back(x);
		else
			t.push_back(x - n);
	}
	for (int j = 1; j <= m; j++)
		if (find(t.begin(), t.end(), j) == t.end()) r.push_back(j);
	cout << l.size() + r.size() << '\n';
	cout << l.size() << ' ' << r.size() << '\n';
	for (auto x : l)
		cout << x << ' ';
	cout << '\n';
	for (auto x : r)
		cout << x << ' ';
	cout << '\n';	
}
         
int main() {
	freopen("birthday.in", "r", stdin);
	freopen("birthday.out", "w", stdout);
	int t;
	cin >> t;
	while (t--) {
		build_graph();
		solve();
	}		
	return 0;	
}   