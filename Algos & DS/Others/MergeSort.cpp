#include <bits/stdc++.h>

using namespace std;

const int INF = 2e9;
const int N = 2e5;

int inversion = 0;
int f[N], s[N];

void merge_it(int* a, int l, int mid, int r) {
	int n = mid - l + 1, m = r - mid;
	for (int i = 1; i <= n; i++) {
		f[i] = a[l + i - 1];
	}
	for (int i = 1; i <= m; i++) {
		s[i] = a[mid + i];
	}
	f[n + 1] = s[m + 1] = INF;
	int fst = 1, snd = 1;
	for (int i = l; i <= r; i++) {
		if (f[fst] <= s[snd]) {
			a[i] = f[fst++];
		} else {
			a[i] = s[snd++];
			inversion += n - fst + 1;
		}
	}
}

void merge_sort(int* a, int l, int r) {
	if (l == r) {
		return;
	}
	int mid = (r + l) >> 1;
	merge_sort(a, l, mid);
	merge_sort(a, mid + 1, r);
	merge_it(a, l, mid, r);
}

int main() {
	int a[N], n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	merge_sort(a, 1, n);
	for (int i = 1; i <= n; i++) {
		cout << a[i] << " ";
	}
	cout << '\n' << inversion;
	return 0;
}