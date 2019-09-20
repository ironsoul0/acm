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
 
#define all(c) c.begin(),c.end()
 
int p[SIZE], h[SIZE];
 
struct edge {
	int u, v, len;
};
 
bool operator < (edge one, edge two) {
	return one.len < two.len;
}
 
void build() {
	for (int i = 0; i < SIZE; i++) {
		p[i] = i;
		h[i] = 0;
	}
}
 
int get_root(int v) {
	if (p[v] == v) return v;
		else
	return p[v] = get_root(p[v]);
}
 
bool merge(int u, int v) {
	int a = get_root(u), b = get_root(v);
	if (a == b) {
		return false;
	} else {
  	if (h[a] < h[b]) {
  		p[a] = b;
    } else if (h[a] > h[b]) {
     	p[b] = a;
    } else {
    	p[b] = a;
    	h[a]++;
		}   
		return true;
	}
}
 
 
int main() {
	int n, m;
	cin >> n >> m;
	edge a[m];
	for (int i = 0; i < m; i++) {
		cin >> a[i].u >> a[i].v >> a[i].len;
	}
	build();
	sort(a, a + m);
	int weight = 0;
	for (int i = 0; i < m; i++) {
		if (merge(a[i].u, a[i].v)) {
			weight += a[i].len;
		}
	}
	cout << weight;
	return 0;
}