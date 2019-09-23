#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <queue>
#include <set>
#include <map>
#include <cassert> 

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int MOD = (int) 1e9 + 7;
const int N = (int) 1e6 + 7;
const ll INF = (ll) 1e18 + 7;

void yes() {
	cout << "YES";
	exit(0);
}

int main() {
	ios_base::sync_with_stdio(0);
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
	vector<int> a(4);
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		cin >> a[i];
		sum += a[i];
	}
	for (int i = 0; i < 4; i++) {
		if (sum - a[i] == a[i]) yes();
	}
	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < 4; j++) {
			if (sum - a[i] - a[j] == a[i] + a[j]) yes();
		}
	}
	cout << "NO";
	return 0;
}