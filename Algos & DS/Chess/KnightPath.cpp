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
На шахматной доске размером 8 ? 8 заданы две клетки. Соедините эти клетки кратчайшим
путем коня.
*/

pair<int, int> convert(char l, int num) {
	return mp(l - 'a' + 1, num);
}

int dx[] = {-1, 1, 2, -2, 1, -1, 2, -2};
int dy[] = {2, 2, 1, 1, -2, -2, -1, -1};

bool used[9][9];
queue<pair<int, int> > q;

void push(pair<int, int> p) {
	q.push(p);
	used[p.first][p.second] = 1;	
}

bool check(int x, int y) {
	return ((x > 0) && (y > 0) && (x < 9) && (y < 9));
}
                            
int main() {
	freopen("knight1.in", "r", stdin);
	freopen("knight1.out", "w", stdout);

	pair<int, int> start, finish;
	char letter;
	int num;

	cin >> letter >> num;
	start = convert(letter, num);
	cin >> letter >> num;
	finish = convert(letter, num);
	
	pair<int, int> d[9][9];
	push(start);

	while(!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();
		for (int i = 0; i < 8; i++) {
			int u = dx[i] + p.first;
			int e = dy[i] + p.second;
			if (!used[u][e] && check(u, e)) {
				push(mp(u, e));
				d[u][e] = p;
			}
		}	
	}
	
	vector<pair<char, int> > ans;
	for (pair<int, int> s = finish; s != start; s = d[s.fi][s.se]) {
		ans.pb(mp(char(s.first + 'a' - 1), s.second));
	}

	ans.pb(mp(start.fi + 'a' - 1, start.se));
	reverse(all(ans));
	
	for (auto square : ans) {
		cout << square.fi << square.se << '\n';
	}
	return 0;
}