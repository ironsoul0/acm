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

void hanoy(int val, char start, char buff, char end) {
	if (val == 0) return;
	hanoy(val - 1, start, end, buff);
	cout << start << ' ' << end << '\n';
	hanoy(val - 1, buff, start, end);
}

int main() {
	ios_base::sync_with_stdio(0);
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
	int n, k;
	cin >> n >> k;
	int pw = (1 << n) - 1;
	if (k < pw || k == pw + 1) {
		cout << "N";
	} else {
		cout << "Y\n";
		int diff = k - pw;
		if (diff & 1) {
			cout << "A B\nB C\nC A\n";
			diff -= 3; 
		}
		for (int i = 0; i < diff / 2; i++) {
			cout << "A B\nB A\n";
		}
		hanoy(n, 'A', 'B', 'C');
	}
	return 0;
}