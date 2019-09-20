#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int ADD_EDGE = 0;
const int DELETE_EDGE = 1;
const int QUESTION = 2;

const int N = (int) 1e6 + 7;
const double EPS = (double) 1e-6;

/**
Приходят три запроса: удалить ребро, добавить и посчитать количество компонент связности.
Для каждого добавления найдем ближайшее удаление и наоборот.
Разобьем задачу на две части.
Уходя в одну часть добавим в СНМ ребра, всегда существующие на этом отрезке.
**/

#define fs first
#define sc second

struct query {
	int type; ///0 - add edge, 1 - delete edge, 2 - question
	int u, v;
	int was;
} a[N];

int size[N], p[N], res[N];
int n, k;

void init() {
	for (int i = 0; i < N; i++)
		size[i] = 1, p[i] = i;
}

int root(int v) {
	if (p[v] == v)
		return v;
	return root(p[v]);
}

pair<int, int> join(int a, int b) {
	a = root(a), b = root(b);
	if (a == b) {
		return make_pair(-1, -1);
	}
	n--;
	if (size[a] > size[b]) {
		p[b] = a;
		size[a] += size[b];	
		return make_pair(a, b);
	} else {
		p[a] = b;
		size[b] += size[a];
		return make_pair(b, a);
	}
}

void disjoin(int a, int b) {     ///Откат СНМ без сжатия путей..
	p[b] = b;
	size[a] -= size[b];	
	n++;
}

void solve(int l, int r) {
	if (r - l + 1 <= 1) {
		if (l == r)
			if (a[l].type == QUESTION) res[l] = n;	
	} else {
		int m = (r + l) >> 1;
		vector<pair<int, int>> joined;
		for (int i = m + 1; i <= r; i++) {
			if (a[i].type == DELETE_EDGE && a[i].was < l) {          
				int u = a[i].u, v = a[i].v;
				pair<int, int> result = join(u, v);
				if (result.first != -1)
					joined.push_back(result);
			}
		}	
		solve(l, m);
		while (joined.size()) {
			disjoin(joined.back().first, joined.back().second);
			joined.pop_back();
		}	
		for (int i = l; i <= m; i++) {
			if (a[i].type == ADD_EDGE && a[i].was > r) {
				int u = a[i].u, v = a[i].v;
				pair<int, int> result = join(u, v);
				if (result.first != -1)
					joined.push_back(result);
			}
		}
		solve(m + 1, r);
		while (joined.size()) {
			disjoin(joined.back().first, joined.back().second);
			joined.pop_back();
		}
	}
}

int main() {
	init();
	cin >> n >> k;
	map<pair<int, int>, int> q;
	for (int i = 0; i < k; i++) {
		string s;
		cin >> s;
		if (s == "?") { 
			a[i].type = QUESTION;
		} else {
			cin >> a[i].u >> a[i].v;
			if (a[i].u > a[i].v) swap(a[i].u, a[i].v);
			if (s == "+") {
				a[i].type = ADD_EDGE;
				q[make_pair(a[i].u, a[i].v)]++;
			} else if (s == "-") {
				a[i].type = DELETE_EDGE;
				q[make_pair(a[i].u, a[i].v)]--;
			}
		}
	}
	for (int i = 0; i < k; i++)
		a[i].was = -1;
	q.clear();	
	for (int i = 0; i < k; i++) {
		if (a[i].type == ADD_EDGE) {
			q[make_pair(a[i].u, a[i].v)] = i;	
		} else if (a[i].type == DELETE_EDGE) {
			int link = q[make_pair(a[i].u, a[i].v)];
			a[i].was = link, a[link].was = i;
		}
	}
	for (int i = 0; i < k; i++) {
		if (a[i].type == ADD_EDGE && a[i].was == -1)
			a[i].was = INT_MAX;
	}
	solve(0, k - 1);
	for (int i = 0; i < k; i++)
		if (res[i] > 0) cout << res[i] << '\n';	
	return 0;	
}         