#include <bits/stdc++.h>
 
using namespace std;
 
const int N = (int) 1e6 + 7;

int n, last[N], t[N * 4], a[N], ans[N];
vector<vector<pair<int, int>>> query(N);

void upd(int v, int tl, int tr, int idx, int val) {
  if (tl == tr) {
    t[v] = val;
  } else {
    int tm = (tl + tr) >> 1;
    if (idx <= tm)
      upd(v + v, tl, tm, idx, val);
    else
      upd(v + v + 1, tm + 1, tr, idx, val);
    t[v] = t[v + v] + t[v + v + 1];
  }
}

int get(int v, int tl, int tr, int l, int r) {
  if (l <= tl && r >= tr)
    return t[v];
  if (l > tr || r < tl)
    return 0;
  int tm = (tl + tr) >> 1;
  return get(v + v, tl, tm, l, r) + get(v + v + 1, tm + 1, tr, l, r);
}

int main() {
  int q;
  cin >> n >> q;
  set<int> qq;
  map<int, int> val;
  int ct = 0;
  for (int i = 1; i <= n; i++)
    cin >> a[i], qq.insert(a[i]);
  for (auto x : qq)
    val[x] = ++ct;
  for (int i = 1; i <= n; i++)
    a[i] = val[a[i]];
  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    query[r].push_back(make_pair(l, i));
  }
  for (int i = 1; i <= n; i++) {
    if (last[a[i]] == 0) {
      last[a[i]] = i;
      upd(1, 1, n, last[a[i]], 1);
    } else {  
      upd(1, 1, n, last[a[i]], 0);
      last[a[i]] = i;
      upd(1, 1, n, last[a[i]], 1);
    }
    for (auto x : query[i]) {
      ans[x.second] = get(1, 1, n, x.first, i);
    }                
  }
  for (int i = 0; i < q; i++)
    cout << ans[i] << '\n';     
  return 0;
}