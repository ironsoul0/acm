#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

const int INF = 2e9;
const int SIZE = 2e5;
const double EPS = 1e-8;

#define sz(s) int(s.size())

#define pii pair<int, int>

#define mp make_pair
#define pb push_back

#define fi first
#define se second

#define all(c) c.begin(), c.end()

/*
��� ��������, ����� ����� � ��� �������� ����� ���������� �����������, �� ��� ����� ���-
��� ������� ��������� ���� �� ��������� ��������� � ���������, ����� �������� ������, ��
��������� �� ����� ��������.
� ���� ���� ������ ����� ����� ������, ������� � ���������� ����� ����� � ����� �������
�� ���, ����� � ���������� �� ���������� ������������ ����� ����� ����������. ������� �����
������� ����� ������� � ����� �� ���������� ������� �������.
������ ����� ����� ������, ������� ����� �������� � ���������� ������ �������.

*/

struct point {
	int x, type, pos;
};

struct ans {
	int start, finish;
};

bool operator <(point one, point two) {
	return (one.x < two.x) ||
		(one.x == two.x && one.type < two.type)
			|| (one.x == two.x && one.type == two.type && one.pos < two.pos);
}

int main() {
	freopen("upsolving.in", "r", stdin);
	freopen("upsolving.out", "w", stdout);

	int n, t = -1;
	cin >> n;
	vector<point> p(n * 2);
	vector<ans> total(n);

	for (int i = 0; i < sz(p); i++) {
		cin >> p[i].x;
		if (i % 2 == 0) {
			++t;
		}
		p[i].pos = t;
		p[i].type = (i + 1) % 2 == 0 ? 1 : -1;
	}

	int b = 0, e = 0;

	sort(all(p));

	for (int i = 0; i < sz(p); i++) {
		if (p[i].type == -1) {
			++b;
			total[p[i].pos].finish = e;		
		} else {
			++e;
			total[p[i].pos].start = b;		
		}
	}

	for (int i = 0; i < sz(total); i++) {
		cout << total[i].start - total[i].finish - 1 << '\n';
	}

	return 0;
}