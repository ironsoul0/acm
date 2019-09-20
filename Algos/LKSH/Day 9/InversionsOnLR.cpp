#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long int64;

const int N = (int) 2e5 + 7;

struct query {
	int l, r, id;
} q[N];

int block = 0;

bool compare(query a, query b) {  ////VERY FAST MO
	int bl1 = a.l / block, bl2 = b.l / block;
	return (bl1 < bl2) || ((bl1 == bl2) && ((bl1 & 1) ? a.r > b.r : a.r < b.r));
}

int a[N], f[N];
int64 ans[N], inversion = 0;
int n;

void modify(int index, int delta) {
	for (; index < N; index |= index + 1)
		f[index] += delta;
}

int sum(int r) {
	int result = 0;
	for (; r >= 0; r = (r & (r + 1)) - 1)
		result += f[r];
	return result;
}

int get(int l, int r) {
	if (l > r)
		return 0;
	return sum(r) - sum(l - 1);
}

void add_l(int index) {
	int value = a[index];
	inversion += get(1, value - 1);
	modify(value, 1);			
}

void erase_l(int index) {
	int value = a[index];
	inversion -= get(1, value - 1);
	modify(value, -1);		
}

void add_r(int index) {
	int value = a[index];
	inversion += get(value + 1, n);
	modify(value, 1);
}

void erase_r(int index) {
	int value = a[index];
	inversion -= get(value + 1, n);
	modify(value, -1);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	int m;
	scanf("%d", &m);
	block = 2 * sqrt(n);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].id = i;
	}
	sort(q + 1, q + m + 1, compare);
	int l = 1, r = 0;
	for (int i = 1; i <= m; ++i) {
		int cur_l = q[i].l, cur_r = q[i].r;
		while (l < cur_l) {
			erase_l(l++);
		}	
		while (l > cur_l) {
			add_l(--l);
		}
		while (r < cur_r) {
			add_r(++r);
		}
		while (r > cur_r) {
			erase_r(r--);
		}
		ans[q[i].id] = inversion;
	}
	for (int i = 1; i <= m; ++i) {
		cout << ans[i] << '\n';
	}
	return 0;	
}  