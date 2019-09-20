#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 1e6 + 7;
const int K = 26;
const int MOD = (int) 1e4;

/**
—колько существует различных подозрительных слов длины n, дл€ данного словар€ слов.
ѕодозрительное слово - слово, в котором встречаетс€ строка из словар€ как подстрока.
–ешим обратную задачу и найдем количество строк длины n, которые не содержат в себе слова из словар€ как подстроки.
—читаетс€ через ƒѕ на матрице
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

void add(string& s) {
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

struct matrix {
	int row, col;
	vector<vector<int>> a;
	matrix(vector<vector<int>> b) {
		a = b;
		row = (int) a.size();
		col = (int) a[0].size();
	}
	matrix() {
	}		
};

matrix operator * (matrix a, matrix b) {
	assert(a.col == b.row);
	vector<vector<int>> result;
	result.resize(a.row);
	for (int i = 0; i < a.row; i++)
		result[i].resize(b.col);
	for (int i = 0; i < a.row; i++) {
		for (int j = 0; j < b.col; j++) {
			for (int k = 0; k < a.col; k++) {
				result[i][j] += a.a[i][k] * b.a[k][j];
				result[i][j] %= MOD;
			} 
		}
	}	
	return matrix(result);
}

vector<vector<int>> d(N);
int used[N];

void dfs(int v = 0) {
	used[v] = 1;
	for (char c = 'a'; c <= 'z'; c++) {
		int next_go = build_go(v, c);		
		if (get_up(next_go) > 0) continue;	
		d[next_go].push_back(v);		
		if (!used[next_go])
			dfs(next_go);
	}
}

matrix bin_pow(matrix a, int n) {
	matrix result = a;
	n--;
	while (n) {
		if (n & 1) {
			result = result * a;
			n--;
		} else {
			a = a * a;
			n >>= 1;
		}
	}
	return result;
}

int bpow(int a, int n) {
	int result = 1;
	while (n) {
		if (n & 1) {
			result *= a;
			result %= MOD;
			n--;
		} else {
			a *= a;
			a %= MOD;
			n >>= 1;
		}
	}
	return result;
}

void print(int n, int final_sum) {
	int x = bpow(26, n);
	x -= final_sum;
	x %= MOD;
	if (x < 0) x += MOD;
	cout << x;
}

int main() {
	ios_base::sync_with_stdio(0);
	init();
	int n, k;
	cin >> n >> k;
	while (k--) {
		string s;
		cin >> s;
		add(s);
	}	
	dfs();
	vector<vector<int>> start;
	start.resize(size);	
	for (int i = 0; i < size; i++)
		start[i].resize(1);
	start[0][0] = 1;
	vector<vector<int>> multiply;
	multiply.resize(size);
	for (int i = 0; i < size; i++)
		multiply[i].resize(size);
	for (int i = 0; i < size; i++) {
		for (auto x : d[i]) {
			multiply[i][x]++;
		}
	}
	matrix ready = bin_pow(matrix(multiply), n);
	ready = ready * matrix(start);
	int final_sum = 0;
	for (int i = 0; i < size; i++) {
		final_sum += ready.a[i][0];
		final_sum %= MOD;
	}
	print(n, final_sum);
	return 0;	
}     