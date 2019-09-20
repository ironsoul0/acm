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

bool good(string s) {
	stack<char> q;
	for (int i = 0; i < sz(s); i++) {
		if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
			q.push(s[i]);
		} else {
			if (q.empty()) return 0;
			char c = q.top();
			if (s[i] == ')' && c != '(') return 0;
			if (s[i] == ']' && c != '[') return 0;
			if (s[i] == '}' && c != '{') return 0;	
			q.pop();
		}
	}
	return q.empty();
}

int main() {
	freopen("check.in", "r", stdin);
	freopen("check.out", "w", stdout);
	string s;

	cin >> s;

	if (good(s)) {
		puts("YES");
	} else {
		puts("NO");
	}

	return 0;
}