#include <bits/stdc++.h>

using namespace std;

#define sz(x) int(x.size())

/*
Главного конструктора Петю попросили разработать новую модель самолёта для компании «Air
Бубундия». Оказалось, что самая сложная часть заключается в подборе оптимального размера топ-
ливного бака.
Главный картограф «Air Бубундия» Вася составил подробную карту Бубундии. На этой карте
он отметил расход топлива для перелёта между каждой парой городов.
Петя хочет сделать размер бака минимально возможным, для которого самолёт сможет долететь
от любого города в любой другой (возможно, с дозаправками в пути).
Формат входных данных
Первая строка входного файла содержит натуральное число n — число городов
в Бубундии. Далее идут n строк по n чисел каждая. i-е число в j-й строке равно расходу топлива
при перелёте из i-го города в j-й. Все числа не меньше нуля и меньше 109
. Гарантируется, что для
любого i в i-й строчке i-е число равно нулю.
Формат выходных данных
Первая строка выходного файла должна содержать одно число — оптимальный размер бака
*/

const int V = 1001;

vector< vector<pair<int, int> > > g(V), rev(V);
vector<int> used(V), color(V);
int cnt = 0, need = 0, n;
stack<int> s;

void topsort(int v) {
	used[v] = 1;
	for (int i = 0; i < sz(g[v]); i++) {
		int u = g[v][i].first, len = g[v][i].second;
		if (!used[u] && len <= need) {
			topsort(u);
		}
	}
	s.push(v);
}
      
void rev_dfs(int v, int id) {
	color[v] = id;
	for (int i = 0; i < sz(rev[v]); i++) {
		int u = rev[v][i].first, len = rev[v][i].second;
		if (color[u] == 0 && len <= need) {
			rev_dfs(u, id);
		}
	}
}

void condensation() {
	for (int i = 1; i <= n; i++) {
		if (!used[i]) {
			topsort(i);
		}
	}	
	while(!s.empty()) {
		if (!color[s.top()]) {
			rev_dfs(s.top(), ++cnt);
		}
		s.pop();
	}
}

int main() {
	freopen("avia.in", "r", stdin);
	freopen("avia.out", "w", stdout);

	int ans = int(2e9);
	cin >> n;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; j++) {
			int len;
			cin >> len;
			g[i].push_back(make_pair(j, len));
			rev[j].push_back(make_pair(i, len));
		}	
	}
	
	int l = -1, r = int(2e9);

	while(r - l > 1) {
			for (int i = 1; i <= n; i++) {
			used[i] = 0;
			color[i] = 0;
		}
		cnt = 0;
		while(!s.empty()) {
			s.pop();
		}
		need = (r + l) >> 1;
		bool good = 1;
		condensation();
		for (int i = 1; i <= n; i++) {
			if (color[i] != 1) {
				good = 0;
			}	
		}
		if (good) {
			ans = min(ans, need);
			r = need;
		} else {
			l = need;
		}
	}
	cout << ans;
	return 0;
}          