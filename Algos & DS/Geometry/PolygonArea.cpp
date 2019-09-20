#include <bits/stdc++.h>
 
using namespace std;
 
struct Vector {
    float x, y;
    Vector() {
    }
    Vector(float _x, float _y) {
        x = _x;
        y = _y;
    }
    float length() {
        return hypot(x, y);
    }
};
 
Vector operator - (Vector f, Vector s) {
    return Vector(s.x - f.x, s.y - f.y);
}
 
istream& operator >> (istream& in, Vector& v) {
    in >> v.x >> v.y;
    return in;
}
 
float cross_product(Vector f, Vector s) {
    return f.x * s.y - s.x * f.y;
}
 
float area(Vector f, Vector s) {
    return cross_product(f, s) * 0.5;
}
 
int main() {
    int n;
    float total = 0.0;
    scanf("%d", &n);
    vector<Vector> v(n);
 
    for (auto &x : v) {
        scanf("%f %f", &x.x, &x.y);
    }
     
    v.push_back(v.front());
    Vector point = v.front();
    v.erase(v.begin());
 
    for (int i = 0; i < int(v.size()) - 1; ++i) {
        total += area(v[i] - point, v[i + 1] - point);
    }
    printf("%.1f", abs(total));
    return 0;
}