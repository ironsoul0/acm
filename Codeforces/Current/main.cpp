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
const int N = (int) 1e5 + 7;
const ll INF = (ll) 1e18 + 7;

#define f first
#define s second

vector<int> a(N), occ(N), s(N);
int sum = 0, n;

int getAns(int x) {
	int cur = 0, ans = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] == 1) {
			occ[cur] = i;
			s[cur] = (cur ? s[cur - 1] : 0) + occ[cur];
			cur++;
		}
		if (cur == x) {
			int mid = cur / 2, mid2 = (cur - 1) / 2;
			int add = INT_MAX;

			{
				int lt = s[mid], nm = mid + 1;
				int gt = s[cur - 1] - s[mid], gm = cur - nm;
				add = min(add, occ[mid] * nm - lt + gt - occ[mid] * gm);
			}
			mid = mid2;
			{
				int lt = s[mid], nm = mid + 1;
				if (nm <= cur) {
				int gt = s[cur - 1] - s[mid], gm = cur - nm;
				add = min(add, occ[mid] * nm - lt + gt - occ[mid] * gm);
				}
			}

			ans += add;
			cur = 0;
		}
	}
	for (int i = 0; i < n; i++) {
		s[i] = 0;
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif	
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		sum += a[i];
	}
	int ans = INT_MAX;
	for (int i = 2; i <= sum; i++) {
		if (sum % i) continue;
		ans = min(ans, getAns(i));
	}
	if (sum % 2 == 0) {
		int prev = -1, ans2 = 0;
		for (int i = 0; i < n; i++) {
			if (a[i] == 1) {
				if (prev == -1) 
					prev = i; 
				else {
					ans2 += i - prev;
					prev = -1;
				}
			}
		}
		ans = min(ans, ans2);
	}
	cout << (ans == INT_MAX ? -1 : ans);
	return 0;
}