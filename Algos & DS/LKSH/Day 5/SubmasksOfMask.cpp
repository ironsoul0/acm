#include <bits/stdc++.h>

using namespace std;

/**
Нужно покрасить граф из 17 вершин в минимальное количество цветов,
чтобы все вершины соединенные ребром были разных цветов:

Пусть dp[mask] решение для вершин множества mask.
Тогда мы уже знаем все ответы для подмножеств mask.

Переберем их, и используя ответы для них будем получать минимальный ответ
для mask.

Биты, которые есть в mask, но нет в submask равно mask ^ submask.
Эти биты будут обозначать множество вершин, которые мы хотим покрасить в один
цвет.

Их мы можем покрасить в один цвет, если между ними нет ребра
**/

typedef long long int64;

const int N = (int) 17;
const double EPS = (double) 1e-6;
const int P = (int) 1e4 + 7;
const int INF = (int) 1e9 + 7;

#define fs first
#define sc second

int edge[N][N];	
int dp[1 << N], x[1 << N], p[1 << N];
int n;

void zerofy() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			edge[i][j] = 0;
	for (int mask = 0; mask < (1 << N); mask++)
		p[mask] = 0;
}

bool valid(int mask) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if ((mask & (1 << i)) && (mask & (1 << j))) {
				if (edge[i][j]) return false;
			}
		}
	}	
	return true;
}

void solve() {
	int m;
	cin >> n >> m;
	while (m--) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		edge[u][v] = edge[v][u] = 1;
	}
	for (int mask = 0; mask < (1 << n); mask++)
		dp[mask] = INF;
	for (int mask = 1; mask < (1 << n); mask++) {
		if (valid(mask)) {
			x[mask] = 1;
		} else {
			x[mask] = INF;
		}	
	}
	dp[0] = x[0] = 0;
	for (int mask = 1; mask < (1 << n); mask++) {
		int subset = mask;
		for (int subset = ((mask - 1) & mask); ; subset = ((subset - 1) & mask)) {  ////Перебор всех подмасок
			int value = dp[subset] + x[mask ^ subset];
			if (dp[mask] > value) {
				dp[mask] = value;
				p[mask] = subset;
			}
			if (subset == 0) break;
		}
	}
	cout << dp[(1 << n) - 1] << '\n';
	vector<int> color(n);
	int cur_color = 0;
	for (int mask = (1 << n) - 1; mask > 0; mask = p[mask]) {
		cur_color++;
		int son = p[mask];
		int wow = (mask ^ son);
		for (int i = 0; i < n; i++)
			if (wow & (1 << i)) color[i] = cur_color;	
	}
	for (int i = 0; i < n; i++)
		cout << color[i] << ' ';
	cout << '\n';
}

int main() {
	int test;
	cin >> test;
	while (test--) {
		zerofy();
		solve();
	}	
	return 0;	
} 