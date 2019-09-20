#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 2e5 + 7;
const int INF = (int) 1e9 + 7;
const double EPS = (double) 1e-6;

#define fs first
#define sc second


/**
Есть прямоугольник N*N и N мест пустых.
Нужно в эти места поставить мужчин и женщин так, чтобы количество их
в одном столбце или строке отличались не более чем на 1.

Делим на две доли : столбцы и строки, соединяем их ребрами.
Теперь добиваемся, чтобы степени всех вершин были четными через фиктивные вершины
Находим эйлеров цикл, и по очереди пишем на ребрах мужчин и женщин
**/

vector<set<pair<int, int>>> g(N);
int deg[N], r[N], id = 0;

void euler(int v, int last = INF) {
	while (g[v].size()) {
		pair<int, int> x = *g[v].begin();
		int to = x.first, id = x.second;
		g[v].erase(make_pair(to, id));
		g[to].erase(make_pair(v, id));
		euler(to, id);
	}       
	if (last != INF) {
		r[last] = id;
		id ^= 1;
	}
}

int main() {
	//freopen("euler.in", "r", stdin);
	//freopen("euler.out", "w", stdout);
	ios_base::sync_with_stdio(0);	
	int s, n;
	cin >> s >> n;
	vector<pair<int, int>> edge;
	for (int i = 0; i < n; i++) {
		int u, v;
		cin >> u >> v;            
		v += s;	
		g[u].insert(make_pair(v, i)), g[v].insert(make_pair(u, i));
		deg[u]++, deg[v]++;
	}	
	int cx = 0, cy = 2 * s + 1;
	for (int v = 1; v <= s; v++) {
		if (deg[v] & 1) {
			g[cx].insert(make_pair(v, INF)), g[v].insert(make_pair(cx, INF));
			deg[cx]++, deg[v]++;
		}	
	}
	for (int v = s + 1; v <= 2 * s; v++) {
		if (deg[v] & 1) {
			g[cy].insert(make_pair(v, INF)), g[v].insert(make_pair(cy, INF));
			deg[cy]++, deg[v]++;
		}
	}
	if (deg[cy] & 1) {
		if (deg[cx] % 2 == 0) assert(false);
		deg[cx]++, deg[cy]++;
		g[cx].insert(make_pair(cy, INF)), g[cy].insert(make_pair(cx, INF));	
	}	
	for (int i = cx; i <= cy; i++) {
		if (deg[i] != 0) {
			euler(i);
			break;
		}
	}
	for (int i = 0; i < n; i++) {
		if (r[i])
			cout << 'W';
		else
			cout << 'M';
	}
	return 0;	
}  