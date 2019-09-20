#include <bits/stdc++.h>
 
using namespace std;
 
vector<int> prefix(string& s) {
	int len = int(s.size());
	vector<int> pi(len);
	pi[0] = 0;
	for (int i = 1; i < int(s.size()); i++) {
		int j = pi[i - 1];
		while(j > 0 && s[i] != s[j]) {
			j = pi[j - 1];
		}
		if (s[i] == s[j]) {
			pi[i] = j + 1;
		} else {
			pi[i] = j;
		}
	}
	return pi;
}
 
int main() {
	string s;
	cin >> s;
	vector<int> pi = prefix(s);
	for (int i = 0; i < int(pi.size()); i++) {
    	int x = pi[i];
    	cout << x << " ";
	}
	return 0;
}