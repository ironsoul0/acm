#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 1e5 + 7;
const double EPS = (double) 1e-6;
const int P = (int) 1e4 + 7;
const int INF = (int) 1e9 + 7;

/**
Даны точки, нужно найти ближайшие
Решаем через Разделяйку
**/

#define fs first
#define sc second

struct point {
	long long x, y;
};

double mini = (double) 10E18;
long long sx = 0, sy = 0, fx = 0, fy = 0;

void modify(point a, point b) {
	double cur_d = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	if (cur_d < mini) {
		mini = cur_d;
		sx = a.x, sy = a.y;
		fx = b.x, fy = b.y;
	}
}

bool cmp_x(point a, point b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

point buffer[N];
point a[N], b[N], c[N];

void merge_two(int l, int m, int r) {
	int nv = m - l + 1, mv = r - m;	
	for (int i = l; i <= m; i++)
		b[i - l + 1] = a[i];
	for (int i = m + 1; i <= r; i++)
		c[i - m] = a[i];	
	b[nv + 1].y = c[mv + 1].y = INF;
	int p1 = 1, p2 = 1;
	for (int i = l; i <= r; i++) {
		if (b[p1].y < c[p2].y) {
			a[i] = b[p1++];
		} else {
			a[i] = c[p2++];
		}
	}
}

void solve(int l, int r) {
	if (r - l + 1 <= 1) {
		return;
	} else {
		int m = (r + l) >> 1;
		long long x_m = a[m].x;
		solve(l, m), solve(m + 1, r);
		merge_two(l, m, r);
		int buf_last = 0;
		vector<point> valid;
		for (int i = l; i <= r; i++) {
			if (abs(a[i].x - x_m) <= mini) {
				valid.push_back(a[i]);
			}
		}
		int k = (int) valid.size();
		for (int i = 0; i < k; i++) {
			int j = i + 1;
			while (j < k && (valid[j].y - valid[i].y) <= mini) {
				modify(valid[i], valid[j]);
				j++;
			}
		}	
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].y;
	}
	sort(a, a + n, cmp_x);
	solve(0, n - 1);
	cout << sx << ' ' << sy << '\n' << fx << ' ' << fy;
	return 0;	
}   