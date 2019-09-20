#include <bits/stdc++.h>
 
using namespace std;
 
const int N = (int) 5e3 + 7;

int n, m;
int a[N][N];  
int f[N][N];  
 
int sum(int x, int y) {
  if (x < 0 || y < 0) {
    return 0;
  }
  int result = 0;
  for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
    for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
      result += f[i][j];
    }
  }
  return result;
}
 
int sum(int x1, int y1, int x2, int y2) {
    return sum(x2, y2)
    - sum(x1 - 1, y2)
    - sum(x2, y1 - 1)
    + sum(x1 - 1, y1 - 1);
}
 
void increase(int x, int y, int delta) {
  a[x][y] += delta;
  for (int i = x; i < n; i |= i + 1) {
    for (int j = y; j < m; j |= j + 1) {
      f[i][j] += delta;
    }
  }
}
 
int main() {
  
  return 0;
}