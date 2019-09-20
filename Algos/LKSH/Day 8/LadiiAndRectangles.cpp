#include <bits/stdc++.h>

typedef long long int64;

using namespace std;

/**
Для каждого прямоугольника сказать защищен ли он.
Защищен он, если ладьи на его территории атакует все клетки поля.

Достаточно знать, что ладьи должны либо быть на всех строках и столбцах
Осталось хранить для каждой строки или столбца последнее вхождение ладьи
**/

const int N = (int) 1e6 + 7;
const int K = 26;
const int LOG = 20;

struct query {
	int x1, y1, x2, y2;
	int type;
	int id;
} a[N];

query b[N];

int n, m, k, q;
int t[N * 4];
bool valid[N];

bool compare_y(query i, query j) {
	if (i.y1 != j.y1)
		return i.y1 < j.y1;
	else
		return i.type < j.type;
}

bool compare_x(query i, query j) {
	if (i.x1 != j.x1)
		return i.x1 < j.x1;
	else
		return i.type < j.type;
}

void modify(int v, int tl, int tr, int index, int value) {
	if (tl == tr) {
		t[v] = value;
	} else {
		int tm = (tl + tr) >> 1;
		if (index <= tm)
			modify(v + v, tl, tm, index, value);
		else
			modify(v + v + 1, tm + 1, tr, index, value);
		t[v] = min(t[v + v], t[v + v + 1]);
	}
}

int get(int v, int tl, int tr, int l, int r) {
	if (l <= tl && r >= tr)
		return t[v];
	if (l > tr || r < tl)
		return INT_MAX;
	int tm = (tl + tr) >> 1;
	return min(get(v + v, tl, tm, l, r), get(v + v + 1, tm + 1, tr, l, r));
}

int main() {	
	cin >> n >> m >> k >> q;
	for (int i = 1; i <= k; i++) {
		cin >> a[i].x1 >> a[i].y1;
		a[i].type = -1;
	}
	for (int i = k + 1; i <= k + q; i++) {
		cin >> a[i].x1 >> a[i].y2;
		cin >> a[i].x2 >> a[i].y1;
		a[i].id = i - k;
		a[i].type = 1;
	}
	for (int i = 1; i <= k + q; i++)
		b[i] = a[i];
	sort(a + 1, a + k + q + 1, compare_y);	
	for (int i = 1; i <= k + q; i++) {
		if (a[i].type == -1) {
			modify(1, 1, n, a[i].x1, a[i].y1);
		} else {
			if (get(1, 1, n, a[i].x1, a[i].x2) >= a[i].y2) valid[a[i].id] = true;
		}
	}
	for (int i = k + 1; i <= k + q; i++) {
		swap(b[i].y1, b[i].y2);
		swap(b[i].x1, b[i].x2);
	}
	for (int i = 0; i < N * 4; i++)
		t[i] = 0;
	sort(b + 1, b + k + q + 1, compare_x);
	for (int i = 1; i <= k + q; i++) {
		if (b[i].type == -1) {
			modify(1, 1, m, b[i].y1, b[i].x1);
		} else {
			if (get(1, 1, m, b[i].y1, b[i].y2) >= b[i].x2) valid[b[i].id] = true;
		}
	}
	for (int i = 1; i <= q; i++) {
		if (valid[i])
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}