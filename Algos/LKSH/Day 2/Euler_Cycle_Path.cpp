#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 1e5 + 7;
const double EPS = (double) 1e-6;

#define fs first
#define sc second

vector<multiset<int>> g(N);
vector<int> path;
int deg[N];

void euler_cycle(int v) {  ///Алгоритм нахождение Эйлерова цикла
	while (!g[v].empty()) {
		int to = *g[v].begin();
		g[v].erase(g[v].find(to));
		g[to].erase(g[to].find(v));
		euler_cycle(to);	
	}
	path.push_back(v);
}

void split(int x, int y) {
	path.pop_back();
	vector<int> result;
	int xi = 0;
	for (int i = 0; i < (int) path.size() - 1; i++) {
		if ((path[i] == x && path[i + 1] == y) || (path[i] == y && path[i + 1] == x))
			xi = i;
	}
	for (int i = xi + 1; i < (int) path.size(); i++)
		result.push_back(path[i]);
	for (int i = 0; i <= xi; i++)
		result.push_back(path[i]);
	path = result;		
}

int main() {
	freopen("euler.in", "r", stdin);
	freopen("euler.out", "w", stdout);	
	int n;
	cin >> n;
	for (int v = 1; v <= n; v++) {
		int x;
		cin >> x;
		while (x--) {
			int to;
			cin >> to;
			g[v].insert(to);
			deg[v]++;		
		}
	}	
	int start = 1, x = 0, y = 0, odd = 0;
	for (int i = 1; i <= n; i++) {
		if (deg[i] & 1) {
			if (x == 0) {
				x = i;
			} else if (y == 0) {
				y = i;
			}		
			odd++;
		} 	
	}
	///Для эйлерова пути либо ноль, либо две вершины с нечетными степенями
	///Для эйлерова цикла ноль вершин с нечетными степенями
	///Если нужно найти путь, а вершин с нечетными степенями две, то добавляем фиктивное ребро и ищем цикл, после чего просто удалим это ребро из пути
	if (odd != 0 && odd != 2) {
		cout << -1;
		exit(0);
	}
	if (x != 0) {
		start = x;
		deg[x]++, deg[y]++;
		g[x].insert(y), g[y].insert(x);
	}
	euler_cycle(start);
	if (x != 0) {
		split(x, y);
	}
	cout << (int) path.size() - 1 << '\n';
	for (auto v : path)
		cout << v << ' ';
	return 0;	
}  