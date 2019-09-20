#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

/**
Принадлежность точки многоугольнику. Найдем самую левую точку.
Если текущий запрос точки левее чем наша самая левая то просто пропускаем.
Иначе бинпоиском найдем угол между которым находится наша точка через векторное произведение
Осталось проверить через площадь треугольника принадлежность углу внутри многоуольника
**/

const int N = (int) 1e5 + 7;

vector<pair<int, int>> a;
int mx = 0, my = 0;
int cx = 0, cy = 0;

bool cross_product(int x1, int y1, int x2, int y2) {
	return (1ll * x1 * 1ll * y2 - 1ll * x2 * 1ll * y1) >= 0;
}

bool shift(pair<int, int> px, pair<int, int> py) {
	int x1 = px.first - cx, y1 = px.second - cy;
	int x2 = py.first - cx, y2 = py.second - cy;
	int x3 = mx - cx, y3 = my - cy;                                                  
	return (cross_product(x3, y3, x1, y1) && cross_product(x2, y2, x3, y3));		
}

int64 get_area(int x1, int y1, int x2, int y2, int x3, int y3) {
	return abs(x1 * 1ll * y2 + x2 * 1ll * y3 + x3 * 1ll * y1 - y1 * 1ll * x2 - y2 * 1ll * x3 - y3 * 1ll * x1);
}

bool triangle(pair<int, int> px, pair<int, int> py) {
	int64 first = get_area(px.first, px.second, py.first, py.second, mx, my);
	first -= get_area(px.first, px.second, mx, my, cx, cy);
	first -= get_area(px.first, px.second, cx, cy, py.first, py.second);
	first -= get_area(mx, my, py.first, py.second, cx, cy);
	return first == 0;
}
             
int main() {
	ios_base::sync_with_stdio(0);
	int n, m, k;
	cin >> n >> m >> k;
	vector<pair<int, int>> p(n);
	int id = 0;
	for (int i = 0; i < n; i++) {
		cin >> p[i].first >> p[i].second;
		if (p[id].first > p[i].first || (p[id].first == p[i].first && p[id].second > p[i].second))
			id = i;
	}
	for (int i = id; i < n; i++) {
		a.push_back(p[i]);
	}
	for (int i = 0; i < id; i++) {
		a.push_back(p[i]);
	}
	mx = a[0].first, my = a[0].second;
	int result = 0;
	for (int i = 1; i <= m; i++) {
		cin >> cx >> cy;
		if (mx > cx || (mx == cx && my > cy)) continue;
		int l = 1, r = n - 1;
		while (r - l > 1) {
			int m = (r + l) >> 1;
			if (shift(a[l], a[m])) {
				r = m;	
			} else {
				l = m;
			}
		}
		if (triangle(a[l], a[r])) result++;
	}
	if (result >= k)
		cout << "YES";
	else
		cout << "NO";
	return 0;	
}  