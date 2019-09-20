#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int N = (int) 1e6 + 7;
const double EPS = (double) 1e-6;

#define fs first
#define sc second

struct point {
	long long x, y;
	int i;	
};

double distance(point a, point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

long long get_area(point a, point b, point c) {
	return a.x * b.y + b.x * c.y + c.x * a.y - a.y * b.x - b.y * c.x - c.y * a.x;
}

bool ccw(point a, point b, point c) {
	return get_area(a, b, c) > 0;
}

point first;

bool less_of_ccw(point a, point b) {
	if (a.i == first.i) return true;
	if (b.i == first.i) return false;
	if (ccw(first, a, b)) return true;
	if (ccw(first, b, a)) return false;
	return distance(first, a) > distance(first, b);
}

vector<point> convex_hull(vector<point> p) {
	vector<int> ip;
	int n = (int) p.size();
	for (int i = 0; i < n; i++)
		p[i].i = i;
	first = p[0];
	for (int i = 1; i < n; i++)
		if (first.x > p[i].x || (first.x == p[i].x && first.y > p[i].y))
			first = p[i];
	sort(p.begin(), p.end(), less_of_ccw);
	ip.push_back(0);
	int i = 0;
	for (i = 1; i < n && abs(get_area(p[0], p[1], p[i])) <= 0; i++) {
		continue;
	}
	int top = 1;	
	ip.push_back(1);
	while (i < n) {
		if (!ccw(p[ip[top - 1]], p[ip[top]], p[i])) {
			--top;
			ip.pop_back();
		} else {
			++top;
			ip.push_back(i);
			++i;
		}
	}
	vector<point> result;
	for (auto i : ip)
		result.push_back(p[i]);
	int k = (int) result.size();
	if (!ccw(result[k - 2], result[k - 1], result[0]))
		result.pop_back();
	return result;
}

long long polygon(vector<point> p) {
	long long result = 0;
	point a = p[0];
	int n = (int) p.size();
	for (int i = 0; i < n; i++) {
		point b = p[i], c = p[(i + 1) % n];
		result += abs(get_area(a, b, c));
	}
	return result;
}

int main() {
	ios_base::sync_with_stdio(0);
	int n;
	cin >> n;
	vector<point> all(n);
	for (int i = 0; i < n; i++)
		cin >> all[i].x >> all[i].y;
	vector<point> result = convex_hull(all);
	long long area = polygon(result);
	cout << result.size() << '\n';
	for (point p : result) {
		cout << p.x << ' ' << p.y << '\n';
	}
	if (area & 1ll) {
		cout << area / 2 << ".5";
	} else {
		cout << area / 2 << ".0";
	}
	return 0;	
}  