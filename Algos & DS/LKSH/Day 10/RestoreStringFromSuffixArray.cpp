#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 1e6 + 7;
const int K = 26;

int main() {
	ios_base::sync_with_stdio(0);
	int n;
	cin >> n;
	string s;
	cin >> s;
	sort(s.begin(), s.end());
	vector<int> a(n);
	string result(n, ' ');
	for (int i = 0; i < n; i++) {
		cin >> a[i];	
		result[a[i] - 1] = s[i];
	}
	vector<pair<string, int>> b;
	for (int i = n - 1; i >= 0; i--) {
		string suffix;
		for (int j = i; j <= n - 1; j++)
			suffix += result[j];
		b.push_back(make_pair(suffix, i + 1));		
	}
	sort(b.begin(), b.end());
	for (int i = 0; i < n; i++) {
		if (b[i].second != a[i]) {
			cout << "No";
			return 0;
		}
	}
	cout << result;
	return 0;	
}    