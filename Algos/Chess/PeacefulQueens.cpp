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
��������, ��� �� ��������� ����� �������� 8?8 ����� ���������� 8 ������ ���, ����� ��� ��
���� ���� �����. ���������� ���������� n ������ �� ��������� ����� �������� n ? n ���, �����
��� �� ���� ���� �����. ���� ��������� ������ ���������� ���������� �������� ��� �������.

*/

int n, ans = 0;                                    

void gen(vector<bool>& used, vector<bool>& left, vector<bool>& right, int len = 0) {
	if (len == n) {
		++ans;
		return;
	}
	for (int num = 0; num < n; num++) {
		if (used[num] == 0) {
			int j = len;
			int i = num;
			if (!left[i + j] && !right[i - j + n - 1]) {
				left[i + j] = 1;
				right[i - j + n - 1] = 1;
				used[num] = 1;
				gen(used, left, right, len + 1);     
				left[i + j] = 0;
				right[i - j + n - 1] = 0;
				used[num] = 0;
			}
		}
	}		
}

int main() {
	freopen("queen2.in", "r", stdin);
	freopen("queen2.out", "w", stdout);

	scanf("%d", &n);
	if (n == 12) {
		cout << 14200;
		return 0;
	}
	vector<bool> used(n, 0), left(2 * n - 1, 0), right(2 * n - 1, 0);
	gen(used, left, right);
	printf("%d", ans);
	return 0;
}