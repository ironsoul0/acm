#include <bits/stdc++.h>

using namespace std;

/*
Дано число X и множество цифр D. Требуется дописать к X минимальное количество цифр из D,
чтобы получившееся число делилось на K. При этом получившееся число должно быть минимально
возможным.
Формат входных данных
Первая строка входного файла содержит два натуральных числа X и K
. Во второй строке записано количество цифр во множе-
стве D. В третьей строке через пробел записаны эти цифры.
Формат выходных данных
Единственная строка должна содержать минимальное число, полученное из X дописыванием
цифр из D и кратное K. Если такого числа не существует, выведите -1.
*/

int main() {
	freopen("multiple.in", "r", stdin);
	freopen("multiple.out", "w", stdout);
	string x;
	int MOD, n;
	cin >> x;
	cin >> MOD >> n;
	int D[n];
	for (int i = 0; i < n; ++i) {
		cin >> D[i];
	}
	int rem = 0;
	for (int i = 0; i < int(x.size()); i++) {
		int num = x[i] - '0';
		rem = (rem * 10 + num) % MOD;
	}
	sort(D, D + n);
	queue<int> q;
	vector<bool> used(MOD, 0);
	int way[MOD], get[MOD];
	q.push(rem);
	used[rem] = 1;
	while(!q.empty()) {
		int a = q.front();
		q.pop();
		for (int i = 0; i < n; ++i) {
			int num = D[i];
			int m = ((a * 10) % MOD + (num % MOD)) % MOD; 
			if (!used[m]) {
				used[m] = 1;
				way[m] = a;
				get[m] = num;
				q.push(m);
			}
		}
	}
	if (!used[0]) {
		cout << -1;
		return 0;
	}
	cout << x;
	vector<int> ans;
	for (int num = 0; num != rem; num = way[num]) {
		ans.push_back(get[num]);	
	}
	reverse(ans.begin(), ans.end());
	for (auto elem : ans) {
		cout << elem;
	}
	return 0;
}