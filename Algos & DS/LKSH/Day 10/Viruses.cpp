#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 1e6 + 7;
const int K = 26;

/**
Можно ли составить строку из 0 и 1, что в ней не встречаются строки из набора как подстроки.
**/

struct node {
	int next[K];
	bool leaf;
	int p;
	char last;
	int suffix_link;
	int go[K];
	int up;
};

node t[N];
int size = 1;

void init(int v = 0) {
	for (int i = 0; i < K; i++)
		t[v].next[i] = t[v].go[i] = -1;			
	t[v].suffix_link = t[v].up = -1;
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
	t[v].leaf = true;
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

int get_up(int v) {
	if (t[v].up == -1) {
		int link = get_suffix_link(v);
		if (t[v].leaf)
			t[v].up = v;
		else if (t[link].leaf)
			t[v].up = link;
		else if (link == 0)
			t[v].up = link;
		else
			t[v].up = get_up(link);
	}
	return t[v].up;
}

int used[N];
bool cycle = false;

void dfs(int v = 0) {
	used[v] = 1;
	for (char c = 'a'; c <= 'b'; c++) {
		int cur = build_go(v, c);
		if (get_up(cur) != 0) continue;	
		if (used[cur] == 1) {
			cycle = true;
		} else if (!used[cur]) {
			dfs(cur);
		}
	}
	used[v] = 2;
}

int main() {
	ios_base::sync_with_stdio(0);
	int n;
	cin >> n;                                                    
	init();
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (auto &x : s) {
			if (x == '0') 
				x = 'a';
			else
				x = 'b';
		}
		add(s, i);
	}				
	dfs();
	if (cycle)
		cout << "TAK";
	else
		cout << "NIE";
	return 0;	
} 