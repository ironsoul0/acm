#include <bits/stdc++.h>
  
using namespace std;
  
typedef long long ll;
  
const int MOD = (int) 1e9 + 7;
const int N = (int) 1e6 + 7;
  
int a[N];
 
int main() {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    ios_base::sync_with_stdio(0);
    int m, n;
    ll all = 0;
    cin >> n >> m;  
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        all += a[i] + a[i];
    }
    if (all < n) {
        cout << -1;
        return 0;
    }
    unordered_map<int, int> can;
    for (int i = 0; i < m; i++) {
        unordered_map<int, int> cur = can;
        if (a[i] <= n) {
            if (can.count(a[i]) == 0 || can[a[i]] > 1) 
                cur[a[i]] = 1;
        }
        if (a[i] * 2 <= n) {
            if (can.count(a[i] * 2) == 0 || can[a[i] * 2] > 2) 
                cur[a[i] * 2] = 2;
        }
        for (auto w : can) {
            int x = w.first, sum = x + a[i];
            if (sum <= n) {
                if (cur.count(sum) == 0 || can[x] + 1 < cur[sum])
                    cur[sum] = can[x] + 1;
            }
            sum += a[i];
            if (sum <= n) {
                if (cur.count(sum) == 0 || can[x] + 2 < cur[sum])
                    cur[sum] = can[x] + 2;
            }
        }
        can = cur;
    }   
    if (n & 1) {
    	cout << "huy";
    	return 0;
    }
    cout << can[n];
    return 0;
}