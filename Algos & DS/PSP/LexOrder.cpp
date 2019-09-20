#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

const int INF = 2e9;
const int SIZE = 2e5;

#define sz(s) int(s.size())

#define pii pair<int, int>

#define mp make_pair
#define pb push_back

#define fi first
#define se second

#define all(c) c.begin(), c.end()

/*
Выведите все правильные скобочные последовательности заданной длины в лексикографическом
порядке.
*/

int n;

void gen(string prefix = "", int open = 0, int close = 0) {
	if (open + close == n * 2 && open == close) {
		printf("%s\n", prefix.c_str());
	} else if (open + close < 2 * n) {
		gen(prefix + '(', open + 1, close);
		if (close < open) {
			gen(prefix + ')', open, close + 1);
		}	
	}
}

int main() {
	freopen("lexical.in", "r", stdin);
	freopen("lexical.out", "w", stdout);
	
	scanf("%d", &n);
	gen();
	return 0;
}