#include <bits/stdc++.h>
  
using namespace std;

typedef long long ll;
  
const int N = (int) 1e3 + 7;
const int M = (int) 1e9 + 7;

ll calc(int n, int k) {
	ll res = 1;
	for (int i = n - k + 1; i <= n; i++)
			res *= (ll)i;
	return res;		
}

int main() {
	int n, k;
	cin >> n >> k;
	cout << calc(n, k); ///Размещения	
	return 0;
}