#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-6;

struct Vector {
	double x, y;
	Vector() {
	}
	Vector(double _x, double _y) {
		x = _x;
		y = _y;
	}
	double length() {
		return sqrt(x * x + y * y);
	}
};                                         

struct Line {
	double a, b, c;
	Line(Vector f, Vector s) {
		a = f.y - s.y;
		b = s.x - f.x;
		c = (s.y - f.y) * s.x + (f.x - s.x) * s.y;
	}
	double dist(Vector v) {
		return abs((a * v.x + b * v.y + c) / (sqrt(a * a + b * b)));
	}
	bool inside(Vector v) {
		return (abs((a * v.x + b * v.y + c )) < EPS);
	}              
};

double dot_product(Vector one, Vector two) {
	return one.x * two.x + one.y * two.y;
}

double cross_product(Vector one, Vector two) {
	return one.x * two.y - two.x * one.y;
}

double angle(Vector one, Vector two) {
	return abs(atan2(cross_product(one, two), dot_product(one, two))) * 180.000 / acos(-1);
}

Vector operator - (Vector f, Vector s) {
	return Vector(s.x - f.x, s.y - f.y);
}

istream &operator >>(istream &in, Vector& s) {
	in >> s.x >> s.y;
	return in; 
}

int main() {
	return 0;
}