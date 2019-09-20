#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 1e2 + 7;
const double EPS = (double) 1e-6;

#define fs first
#define sc second

///Алгоритм Куна находит максимальное паросочетание в двудольном графе
///Задача:
///Дано имя из латинских букв. Даны кубики на которых написаны некоторые буквы
///Необходимо сопоставить каждой букве из имени кубик, на котором эта буква есть.
///Тем самым получается имя человека.

///Сопоставим левой доле кубики, а правой буквы из имени
///Алгоритмом Куна для правой доли(каждой буквы имени) найдем подходящий кубик

vector<vector<int>> g(N);
bool used[N];
int w[N];

bool in(char c, string s) {
	for (auto x : s)
		if (x == c) return true;
	return false;
}

bool start_kuhn(int v) {
	if (used[v])
		return false;
	used[v] = true;
	for (auto to : g[v]) {
		if (w[to] == -1 || start_kuhn(w[to])) {
			w[to] = v;
			return true;
		}
	}	
	return false;
}

int main() {
	freopen("kuhn.in", "r", stdin);
	freopen("kuhn.out", "w", stdout);
	int n;
	cin >> n;
	string s;
	cin >> s;
	for (int i = 1; i <= n; i++) {
		string t;
		cin >> t;
		for (int j = 1; j <= (int) s.size(); j++) {
			if (in(s[j - 1], t)) {
				g[i].push_back(j);
			}	
		}
	}
	for (int i = 0; i < N; i++)
		w[i] = -1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < N; j++)
			used[j] = false;
		start_kuhn(i);			
	}
	vector<int> result;
	for (int j = 1; j <= (int) s.size(); j++) {
		if (w[j] == -1) {
			cout << "NO";
			exit(0);
		}
		result.push_back(w[j]);
	}
	cout << "YES" << '\n';
	for (auto x : result)
		cout << x << ' ';
	return 0;	
}  