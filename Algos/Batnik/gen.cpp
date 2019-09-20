#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int MOD = (int) 1e9 + 7;
const int N = (int) 1e6 + 7;
 
int main() {
	srand(time(NULL));
	freopen("in.txt", "w", stdout);
	int n = 0, m = 0;
	while(n == 0)
		n = rand() % 100;
	while(m == 0) {
		m = rand() % 10;
	}		
	cout << n << ' ' << m << '\n';
	for (int i = 0; i < m; i++) {
		int x = 0;
		while(x == 0)
			x = rand() % 100;
		cout << x << ' ';
	}	
	cout << '\n';
	return 0;
}