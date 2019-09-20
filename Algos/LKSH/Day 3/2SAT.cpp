#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 1e5 + 7;
const double EPS = (double) 1e-6;

#define fs first
#define sc second

/**
False -> True. 
Состояние, находящееся в сильной компоненте связности с меньшим номером будет равно false.
Вершины покрашены в три цвета, нужно перекрасить все вершины в цвета так, чтобы ни одно ребро не соединяло вершины двух цветов.
Сводим в 2 SAT. Раздвоим вершину с двумя цветами не равными исходной. Соединим ребром с вершинами, смежными в исходном графе.
**/      

int n, m;
map<string, vector<string>> g, rev;
set<string> used;
vector<string> order;
int color = 0;
map<string, int> wow;

void rev_dfs(string v) {
	wow[v] = color;
	used.insert(v);
	for (auto x : rev[v]) {
		if (!used.count(x))
			rev_dfs(x);
	}	
}

void dfs(string v) {
	used.insert(v);
	for (auto x : g[v]) {
		if (!used.count(x))
			dfs(x);
	}
	order.push_back(v);
}                       

vector<string> all;

void add(int a, char c, int b, char d) {
	string u, v;
	u += to_string(a), u += c;
	v += to_string(b), v += d;
	g[u].push_back(v);
	rev[v].push_back(u);
}

void join(string& s, int u, int v) { 
	vector<char> cur = {'R', 'G', 'B'};
	vector<char> fs, fp;
	for (auto x : cur) {
		if (x != s[u]) fs.push_back(x);
		if (x != s[v]) fp.push_back(x);
	}	
	for (int i = 0; i < 2; i++) {
		int cnt = 0, id = 0;
		for (int j = 0; j < 2; j++)
			if (fs[i] != fp[j]) cnt++, id = j;
		if (cnt == 2) continue;
		add(u, fs[i], v, fp[id]);
	}
}

int main() {
	string s;
	cin >> n >> m >> s;
	while (m--) {
		int u, v;
		cin >> u >> v;
		join(s, u - 1, v - 1);
		join(s, v - 1, u - 1);
	}
	for (int i = 0; i < n; i++) {
		string a, b;
		a += to_string(i), b += to_string(i);
		if (s[i] == 'R') {
			a += 'B', b += 'G';	
		} else if (s[i] == 'B') {
			a += 'R', b += 'G';
		} else if (s[i] == 'G') {
			a += 'B', b += 'R';
		}
		all.push_back(a), all.push_back(b);
	}
	for (auto x : all) {
		if (!used.count(x))
			dfs(x);
	}
	used.clear();
	reverse(order.begin(), order.end());
	for (int i = 0; i < (int) order.size(); i++) {
		if (!used.count(order[i])) {
			color++;
			rev_dfs(order[i]);
		}
	}
	string result;
	for (int i = 0; i < n; i++) {
		string a, b;
		a += to_string(i), b += to_string(i);
		if (s[i] == 'R') {
			a += 'B', b += 'G';	
		} else if (s[i] == 'B') {
			a += 'R', b += 'G';
		} else if (s[i] == 'G') {
			a += 'B', b += 'R';
		}
		if (wow[a] == wow[b]) {
			cout << "Impossible";
			return 0;
		}
		if (wow[a] < wow[b]) {
			result += b.back();
		} else {
			result += a.back();
		}
	}
	cout << result;
	return 0;	
}  