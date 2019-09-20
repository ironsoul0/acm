#include <bits/stdc++.h>
  
using namespace std;

typedef long long ll;
  
const int N = (int) 1e3 + 7;
const int M = (int) 1e9 + 7;

ll dp[N][N];

void precalc() {
  for (int i = 0; i < N; i++)
    dp[i][0] = 1;
  for (int i = 1; i < N; i++)
    for (int j = 1; j < N; j++)
      dp[i][j] = sum(dp[i - 1][j], dp[i - 1][j - 1]);
}

int main() {
  precalc();
  int n, m;
  cin >> n >> m;
  cout << dp[n][m]; ///Число сочетаний из n по m  
  return 0;
}