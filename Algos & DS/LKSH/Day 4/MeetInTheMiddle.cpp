#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 1e2 + 7;
const double EPS = (double) 1e-6;
const int P = (int) 1e5 + 7;
const int64 BIG = (int64) 1e18 + 7;

/**
ƒано небольшое количество предметов, около 32. 
” каждого есть стоимость и вес.
Ќужно насобирать вещи с наибольшей стоимостью и уложитьс€ в отрезок веса [L, R].
»спользуес€ трюк meet-in-the-middle.
–ешив одну часть задачи за полный перебор (2^16) мы будем ее использовать дл€ решени€ другой части. »спользую дерево отрезков,
чтобы находить максимум на отрезке, в который нужно уложитьс€.
**/

#define fs first
#define sc second

struct item {
	int64 w, v;
	int mask;
};

int n;
int64 l, r, w[N], v[N];
pair<int64, int> t[P * 4];
vector<item> value;

void modify(int v, int tl, int tr, int index, int64 value) {
	if (tl == tr) {
		t[v] = make_pair(value, tl);
	} else {
		int tm = (tl + tr) >> 1;
		if (index <= tm)
			modify(v + v, tl, tm, index, value);
		else
			modify(v + v + 1, tm + 1, tr, index, value);
		t[v] = max(t[v + v], t[v + v + 1]);
	}
}

pair<int64, int> get(int v, int tl, int tr, int l, int r) {
	if (l <= tl && r >= tr)
		return t[v];
	if (l > tr || r < tl)
		return make_pair(-BIG, -1);
	int tm = (tl + tr) >> 1;
	return max(get(v + v, tl, tm, l, r), get(v + v + 1, tm + 1, tr, l, r));
}

bool operator < (item a, item b) {
	return a.w < b.w;	
}

int main() {
	freopen("dowry.in", "r", stdin);
	freopen("dowry.out", "w", stdout);
	cin >> n >> l >> r;
	for (int i = 0; i < n; i++)
		cin >> w[i] >> v[i];
	int first = n / 2;
	for (int mask = 0; mask < (1 << first); mask++) {
		item cur;
		cur.mask = mask, cur.w = 0, cur.v = 0;	
		for (int bit = 0; bit < first; bit++) {
			if (mask & (1 << bit)) {
				cur.w += w[bit];
				cur.v += v[bit];
			}
		}	
		value.push_back(cur);
	}
	sort(value.begin(), value.end());
	int tt = (int) value.size();
	for (int i = 0; i < tt; i++)
		modify(1, 1, tt, i + 1, value[i].v);
	int second = n - first;
	int64 ans = 0;
	int mask1 = 0, mask2 = 0;
	for (int mask = 0; mask < (1 << second); mask++) {
		int64 cur_w = 0, cur_v = 0;
		for (int bit = 0; bit < second; bit++) {
			int now = bit + first;
			if (mask & (1 << bit)) {
				cur_w += w[now];
				cur_v += v[now];
			}
		}
		int64 new_l = l - cur_w, new_r = r - cur_w;
		item cur;
		cur.w = new_l;
		int l_i = lower_bound(value.begin(), value.end(), cur) - value.begin();
		cur.w = new_r;
		int r_i = upper_bound(value.begin(), value.end(), cur) - value.begin() - 1;
		if (l_i <= r_i && l_i < (int) value.size() && r_i >= 0) {
			pair<int64, int> h = get(1, 1, tt, l_i + 1, r_i + 1);
			if (h.first + cur_v > ans) {
				ans = h.first + cur_v;
				mask1 = value[h.second - 1].mask;
				mask2 = mask;
			}			
		}
	}
	vector<int> res;
	for (int i = 0; i < first; i++)
		if (mask1 & (1 << i)) res.push_back(i + 1);
	for (int i = 0; i < second; i++)
		if (mask2 & (1 << i)) res.push_back(first + i + 1);
	cout << res.size() << '\n';
	for (auto x : res)
		cout << x << ' ';
	return 0;	
}   