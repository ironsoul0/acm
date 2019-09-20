#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 8e2 + 7;
const int INF = (int) 1e9 + 7;

/**
Есть строка и карточки, на которых с двух сторон написаны буквы.
Нужно использовать некоторые карточки, их можно менять местами и переворачивать.
Нужно построить данную строку.

Создаем фиктивный сток и ведем из него ребра в 26 букв, на которых написано количество буквы в исходной строке
Каждую букву соединим с каждой строкой, состоящей из двух символов, в которой она содержится и соединим ребром, на котором написана бесконечность
Все эти пары соединим с фиктивным истоком, на ребре напишем количество этих пар в наших данных карточках
**/

#define fs first
#define sc second

struct edge {
	int to, f, c;
	edge(int _to, int _f, int _c) {
		to = _to, f = _f, c = _c;
	}
};

int used[N];
vector<vector<int>> g(N);
int start = 0, t;
vector<edge> all;

int dfs(int v, int c_min, int it) {
	if (v == t)
		return c_min;
	used[v] = 1;
	for (auto i : g[v]) {
		edge x = all[i];
		int to = x.to;
		if (!used[to] && x.f < x.c && x.c - x.f >= it) {
			int delta = dfs(to, min(c_min, x.c - x.f), it);
			if (delta > 0) {
				all[i].f += delta;
				all[i ^ 1].f -= delta;
				return delta;
			}
		}	
	}
	return 0;
}

void find_flow() {
	start = 0;
	int it = (1 << 30);
	while (it > 0) {
		for (int i = 0; i < N; i++)
			used[i] = 0;
		while (dfs(start, INT_MAX, it) > 0) {
			for (int i = 0; i < N; i++)
				used[i] = 0;	
		}
		it >>= 1;	
	}	
}

void create_edge(int u, int v, int c) {
	g[u].push_back(all.size());	
	all.push_back(edge(v, 0, c));
	g[v].push_back(all.size());
	all.push_back(edge(u, 0, 0));
}

map<string, int> id;
int w[N], v[N];
map<string, vector<int>> cnt;

int main() {
	ios_base::sync_with_stdio(0);
	string rev[N];
	t = 1;
	string s;
	for (char c = 'a'; c <= 'z'; c++) {
		s += c;
		id[s] = t;
		rev[t] = s;
		s.pop_back();
		t++;
	}
	for (char c = 'a'; c <= 'z'; c++) {
		s += c;
		for (char x = 'a'; x <= 'z'; x++) {
			s += x;
			id[s] = t;
			rev[t] = s;
			s.pop_back();	
			t++;
		}
		s.pop_back();	
	}	
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		string x;
		cin >> x;
		cnt[x].push_back(i);
		v[id[x]]++;
	}
	string z;
	cin >> z;
	for (auto x : z) {
		s += x;
		w[id[s]]++;	
		s.pop_back();
	}
	for (char c = 'a'; c <= 'z'; c++) {
		s += c;
		create_edge(start, id[s], w[id[s]]);
		s.pop_back();
	}        
	for (char c = 'a'; c <= 'z'; c++) {
		s += c;
		for (char x = 'a'; x <= 'z'; x++) {
			string k;
			k += x;
			for (char y = 'a'; y <= 'z'; y++) {
				k += y;
				if (c == x || c == y) {
					create_edge(id[s], id[k], INF);
				}
				k.pop_back();
			}	
		}
		s.pop_back();	
	}
	for (char c = 'a'; c <= 'z'; c++) {
		for (char x = 'a'; x <= 'z'; x++) {
			string k;
			k += c, k += x;
			create_edge(id[k], t, v[id[k]]);
		}
	}
	find_flow();
	int flow = 0;
	for (auto x : all)
		if (x.to == t && x.f > 0) flow += x.f;
	if (flow != (int) z.size()) {
		cout << "IMPOSSIBLE";
		return 0;
	}
	vector<vector<int>> res(N);
	for (int v = 1; v <= 26; v++) {
		if (w[v] == 0) continue;
		for (int x : g[v]) {
			edge now = all[x];
			string p = rev[now.to];
			for (int c = 0; c < now.f && cnt[p].size() && (int) res[v].size() < w[v]; c++) {
				int cur = cnt[p].back();
				if (p[0] == 'a' + v - 1) {
		    	res[v].push_back(cur);
				} else if (p[1] == 'a' + v - 1) {
					res[v].push_back(-cur);
				} else assert(false);			
				cnt[p].pop_back();
			}
		}
	}
	for (auto x : z) {
		cout << res[x - 'a' + 1].back() << ' ';
		res[x - 'a' + 1].pop_back();
	}
	return 0;	
}