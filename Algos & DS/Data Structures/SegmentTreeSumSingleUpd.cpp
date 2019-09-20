#include <bits/stdc++.h>

using namespace std;

typedef long long nis;

const int N = (int) 1e6 + 7;

nis a[N], t[N * 4];

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

nis get(int v, int tl, int tr, int l, int r) {
  if (l <= tl && r >= tr) {
    return t[v];
  }
  if (l > tr || r < tl) {
    return 0;
  }
  int tm = (tl + tr) >> 1;
  return get(v + v, tl, tm, l, r) + get(v + v + 1, tm + 1, tr, l, r);
}

void upd(int v, int tl, int tr, int idx, nis val) {
  if (tl == tr) {
    t[v] = val;
  } else {
    int tm = (tl + tr) >> 1;
    if (idx <= tm) {
      upd(v + v, tl, tm, idx, val);
    } else {
      upd(v + v + 1, tm + 1, tr, idx, val);
    }
    t[v] = t[v + v] + t[v + v + 1];
  }
}

int main() {
  
  return 0;
}
