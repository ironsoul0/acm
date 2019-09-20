#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 1e6 + 7;
const int K = 26;

/**
Для каждой строки из набора сказать встречается ли она в тексте
**/

struct node {
	int next[K];
	vector<int> leaf;
	int p;
	char last;
	int suffix_link;
	int go[K];
};

node t[N];
int size = 1;
int cnt[N];

void init(int v = 0) {
	for (int i = 0; i < K; i++)
		t[v].next[i] = t[v].go[i] = -1;			
	t[v].suffix_link = -1;
}

void add(string& s, int y) {
	int v = 0;
	for (auto c : s) {
		int index = c - 'a';
		if (t[v].next[index] == -1) {
			init(size);
			t[size].p = v;
			t[size].last = c;
			t[v].next[index] = size;
			size++;
		}
		v = t[v].next[index];
	}
	t[v].leaf.push_back(y);
}

int build_go(int v, char c);

int get_suffix_link(int v) {
	if (t[v].suffix_link == -1) {
		if (v == 0 || t[v].p == 0)
			t[v].suffix_link = 0;
		else 	
			t[v].suffix_link = build_go(get_suffix_link(t[v].p), t[v].last);
	}
	return t[v].suffix_link;
}

int build_go(int v, char c) {
	int index = c - 'a';
	if (t[v].go[index] == -1) {
		if (t[v].next[index] != -1) {
			t[v].go[index] = t[v].next[index];
		} else {
			if (v == 0)
				t[v].go[index] = 0;
			else
				t[v].go[index] = build_go(get_suffix_link(v), c);
		}		
	}
	return t[v].go[index];
}

bool used[N];

int main() {
	ios_base::sync_with_stdio(0);
	int n;
	cin >> n;
	init();
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		add(s, i);
	}			
	int v = 0;
	string text;
	cin >> text;
	for (auto x : text) {
		v = build_go(v, x);
		if (!used[v]) {
			for (auto y : t[v].leaf)
				cnt[y]++;
			int cur = v;	
			while (cur > 0) {
				cur = get_suffix_link(cur);
				used[cur] = true;
				for (auto y : t[cur].leaf)
					cnt[y]++;
			}
			used[v] = true;
		}
	}
	for (int i = 0; i < n; i++) {
		if (cnt[i] > 0)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;	
}         