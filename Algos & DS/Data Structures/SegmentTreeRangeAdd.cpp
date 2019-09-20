#include <bits/stdc++.h>
 
using namespace std;
 
const int N = (int) 1e6 + 7;
 
typedef long long nis;
 
nis a[N], t[N * 4], z[N * 4];
 
void build(int v, int tl, int tr) {
  if (tl == tr) {
    t[v] = a[tl];
  } else {  
    int tm = (tl + tr) >> 1;
    build(v + v, tl, tm);
    build(v + v + 1, tm + 1, tr);
    t[v] = t[v + v] + t[v + v + 1];
  }
}
 
void push(int v, int tl, int tr) {
  if (z[v] != 0 && v + v + 1 < N * 4) {
    int tm = (tr + tl) >> 1;
    t[v + v] += (tm - tl + 1) * 1ll * z[v];
    t[v + v + 1] += (tr - tm) * 1ll * z[v];
    z[v + v] += z[v];
    z[v + v + 1] += z[v];
    z[v] = 0;
  }
}
 
void add(int v, int tl, int tr, int l, int r, nis val) {
  if (l <= tl && r >= tr) {
    t[v] += (tr - tl + 1) * 1ll * val;  
    z[v] += val;
    return;
  }
  if (l > tr || r < tl) {
    return;
  }
  int tm = (tl + tr) >> 1;
  push(v, tl, tr);
  add(v + v, tl, tm, l, r, val);
  add(v + v + 1, tm + 1, tr, l, r, val);
  t[v] = t[v + v] + t[v + v + 1]; 
}
 
nis get(int v, int tl, int tr, int idx) {
  if (tl == tr) {
    return t[v];  
  } else {
    int tm = (tl + tr) >> 1;
    push(v, tl, tr);
    if (idx <= tm) {
      get(v + v, tl, tm, idx);
    } else {
      get(v + v + 1, tm + 1, tr, idx); 
    } 
  }
}
 
int main() {
  
  return 0;
}