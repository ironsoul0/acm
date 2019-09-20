#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 3e2 + 7;
const int INF = (int) 7e7 + 7;
const int MOD = (int) 1e9 + 7;

/**
Есть n человек и m сортов чая. 
Количество чая сорта i равно a_i.
Каждый сотрудник любит некоторые сорты чая.
Каждый день сотрудник пьет по одному любимому чаю.
Найти максимальное количество дней, когда все смогут пить свой любимый чай

Создаем фиктивный исток и соединяем с чаем, на ребрах пишем количество этого чая
Каждый чай соединяем с теми кто, его любит и пишем на ребрах бесконечность.

Бинарным поиском перебираем вес ребра, которым мы соединим всех сотрудников с фиктивным стоком, если весь возможный чай придет в сток, то
увеличим левую границу и попрубуем найти ответ побольше 
**/

#define fs first
#define sc second

struct edge {
	int to, f, c;
	edge(int _to, int _f, int _c) {
		to = _to, f = _f, c = _c;
	}
};

int used[N], a[N];
vector<vector<int>> b(N);
vector<vector<int>> g(N);
vector<edge> all;
int n, m, s, t;

int dfs(int v, int c_min, int it) {
	if (v == t)
		return c_min;
	used[v] = 1;
	for (auto i : g[v]) {
		edge x = all[i];
		int to = x.to;
		if (!used[to] && x.f < x.c && x.c - x.f >= it) {
			int delta = dfs(to, min(c_min, x.c - x.f), it);
			if (delta > 0) {
				all[i].f += delta;
				all[i ^ 1].f -= delta;
				return delta;
			}
		}	
	}
	return 0;
}

void build() {
	for (int i = 1; i <= m; i++) {
		g[s].push_back(all.size());
		all.push_back(edge(i, 0, a[i]));
		g[i].push_back(all.size());
		all.push_back(edge(s, 0, 0));	
	}	 
	for (int i = 1; i <= n; i++) {
		for (auto x : b[i]) {
			int to = i + m;
			g[x].push_back(all.size());
			all.push_back(edge(to, 0, MOD));
			g[to].push_back(all.size());
			all.push_back(edge(x, 0, 0));	
		}
	}
}

bool valid(int x) {
	for (int i = 0; i < N; i++)
		g[i].clear();
	all.clear();
	build();
	s = 0;
	t = n + m + 1;
	for (int i = 1; i <= n; i++) {
		int v = i + m;
		g[v].push_back(all.size());
		all.push_back(edge(t, 0, x));
		g[t].push_back(all.size());
		all.push_back(edge(v, 0, 0));
	}
	for (int i = 0; i < N; i++)
		used[i] = 0;	
	int it = (1 << 30);
	while (it > 0) {
		for (int i = 0; i < N; i++)
			used[i] = 0;
		while (dfs(s, INT_MAX, it) > 0) {
			for (int i = 0; i < N; i++)
				used[i] = 0;	
		}
		it >>= 1;	
	}
	int flow = 0;
	for (auto x : all) {
		if (x.to == t && x.f > 0)
			flow += x.f;
	}
	return flow == n * x;
}

int main() {
	freopen("tea.in", "r", stdin);
	freopen("tea.out", "w", stdout);
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++) {
		int k;
		cin >> k;
		b[i].resize(k);
		for (int j = 0; j < k; j++)
			cin >> b[i][j];
	}
	int ans = 0, l = 1, r = INF;
	while (l <= r) {
		int m = (r + l) >> 1;
		if (valid(m)) {
			ans = m;
			l = m + 1;
		} else {
			r = m - 1;
		}	
	}
	cout << ans;
	return 0;	
}