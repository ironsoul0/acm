#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int64;

/**
Задобрите Инти
Сгенерировать k-й лексикографический симпатичный узор.
Насчитаем динамику dp[i][mask], оно равно количеству способов заполнить ряды от i до w, где mask означает последний ряд.
**/

const int N = (int) 2e3 + 7;
const int64 INF = (int64) 3e18 + 7;

vector<vector<int>> g(N);
int w, h;
bool correct[N][N];

bool valid(int x, int y) {
	for (int i = 0; i < h - 1; i++) {
		int fx = 0, fy = 0;
		if (x & (1 << i)) fx++;
		if (x & (1 << (i + 1))) fy++;
		int sx = 0, sy = 0;		
		if (y & (1 << i)) sx++;
		if (y & (1 << (i + 1))) sy++;
		if (fx == fy && sx == sy && fx == sx) return correct[x][y] = false;
	}
	return correct[x][y] = true;
}

void build() {
	for (int i = 0; i < (1 << h); i++) {
		for (int j = 0; j < (1 << h); j++) {
			if (valid(i, j)) g[i].push_back(j);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	int64 k;
	cin >> w >> h >> k;
	build();
	int full = (1 << h);	
	vector<vector<int64>> new_dp(w, vector<int64>(full));
	for (int i = 0; i < full; i++)
		new_dp[w - 1][i] = 1;
	if (w == 1 && k > full) {
		cout << "Impossible";
		return 0;
	}
	vector<int> result;
	for (int i = w - 2; i >= 0; i--) {
		for (int j = 0; j < full; j++) {
			for (auto to : g[j]) {
				new_dp[i][j] += new_dp[i + 1][to];
				new_dp[i][j] = min(new_dp[i][j], INF); ///Против переполнения
			}
		}
	} 
	int64 all = 0;
	for (int j = 0; j < full; j++) {
		all += new_dp[0][j];
		all = min(all, INF);
	}
	if (all < k) {
		cout << "Impossible";
		return 0;
	}
	int last = 0;
	for (int i = 0; i < w; i++) {
		int wow = 0;
		for (int j = 0; j < full; j++) {
			if (i != 0 && !correct[last][j]) {
				continue;			
			}	
			if (new_dp[i][j] >= k) {      ///Генерим к-тый объект. Ставим от меньшего к большему
				wow = j;
				break;
			} else {
				k -= new_dp[i][j];
			}
		}	
		for (int j = h - 1; j >= 0; j--) {
			if (wow & (1 << j)) result.push_back(1); else result.push_back(0);
		}
		last = wow;	
	}
	assert(k == 1ll);
	int size = (int) result.size();
	assert(size == w * h);
	vector<vector<int>> f(h, vector<int>(w));
	int row = 0, col = 0;
	for (int i = 0; i < (int) result.size(); i++) {
		f[row][col] = result[i];
		if (row + 1 == h) {
			row = 0;
			col++;	
		} else {
			row++;	
		}
	}
	for (int i = 0; i < h; i++, cout << '\n') {
		for (int j = 0; j < w; j++) {
			if (f[i][j]) cout << 'b'; else cout << 'w';
		}
	}
	return 0;	
}   