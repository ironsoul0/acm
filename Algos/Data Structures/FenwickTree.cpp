#include <bits/stdc++.h>
 
using namespace std;
 
const int N = (int) 1e6 + 7;

int n, a[N], f[N];  
 
int sum(int x) {
  int result = 0;
  for (; x >= 0; x = (x & (x + 1)) - 1)
    result += f[x];
  return result;
}
 
int sum(int l, int r) {
  if (l == 0) 
    return sum(r);
  else
    return sum(r) - sum(l - 1);
}
 
void modify(int idx, int delta) {
  a[idx] += delta;
  for (; idx < N; idx |= idx + 1)
    f[idx] += delta;
}
 
int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    int t;
    cin >> t;
    increase(i, t);
  }
  return 0;
}