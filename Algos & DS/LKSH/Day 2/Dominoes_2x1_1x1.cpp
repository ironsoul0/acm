#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 1e4 + 7;
const double EPS = (double) 1e-6;
const int P = (int) 1e2 + 7;

/**
≈сть поле, где некоторые клетки зан€ты. Ќужно замостить незан€тые клетки
доминошками 2х1 и 1х1. —тоимость первой услуги - а, а второй - b. 

Ѕудем пытатьс€ максимизировать использование доминошки 2х1, разбив
клетки на две доли, представив доску как шахматную доску. ќсталось найти
максимальное паросочетание в двудольном графе через алгоритм  уна.
**/

#define fs first
#define sc second

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

char f[P][P];
int w[N], ban[N], used[N];
int n, m;
vector<vector<int>> g(N);

bool valid(int x, int y) {
	return (x >= 1 && y >= 1 && x <= n && y <= m && f[x][y] == '*');
}

int modify(int x, int y) {
	return (x - 1) * m + y;
}

bool help_kuhn(int v) {
	if (used[v])
		return false;
	used[v] = 1;
	for (auto to : g[v]) {
		if (w[to] == -1 || help_kuhn(w[to])) {
			w[to] = v;
			return true;
		}
	}
	return false;
}

int main() {
	freopen("dominoes.in", "r", stdin);
	freopen("dominoes.out", "w", stdout);
	int a, b;
	cin >> n >> m >> a >> b;
	int all = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> f[i][j];
			if (f[i][j] == '*') {
				all++;
			}
		}
	}
	for (int i = 1; i <= n * m; i++)
		w[i] = -1, ban[i] = 0;
	if (2 * b <= a) {
		cout << all * b;
		exit(0);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k], ny = j + dy[k];
				if (valid(nx, ny) && valid(i, j)) {
					int v = modify(i, j), to = modify(nx, ny);
					if ((i + j) & 1) {
						g[v].push_back(to);
					}
				}	
			}
		}
	}	
	for (int v = 1; v <= n * m; v++) { ///Kuhn Optimization
		for (auto to : g[v]) {
			if (w[to] == -1) {
				w[to] = v;
				ban[v] = 1;
				break;
			}
		}
	}
	for (int v = 1; v <= n * m; v++) {
		if (ban[v]) continue; ///Here optimization goes
		for (int j = 1; j <= n * m; j++)
			used[j] = 0;
		help_kuhn(v);
	}		
	int cur = 0;
	for (int i = 1; i <= n * m; i++) {
		if (w[i] != -1) /// летки в максимальном паросочетании
			cur++;
	}
	cout << cur * a + (all - cur * 2) * b;
	return 0;	
}   