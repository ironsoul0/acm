#include <bits/stdc++.h>
 
using namespace std;
 
const double EPS = 1e-9;
 
struct Vector {
    double x, y;
    Vector() {
    }
    Vector(double _x, double _y) {
        x = _x;
        y = _y;
    }
    double length() {
        return hypot(x, y);
    }
};
 
Vector operator - (Vector f, Vector s) {
    return Vector(s.x - f.x, s.y - f.y);
}
 
double dot_product(Vector f, Vector s) {
    return f.x * s.x + f.y * s.y;
}
 
double cross_product(Vector f, Vector s) {
    return f.x * s.y - s.x * f.y;
}
 
double angle(Vector f, Vector s) {
    return abs(atan2(cross_product(f, s), dot_product(f, s)));
}
 
istream& operator >> (istream &in, Vector& v) {
    in >> v.x >> v.y;
    return in;
}
 
bool operator == (Vector f, Vector s) {
    return (abs(f.x - s.x) < EPS && abs(f.y - s.y) < EPS);
}
 
int main() {
    Vector a, b, c, d;
    cin >> a >> b >> c >> d;
 
    if (d == a || d == b || d == c) {
        puts("In");
        return 0;
    }
     
    double fi = angle(d - a, d - b);
    double se = angle(d - a, d - c);
    double th = angle(d - b, d - c);
 
    if (abs(fi + se + th - acos(-1) * 2) < EPS) {
        puts("In");
    } else {
        puts("Out");
    }
    return 0;
}