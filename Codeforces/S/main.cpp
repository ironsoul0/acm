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
 
#define f first
#define s second
 
typedef long long ll;
typedef pair<ll, ll> pii;
 
const int MOD = (int) 1e9 + 7;
const int N = (int) 1e6 + 7;
const ll INF = (ll) 1e18 + 7;
 
ll overlap(pii b1, pii e1, pii b2, pii e2) {
	ll farea = abs(b1.f - e1.f) * 1ll * abs(b1.s - e1.s);
	ll sarea = abs(b2.f - e2.f) * 1ll * abs(b2.s - e2.s);
 
	ll iArea = max(0ll, (min(e1.f, e2.f) - max(b1.f, b2.f))) * max(0ll, (min(e1.s, e2.s) - max(b1.s, b2.s)));  
	return iArea;
}
 
int main() {
	ios_base::sync_with_stdio(0);
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
	pii b1, e1;
	cin >> b1.f >> b1.s >> e1.f >> e1.s;
	pii b2, e2;
	cin >> b2.f >> b2.s >> e2.f >> e2.s;
	pii b3, e3;
	cin >> b3.f >> b3.s >> e3.f >> e3.s;
	ll totalArea = abs(b1.f - e1.f) * 1ll * abs(b1.s - e1.s);
	ll overlapArea = overlap(b1, e1, b2, e2) + overlap(b1, e1, b3, e3) - overlap(b2, e2, b3, e3);
	//cout << totalArea << ' ' << overlap(b1, e1, b2, e2) << endl;
	if (totalArea > overlapArea) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
	}
	return 0;
}