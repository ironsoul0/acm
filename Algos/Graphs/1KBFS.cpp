#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

const int INF = 2e9;
const int SIZE = 2e5;

#define sz(s) int(s.size())

#define pii pair<int, int>

#define mp make_pair
#define pb push_back

#define fi first
#define se second

#define all(c) c.begin(), c.end()

/*
Карта мира в компьютерной игре «Цивилизация» версии 1 представляет собой прямоугольник,
разбитый на квадратики. Каждый квадратик может иметь один из нескольких возможных релье-
фов, для простоты ограничимся тремя видами рельефов — поле, лес и вода. Поселенец перемещается
по карте, при этом на перемещение в клетку, занятую полем, необходима одна единица времени, на
перемещение в лес — две единицы времени, а перемещаться в клетку с водой нельзя.
У вас есть один поселенец, вы определили место, где нужно построить город, чтобы как можно
скорее завладеть всем миром. Найдите маршрут переселенца, по которому можно прийти в место
строительства города за минимальное время. На каждом ходе переселенец может перемещаться в
клетку, имеющую общую сторону с той клеткой, где он сейчас находится.
Формат входных данных
Во входном файле записаны два натуральных числа N и M, не превосходящих 1000 — размеры
карты мира (N — число строк в карте, M — число столбцов). Затем заданы координаты начального
положения поселенца x и y, где x — номер строки, y — номер столбца на карте (1 6 x 6 N,
1 6 y 6 M), строки нумеруются сверху вниз, столбцы — слева направо. Затем аналогично задаются
координаты клетки, куда необходимо привести поселенца.
Далее идет описание карты мира в виде N строк, каждая из которых содержит M символов.
Каждый символ может быть либо «.» (точка), обозначающим поле, либо «W», обозначающим лес,
либо «#», обозначающим воду.
Гарантируется, что начальная и конечная клетки пути переселенца не являются водой.
Формат выходных данных
В первой строке выходного файла выведите количество единиц времени, необходимое для пе-
ремещения поселенца (перемещение в клетку с полем занимает 1 единицу времени, перемещение в
клетку с лесом — 2 единицы времени). Во второй строке выходного файла выведите последователь-
ность символов, задающих маршрут переселенца. Каждый символ должен быть одним из четырех
следующих: «N» (движение вверх), «E» (движение вправо), «S» (движение вниз), «W» (движение
влево). Если таких маршрутов несколько — выведите любой из них.
Если дойти из начальной клетки в конечную невозможно, выведите число -1.
*/

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int n, m;
vector<string> t(1100);

bool is_valid(int x, int y, int n, int m) {
	return ((x > -1) && (y > -1) && (x < n) && (y < m) && (t[x][y] != '#'));	
}

int get_cost(int i, int j) {
	if (t[i][j] == 'W') {
		return 2;
	}
	if (t[i][j] == '.') {
		return 1;	
	}
	if (t[i][j] == '#') {
		return 0;
	}
}

pair<int, int> way[1100][1100];

int main() {
	freopen("civ.in", "r", stdin);
	freopen("civ.out", "w", stdout);

	int sx, sy, fx, fy;
	
	cin >> n >> m;
	cin >> sx >> sy;
	cin >> fx >> fy;

	--sx;
	--sy;
	--fx;
	--fy;

	for (int i = 0; i < n; ++i) {
		cin >> t[i];
	}
	
	queue<pair<int, int> > q[3];
	vector<vector<int> > dist(n + 1, vector<int>(m + 1, INF));

	q[0].push(make_pair(sx, sy));
	dist[sx][sy] = 0;

	while(!q[0].empty() || !q[1].empty() || !q[2].empty()) {
		while(!q[0].empty()) {
			pair<int, int> cp = q[0].front();
			q[0].pop();
			for (int i = 0; i < 4; ++i) {
				int cx = cp.first + dx[i];
				int cy = cp.second + dy[i];
				if (!is_valid(cx, cy, n, m)) {
					continue;
				}
				int cost = get_cost(cx, cy);
				int x = cp.first, y = cp.second;
				if (is_valid(cx, cy, n, m) && dist[x][y] + cost < dist[cx][cy]) {
					dist[cx][cy] = dist[x][y] + cost;
					q[cost].push(make_pair(cx, cy));
					way[cx][cy] = mp(x, y); 			
				} 
			}
		}
		swap(q[0], q[1]);
		swap(q[1], q[2]);
	}
	vector<pii> ans;
	
	if (dist[fx][fy] == INF) {
		cout << -1;
		return 0;
	} else {
		cout << dist[fx][fy] << '\n';
		for (pair<int, int> cnt = mp(fx, fy); cnt != mp(sx, sy); cnt = way[cnt.fi][cnt.se]) {
			ans.pb(cnt);
		}
		ans.pb(mp(sx, sy));
	}

	reverse(all(ans));
	int cntX, cntY;
	if (!ans.empty()) {
		cntX = ans[0].fi, cntY = ans[0].se;
	}

	for (int i = 1; i < sz(ans); i++) {
		if (ans[i].fi != cntX) {
			if (ans[i].fi > cntX) {
				cout << 'S';
			} else {
				cout << 'N';
			}
		} else {
			if (ans[i].se > cntY) {
				cout << 'E';
			} else {
				cout << 'W';
			}	
		}
		cntX = ans[i].fi;
		cntY = ans[i].se;
	}
	return 0;
}