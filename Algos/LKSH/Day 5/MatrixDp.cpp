#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 18;
const int MOD = (int) 1e9 + 7;

/*
Требуется найти число Фибоначчи
f1 = f2 = 1
f_i = a * f_i-1 + b * f_i-2 + c * 2^i + d * i + e.
Создадим матрицу 5 на 1, где первое число обычная однерка, второе число i + 1, третье число предыдущее число фибоначчи, четвертое число фибоначчи
Пятое число 2^i+1

Формула A_n = M^n-2 * A_2
*/

#define fs first
#define sc second

struct matrix {
	int n = 0, m = 0;
	vector<vector<int>> a;
	matrix(vector<vector<int>> b) {
		a = b;
		n = (int) a.size();
		m = (int) a[0].size();
	}
	matrix() {
	}
};

matrix operator * (matrix a, matrix b) {
	vector<vector<int>>	result;
	result.resize(a.n);
	for (int i = 0; i < (int) result.size(); i++)
		result[i].resize(b.m);
	for (int i = 0; i < a.n; i++) {
		for (int j = 0; j < b.m; j++) {
			result[i][j] = 0;
			for (int k = 0; k < a.m; k++) {
				result[i][j] += (1ll * a.a[i][k] * 1ll * b.a[k][j]) % MOD;
				result[i][j] %= MOD;
			}
		}
	}	
	return matrix(result);
}

int a, b, c, d, e, size = 5;

matrix bin_pow(matrix x, int64 n) {
	matrix result = x;
	n--;
	while (n) {
		if (n & 1ll) {
			result = result * x;
			n--;
		} else {
			x = x * x;
			n >>= 1ll;
		}
	}
	return result;
}

int main() {
	int a, b, c, d, e;
	int64 n;
	cin >> a >> b >> c >> d >> e >> n;
	if (n == 1 || n == 2) {
		cout << 1;
		exit(0);
	}
	vector<vector<int>> cur;
	cur.resize(size);
	cur[0] = {1};
	cur[1] = {3};
	cur[2] = {1};
	cur[3] = {1};
	cur[4] = {8};
	matrix x(cur);
	cur.clear();
	cur.resize(size);
	cur[0] = {1, 0, 0, 0, 0};
	cur[1] = {1, 1, 0, 0, 0};
	cur[2] = {0, 0, 0, 1, 0};
	cur[3] = {e, d, b, a, c};
	cur[4] = {0, 0, 0, 0, 2};
	matrix y(cur);
	matrix dp = bin_pow(y, n - 2);
	matrix result = dp * x;
	cout << result.a[3][0];
	return 0;	
}