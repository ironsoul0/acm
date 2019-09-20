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
Ќа каждой клетке шахматной доски размеров 8 ? 8 записано целое неотрицательное число.
 ороль может перемещатьс€ по шахматной доске из левого нижнего угла в правый верхний, пере-
меща€сь только вправо, вверх или по диагонали вправоЦвверх. ѕри этом стоимость прохода через
данную клетку равна числу, записанному на этой клетке.
ѕереместите корол€ из левого нижнего угла в правый верхний с наименьшей стоимостью про-
хода.
*/

int dp[8][8];
pair<int, int> p[8][8];
                            
int main() {
	freopen("king2.in", "r", stdin);
	freopen("king2.out", "w", stdout);
	
	int a[8][8];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cin >> a[i][j];
		}
	}
	
	dp[7][0] = a[7][0];

	for (int i = 6; i >= 0; i--) {
		dp[i][0] = dp[i + 1][0] + a[i][0];
		p[i][0] = mp(i + 1, 0);
	}

	for (int i = 1; i < 8; i++) {
		dp[7][i] = dp[7][i - 1] + a[7][i];
		p[7][i] = mp(7, i - 1);
	}

	for (int i = 6; i >= 0; i--) {
		for (int j = 1; j < 8; j++) {
			dp[i][j] = min(dp[i + 1][j], min(dp[i][j - 1], dp[i + 1][j - 1])) + a[i][j];
			int recalc = dp[i][j] - a[i][j];
			if (recalc == dp[i][j - 1]) {
				p[i][j] = mp(i, j - 1);
			} else if (recalc == dp[i + 1][j]) {
				p[i][j] = mp(i + 1, j);
			} else {
				p[i][j] = mp(i + 1, j - 1);
			}
		}
	}

	cout << dp[0][7] << '\n';
	
	vector<pair<char, int> > ans;
	pair<int, int> finish = mp(0, 7);

	for (pair<int, int> s = finish; s != mp(7, 0); s = p[s.fi][s.se]) {
		ans.pb(mp(char('a' + s.se), 8 - s.fi));
	}

	ans.pb(mp('a', 1));
	reverse(all(ans));
	for (auto elem : ans) {
		cout << elem.fi << elem.se << " ";
	}
	return 0;
}