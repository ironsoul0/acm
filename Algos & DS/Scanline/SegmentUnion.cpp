#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

const int INF = 2e9;
const int SIZE = 2e5;
const double EPS = 1e-8;

#define sz(s) int(s.size())

#define pii pair<int, int>

#define mp make_pair
#define pb push_back

#define fi first
#define se second

#define all(c) c.begin(), c.end()

/*
–еша€ задачу из контрольной по математике, ¬ас€ получил ответ в виде объединени€ от-
резков
на числовой пр€мой. ќднако, некоторые из этих отрезков могут пересекатьс€ друг с
другом, что не слишком нравитс€ ¬асе. ¬аша задача Ч представить ¬асин ответ в виде объединени€
минимального количества отрезков.
*/

int main() {
	freopen("merge.in", "r", stdin);
	freopen("merge.out", "w", stdout);
	
	int n;
	cin >> n;
	vector<pii> points(n * 2);
	
	for (int i = 0; i < n * 2; i++) {
		cin >> points[i].fi;
		points[i].se = (i + 1) % 2 == 0 ? 1 : -1;
	}
	
	vector<pii> total;
	pii ans;
	int cnt = 0;

	sort(all(points));

	for (int i = 0; i < n * 2; i++) {
     	int type = points[i].se;
     	cnt -= type;	
		if (type == -1 && cnt == 1) {
			ans.fi = points[i].fi;
		}
		if (type == 1 && cnt == 0) {
			ans.se = points[i].fi;
			total.pb(ans);
		}     	
	}

	cout << sz(total) << '\n';
	for (auto elem : total) {
		cout << elem.fi << " " << elem.se << '\n';
	}
	
	return 0;
}