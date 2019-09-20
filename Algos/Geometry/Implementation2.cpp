#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const ll N = (ll)(5e5) + 322;
const ll INF = (ll)(1e18);
const ll mod = (ll)(1e9) + 7;

ll n, x, y, sx, sy;
double mx, mn = INF;

const double eps = 1e-8;
const double pi = 3.14159265358979323;
// ���������� ����� �������� ���� �����
long long gcd (long long a, long long b)
{
    a = (a < 0 ? - a : a);
    b = (b < 0 ? - b : b);
    while (a && b)
        if (a > b) a %= b;
        else b %= a;
    return a + b;
}

//*********************** ��������� ������ ************************************
// �����
class point
{
public: 
    double x, y;
    // �������������� �������� - ������ �����
    int i;
    // �������� ����� (_x, _y)
    point(double _x, double _y) 
    {
        x = _x;
        y = _y;
    }
    // �������� ����� (0, 0)
    point()
    {
        point(0, 0);  
    }
};

// ������
class line
{
public: 
    double a, b, c;
    // �������� ������ ax + by + c = 0
    line(double _a = 0, double _b = 0, double _c = 0) 
    {
        a = _a;
        b = _b;
        c = _c;
    }
};
class circle
{
public: 
    point c;
    double r;
    // �������������� ������
    double alpha;

    // �������� ���������� � ������� (x, y) � �������� _r
    circle (double x, double y, double _r)
    {
       c = point(x, y);
       r = _r;
    }
    // �������� ���������� � ������� p � �������� _r
    circle (point p, double _r)
    {
        c = p;
        r = _r;
    }
    circle ()
    {
       circle(0, 0, 0);
    }
};
// ��������� ���� ����� �� �������� ����� ������ �� ����� �����
class less_of_posXY
{
public :
    bool operator () (point a, point b)
    {
        if (abs (a.x - b.x) > eps)
            return a.x < b.x;

        if (abs (a.y - b.y) <= eps) return false;
        return a.y < b.y;
    }
};
// ��������� ���� �����
class equal_point 
{
public :
    bool operator () (point a, point b)
    {
        return abs (a.x - b.x) <= eps && abs (a.y - b.y) <= eps;
    }
};
//-----------------------------------------------------------------------------
//*********************** ������� ��� ������ � ������� ************************
//-----------------------------------------------------------------------------
// ���������� ����� ����� �������
double dist(point a, point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
// ����� �� ����� � ��������������, ������� �������� �������� �����
bool point_in_box (point t, point p1, point p2)
{
    return  (abs (t.x - min(p1.x, p2.x)) <= eps || min(p1.x, p2.x) <= t.x) && 
            (abs (max(p1.x, p2.x) - t.x) <= eps || max(p1.x, p2.x) >= t.x) && 
            (abs (t.y - min(p1.y, p2.y)) <= eps || min(p1.y, p2.y) <= t.y) && 
            (abs (max(p1.y, p2.y) - t.y) <= eps || max(p1.y, p2.y) >= t.y);
}
// �������� ����� �� ���� �����
point min_px (point a, point b)
{
        return a.x < b.x || (abs (a.x - b.x) <= eps && a.y < b.y) ? a : b;
}
// �������� ������ �� ���� �����
point max_px (point a, point b)
{
        return a.x > b.x || (abs (a.x - b.x) <= eps && a.y > b.y) ? a : b;
}
// �������� ������ �� ���� �����
point min_py (point a, point b)
{
        return a.y < b.y || (abs (a.y - b.y) <= eps && a.x < b.x) ? a : b;
}
// �������� ������� �� ���� �����
point max_py (point a, point b)
{
        return a.y > b.y || (abs (a.y - b.y) <= eps && a.x > b.x) ? a : b;
}

// �������� ���� �����
double polar_angle (point p)
{
    double alpha = atan2(p.y, p.x);
    if (alpha < 0) alpha += 2 * pi;
    return alpha;
}
// �������� ����������
double polar_dist (double alpha, double r1, double betta, double r2)
{
    point p1 = point (r1 * cos (alpha), r1 * sin (alpha));
    point p2 = point (r2 * cos (betta), r2 * sin (betta));
    return dist (p1, p2);
}
// ������� :: ������� ������� � �������� ���������
point part_segment (point p1, point p2, double m, double n)
{
    point t;
    t.x = (p1.x * n + p2.x * m) / (m + n);
    t.y = (p1.y * n + p2.y * m) / (m + n);
    return t;
}
// ������� ����� �� �������� ���� ������ ������ ���������
point turn (point p, double alpha)
{
    double c = cos(alpha);
    double s = sin(alpha);
    return point (p.x * c - p.y * s, p.x * s + p.y * c);
}
// ������� ����� �� �������� ���� ������ �������� �����
point turn_of (point p, double alpha, point c)
{
    point t = turn (point (p.x - c.x, p.y - c.y), alpha);
    return point (t.x + c.x, t.y + c.y);
}
// ���������� �������� ����� ������� � �����
point add_vector (point p, point p1, point p2, double k)
{
    return point (p.x + (p2.x - p1.x) * k, p.y + (p2.y - p1.y) * k);
}
//-----------------------------------------------------------------------------
//*********************** ������� ��� ������ � ������� ************************
//-----------------------------------------------------------------------------
// ��������� ������, ���������� ����� ��� �����
line toline (point p1, point p2)
{
    double a = p2.y - p1.y;
    double b = p1.x - p2.x;

    return line(a, b, - a * p1.x - b * p1.y);
}
// ���� ����� ��� ������������ � ��������� ������
int point_in_line (line l, point p)
{
    double s = l.a * p.x + l.b * p.y + l.c;
    return s < - eps ? - 1 : s > eps ? 1 : 0;
}
// ����������� �� ������?
bool is_parallel_line (line l1, line l2)
{
    return abs (l1.a * l2.b - l2.a * l1.b) <= eps;
}
// ��������� �� ������?
bool is_equal_line (line l1, line l2)
{
    return (abs(l1.a * l2.b - l2.a * l1.b) <= eps && 
            abs(l1.a * l2.c - l2.a * l1.c) <= eps && 
            abs(l1.b * l2.c - l2.b * l1.c) <= eps);
}
// ����������� ���� ������
int cross_line (line l1, line l2, point &p)
{
    if (is_equal_line (l1, l2)) return 2;
    if (is_parallel_line (l1, l2)) return 0;

    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
    p.y = (l1.b != 0 ? (- l1.c - l1.a * p.x) / l1.b : (- l2.c - l2.a * p.x) / l2.b);
    return 1;
}
// ������������� � ������, ���������� ����� �������� �����
line perp_line (line l, point p)
{
    return line (l.b, - l.a, - l.b * p.x + l.a * p.y);
}
// �������� ����� �� ������
point closest_point (line l, point p)
{
    double k = (l.a * p.x + l.b * p.y + l.c) / (l.a * l.a + l.b * l.b);
    return point (p.x - l.a * k, p.y - l.b * k);
}
// ���������� �� ����� �� ������
double dist_point_to_line (point p, line l)
{
    return abs((l.a * p.x + l.b * p.y + l.c) / sqrt(l.a * l.a + l.b * l.b));
}
// ������ ������������ ������ � ������� �� ���������� d �� ��
line parallel_line_of_dist (line l, double d)
{
    return line (l.a, l.b, l.c - d * sqrt (l.a * l.a + l.b * l.b));
}
// ���������� ����� ������������� �������
double dist_between_line (line l1, line l2)
{
    return abs (l1.c - l2.c) / sqrt (l1.a * l1.a + l2.b * l2.b);
}
//-----------------------------------------------------------------------------
//*********************** ������� ��� ������ � ��������� **********************
//-----------------------------------------------------------------------------
// ����������� �� ����� �� �������?
bool point_in_segment (point t, point p1, point p2)
{
    double a = p2.y - p1.y;
    double b = p1.x - p2.x;
    double c = - a * p1.x - b * p1.y;
    if (abs(a * t.x + b * t.y + c) > eps) return false;

    return point_in_box (t, p1, p2);
}

// ������������ �� �������?
bool is_cross_segment (point p1, point p2, point p3, point p4)
{
    line l1 = toline(p1, p2);
    line l2 = toline(p3, p4);
    int sign1 = point_in_line(l1, p3) * point_in_line(l1, p4);
    int sign2 = point_in_line(l2, p1) * point_in_line(l2, p2);

    if (abs(sign1) <= eps && abs(sign2) <= eps)
        return point_in_box(p1, p3, p4) || point_in_box(p2, p3, p4) ||
               point_in_box(p3, p1, p2) || point_in_box(p4, p1, p2);
    return sign1 <= eps && sign2 <= eps;
}
// ����������� ��������
bool cross_segment (point p1, point p2, point p3, point p4, point &t)
{
    // ������ ������ ���������� ����� ��� ������� � ���������� ��
    line l1 = toline(p1, p2);
    line l2 = toline(p3, p4);

    int flag = cross_line(l1, l2, t);
    if (flag == 0) return false;
    
    // ���� ������ ���������, ��������� ������ ����� ������� �� �������������� ������� �������
    if (flag == 2)
    {
        if (point_in_box (p1, p3, p4)) { t = p1; return true; }
        if (point_in_box (p2, p3, p4)) { t = p2; return true; }
        if (point_in_box (p3, p1, p2)) { t = p3; return true; }
        if (point_in_box (p4, p1, p2)) { t = p4; return true; }
        return false;
    }
    // ���� ������ ������������, ��������� ����������� �� ����� ����������� ����� ��������
    return point_in_box (t, p1, p2) && point_in_box (t, p3, p4);
}
// ���������� �� ����� �� �������
double dist_point_to_segment (point p, point p1, point p2)
{
    point t = closest_point (toline (p1, p2), p);

    if (point_in_box (t, p1, p2))
        return dist (p, t);
    else
        return min (dist (p, p1), dist (p, p2));
}

// ����������� ������� � ������
int cross_segment_line (point p1, point p2, line l, point &p)
{
    line t = toline (p1, p2);
    int flag = cross_line (l, t, p);
    if (flag == 0) return 0;
    if (flag == 2) return 2;

    if (point_in_box (p, p1, p2)) return 1;
    return 0;
}
//-----------------------------------------------------------------------------
//*********************** ������� ��� ������ � �������������� *****************
//-----------------------------------------------------------------------------
// ��������������� ������� ������������
double area_triangle (point a, point b, point c)
{
    return 0.5 * (a.x * b.y + b.x * c.y + c.x * a.y - a.y * b.x - b.y * c.x - c.y * a.x); 
}
// ���� ����� ����� ������� - ����� ������������ ��������
double angle_point (point a, point b, point c)
{
    double x1 = a.x - b.x, x2 = c.x - b.x;
    double y1 = a.y - b.y, y2 = c.y - b.y;
    double d1 = sqrt (x1 * x1 + y1 * y1);
    double d2 = sqrt (x2 * x2 + y2 * y2);
    return acos ((x1 * x2 + y1 * y2) / (d1 * d2));
}
//����� �� ����� ������ �� ������� � ������ ������ ������� �������?
bool ccw (point a, point b, point c)
{
        return area_triangle (a, b, c) > eps;
}
// ������ ����
line height_line (point a, point b, point c)
{
    return perp_line (toline (a, c), b);
}
// ������� ����
line median_line (point a, point b, point c)
{
    return toline (b, point ((a.x + c.x) / 2, (a.y + c.y) / 2));
}
// ����������� ����
line bisector_line (point a, point b, point c)
{
    double ab = dist (a, b);
    double bc = dist (b, c);
    point tab = part_segment (b, a, bc, ab);
    point tbc = part_segment (b, c, ab, bc);
    point p = part_segment (tab, tbc, 1, 1);
    return toline (b, p);
}
// ��������� � ����������� ����������
circle entered_circle (point a, point b, point c)
{
    line ba = bisector_line (b, a, c);
    line bb = bisector_line (a, b, c);

    circle res;
    int flag = cross_line (ba, bb, res.c);
    res.r = dist_point_to_line (res.c, toline (a, b));
    return res;
}
// ��������� ����� ������������ ����������
circle described_circle (point a, point b, point c)
{
    point tab = part_segment (a, b, 1, 1);
    point tbc = part_segment (b, c, 1, 1);
    line pab = perp_line (toline (a, b), tab);
    line pbc = perp_line (toline (b, c), tbc);

    circle res;
    int flag = cross_line (pab, pbc, res.c);
    res.r = dist (res.c, a);
    return res;
}
//-----------------------------------------------------------------------------
//*********************** ������� ��� ������ � ������������ *******************
//-----------------------------------------------------------------------------
// ��������� ����� ������������ ����������
int point_in_circle (point p, circle c)
{
    double d = dist (p, c.c);
    if (abs (c.r - d) <= eps) return 1;
    if (c.r > d) return 0;
    return 2;
}
// ����������� ���������� ����������� ��� ����� �����
circle min_circle_for_three_point (point a, point b, point c)
{
    // ���� ��� �����������, �� ��������� ���
    if (abs (area_triangle (a, b, c)) > eps)
        return described_circle (a, b, c);
    // ����� ��� ������� � ����� � �� - �� �������� �������� ���������� ��������� � �������
    point maxP = max_px (max_px (a, b), c);
    point minP = min_px (max_px (a, b), c);
    return circle (part_segment (maxP, minP, 1, 1), 0.5 * dist (minP, maxP));
}
// ����� ����������� ����������� � �����������, ������� ���������� �� �������� �����
int tangent_points (point p, circle c, point &p1, point &p2)
{
    // ������, ����� ������� ������ ����
    int flag = point_in_circle (p, c);
    if (flag == 0) return 0;
    if (flag == 1)
    {
        p1 = p;
        return 1;
    }
    // ���� ����� ������� ���������� � ������ �������
    double d = dist (p, c.c);
    double alpha = asin (c.r / d);
    // ������� ������ ���������� ������ �������� ����� � ��� ������� �� �������� ����
    point _p1 = turn_of (c.c, alpha, p);
    point _p2 = turn_of (c.c, - alpha, p);
    // ���������� �� ����� �� ����� ������� � ��������� ����� �������
    double k = sqrt (d * d - c.r * c.r);
    d = dist (p, _p1);
    p1 = part_segment (p, _p1, k, d - k);
    p2 = part_segment (p, _p2, k, d - k);

    return 2;
}

// ����������� ������ � �����������
int cross_line_circle (line l, circle c, point &p1, point &p2)
{
    // �������� ������ ���������� �� ������
    point p = closest_point (l, c.c);
    // ������� ����� �������?
    int flag = 0;
    double d = dist (c.c, p);
    if (abs (d - c.r) <= eps) flag = 1;
    else
        if (c.r > d) flag = 2;
        else return 0;

    // ������� ���������� �� �������� �� ����� �����������
    double k = sqrt (c.r * c.r - d * d);
    double t = dist (point (0, 0), point (l.b, - l.a));
    // ��������� � �������� ������� ������������ � ������ �����������
    p1 = add_vector (p, point (0, 0), point (- l.b, l.a), k / t);
    p2 = add_vector (p, point (0, 0), point (l.b, - l.a), k / t);

    return flag;
}
// ����������� �����������
int cross_circle (double x1, double y1, double r1, 
                  double x2, double y2, double r2, point &p1, point &p2)
{
    if (abs (x1 - x2) <= eps && abs (y1 - y2) <= eps && abs (r1 - r2) <= eps)
        return 3;
    double a = 2 * (x2 - x1);
    double b = 2 * (y2 - y1);
    double c = x1 * x1 + y1 * y1 - r1 * r1 - (x2 * x2 + y2 * y2 - r2 * r2);
    return cross_line_circle (line (a, b, c), circle (x1, y1, r1), p1, p2);
}
// ����� ������� ����������� � �����������
int contact_points (point p, circle c, point &p1, point &p2)
{
    int flag = point_in_circle (p, c);
    if (flag == 0) return 0;
    if (flag == 1)
    {
        p1 = p;
        return 1;
    }  
    // ������� ���������� �� ����� �������
    double d = dist (p, c.c);
    double k = sqrt (d * d - c.r * c.r);
    return cross_circle (p.x, p.y, k, c.c.x, c.c.y, c.r, p1, p2);
}
//-----------------------------------------------------------------------------
//*********************** ������� ��� ������ � ������ *************************
//-----------------------------------------------------------------------------
// ����������� �� ����� ����?
bool point_in_ray (point p, point p1, point p2)
{
    // ����������� �� ����� ������ ����
    line l = toline (p1, p2);
    if (point_in_line (l, p) != 0) return false;

    // ���� ������ ������������, �� ��������� �� y
    if (abs (l.b) <= eps)
        if (p2.y >= p1.y) 
            return p.y >= p1.y;
        else
            return p.y <= p1.y;

    // ����� ��������� �� x 
    if (p2.x >= p1.x) 
        return p.x >= p1.x;
    else
        return p.x <= p1.x;
}
// ���������� �� ����� �� ����
double dist_point_to_ray (point p, point p1, point p2)
{
    // ����������� ����� �� ������, ���������� �� ����
    line l = toline (p1, p2);
    point t = closest_point (l, p);

    // ���� ���������� ����� ����������� ����, �� ���������� ���������� �� ������
    if (point_in_ray (t, p1, p2))
        return dist (p, t);

    // ����� ���������� ���������� �� ������ ����
    return dist (p, p1);
}
// ��������� ���� � �����������
int cross_ray_circle (point p, point t, circle c, point &p1, point &p2)
{
    // ���������� ������ ���� � �����������
    line l = toline (p, t);
    int flag = cross_line_circle (l, c, p1, p2);
    if (flag == 0) return 0;

    // ���� ����� ����������� ����, �� ��������� �� �� �������������� ����
    // ���� ����� ����
    if (flag == 1)
        if (point_in_ray (p1, p, t))
            return 1;
        else
            return 0;

    // ���� ����� ���
    bool b1 = point_in_ray (p1, p, t);
    bool b2 = point_in_ray (p2, p, t);

    if (b1)
        if (b2)
            return 2;
        else
            return 1;
    else
        if (b2)
        {
            p1 = p2;
            return 1;
        }
        else
            return 0;
}
// ����� ���� � ��������� �������, ������� �� ���������� �� ���� �� �������� �����������
class less_of_polar_angle
{
public :
    bool operator () (circle c1, circle c2)
    {
        return c1.alpha < c2.alpha;
    }
};
bool ray_nocross_for_circset (point p, vector < circle > v, point &t)
{
    int n = v.size();
    int i, j, k;

    // ��� ������ ���������� ������� � �������� ����
    for (i = 0; i < n; ++ i)
        v[i].alpha = polar_angle (point (v[i].c.x - p.x, v[i].c.y - p.y));

    // ��������� ��� ���������� �� ��������� ���� ����� �� �����
    sort (v.begin (), v.end (), less_of_polar_angle ());

    // ������� ���������� � ������������ ��������
    k = 0;
    for (i = 1; i < n; ++ i)
        if (v[i].r > v[k].r)
            k = i;

    // ������������� ��� ���������� �� �������, ������� � k
    i = k; // ������� ����������
    do
    {
        point p1, p2;
        int flag = contact_points (p, v[i], p1, p2);
        double alpha = polar_angle (point (p1.x - p.x, p1.y - p.y));
        double betta = polar_angle (point (p2.x - p.x, p2.y - p.y));

        // ������� ����� ����� ������� - t
        if (abs (alpha - betta) >= pi) 
            if (alpha < betta)
                t = p1;
            else 
                t = p2;
        else
            if (alpha < betta)
                t = p2;
            else
                t = p1;
        
        // ���������� � �� 0.001 �� �������������� �����
        double d = 0.001 / dist (v[i].c, t);
        t = add_vector (t, v[i].c, t, d);

        // ���� ������ ����������, ������� ���������� ��� (p, t)
        bool flag_cross = false;
        j = (i + 1) % n;
        do
        {
            if (cross_ray_circle (p, t, v[j], p1, p2) != 0)
            {
                flag_cross = true;
                i = j;
                break;
            }
            j = (j + 1) % n;
        }
        while (j != k);

        // ���� ��� ���������� �� ���������� ���� ���
        if (flag_cross == false)    return true;
    }
    while (i != k);

    return false;
}
//-----------------------------------------------------------------------------
//*********************** ������� ��� ������ � ���������������� ***************
//-----------------------------------------------------------------------------
// ��������������� ������� ��������������
double area_polygon (vector < point > p)
{
    int i, j;
    double s = 0;
    for (i = 0; i < p.size(); ++ i)
    {
        j = (i + 1) % p.size();
        s += p[i].x * p[j].y - p[j].x * p[i].y;
    }
    return 0.5 * s;
}

// �������� ��������������
double perimeter_polygon (vector < point > p)
{
    int i, j;
    double perimeter = 0;
    for (i = 0; i < p.size(); ++ i)
    {
        j = (i + 1) % p.size();
        perimeter += dist (p[i], p[j]);
    }
    return perimeter;
}
// ����������� �� ����� � ��������������?
bool point_in_polygon (point t, vector < point > p)
{
        int i, j;
        int count = 0;
        for (i = 0; i < p.size(); ++ i)
        {
                j = (i + 1) % p.size();
                if (min (p[i].y, p[j].y) < t.y && t.y <= max (p[i].y, p[j].y) &&
                    ccw (min_py (p[i], p[j]), max_py (p[i], p[j]), t))
                {
                    // ���� �������� ����� ����� �� ������� � ����� ��������� ������ �� �������
                    // �� ����������� ���������� "���������" ����� � �������������
                    ++ count; 
                }
        }
        return count % 2;
}
// ���������� ����� �� ������� ��������������
long long count_B (vector < point > p)
{
    int i, j;
    long long count = 0;
    for (i = 0; i < p.size(); ++ i)
    {
        j = (i + 1) % p.size();
        count += gcd (p[j].x - p[i].x, p[j].y - p[i].y);
    }
    return count;
}
// ���������� ����� ������ ��������������
long long count_I (vector < point > p)
{
    return abs (area_polygon (p)) - count_B (p) / 2 + 1;
}
// �������� �� �������������?
bool is_convex (vector < point > p)
{
    int l, i, r;
    int n = p.size();
    bool isccw = ccw (p[n - 1], p[0], p[1]);
    for (i = 1; i < n; ++ i)
    {
        l = (i - 1 + n) % n;
        r = (i + 1) % n;
        if (ccw (p[l], p[i], p[r]) != isccw)
            return false;
    }
    return true;
}
// �������� �������� - �������� ��������
void hull_jarvis (vector < point > p, vector < int > &ip)
{
    int n = p.size();
    int first, q, next, i;
    double sign;
    // ������� ����� ������ �� ����� ����� �����
    first = 0;
    for (i = 1; i < n; ++ i)
        if (p[i].x < p[first].x || (p[i].x == p[first].x && p[i].y < p[first].y))
            first = i;
  
    q = first; // ������� �����
    // ��������� ����� � ��������
    do
    {
        ip.push_back(q);
        next = q;
        // ���� ��������� �����
        for (i = n - 1; i >= 0; -- i)
            if (p[i].x != p[q].x || p[i].y != p[q].y)
            {
                sign = area_triangle (p[q], p[i], p[next]);

                if (next == q || sign > 0 || (sign == 0 && point_in_box (p[next], p[q], p[i])))
                    next = i;
            }
        q = next;
    }
    while (q != first);
}
// �������� �������� - �������� �������
point first;
class less_of_ccw
{
public :
    bool operator () (point a, point b)
    {
        if (a.i == first.i) return true;
        if (b.i == first.i) return false;
        if (ccw (first, a, b)) return true;
        if (ccw (first, b, a)) return false;
        return dist (first, a) > dist (first, b);
    }
};
void hull_graham (vector < point > p, vector < int > &ip)
{
    int n = p.size();
    int i;
    for (i = 0; i < n; ++ i)
        p[i].i = i;
    // ���� ����� ������ �� ����� ����� ����� - ������ �����
    first = p[0];
    for (i = 1; i < n; ++ i)
        if (first.x > p[i].x || (first.x == p[i].x && first.y > p[i].y))
            first = p[i];
    
    // ��������� ����� �� �� ���� ������������ ������ �����
    sort (p.begin (), p.end (), less_of_ccw ());
    // ������ ����� ��������
    ip.push_back (0);
    // ���� ������ ����� ��������
    for (i = 1; i < n && abs (area_triangle (p[0], p[1], p[i])) <= eps; ++ i);
    ip.push_back (1);

    // ��������������� ��������� ����� � ��������
    int top = 1; // ������ ��������� ����� � ��������
    while (i < n)
    {
        // ���� ���� ������ pi �� ��������� ��������� ����� �� ��������
        if (! ccw (p[ip[top - 1]], p[ip[top]], p[i]))
        {
            -- top;
            ip.pop_back ();
        }
        // ����� ��������� ����� � ��������
        else
        {
            ++ top;
            ip.push_back (i);
            ++ i;
        }
    }
    for (i = 0; i < ip.size(); ++ i)
        ip[i] = p[ip[i]].i;
}
// ����������� ����������, ����������� ��������� �����
circle min_described_circle (vector < point > p)
{
    int n = p.size ();
    int i, j, k;
    circle c = circle (0, 0, 1e9);
    for (i = 0; i < n; ++ i)
        for (j = i + 1; j < n; ++ j)
            for (k = j + 1; k < n; ++ k)
            {
                circle t = min_circle_for_three_point (p[i], p[j], p[k]);
                int u;
                for (u = 0; u < n; ++ u)
                    if (point_in_circle (p[u], t) == 2) break;
                if (u >= n && t.r < c.r)
                    c = t;
            }
    return c;
}
// ������������ �������������� ����������� ������
//        1 - ��������� � ������������� �������
//        - 1 - ��������� � ������������� �������
//        0 - ������ ���������� ���� �� ������ �������������� (������� � �� �������)
int polygon_for_line (vector < point > p, line l)
{
    int i, j;
    int s = - 2; // ����
    for (i = 0; i < p.size(); ++ i)
    {
        int t = point_in_line (l, p[i]); // ��������� ������� ������������ ������
        if (t != 0)        // ���� ����� �� ������������ ������
            if (s != - 2)     // ���� s �� ���������
                if (t != s)        // ���� ����� ��������, �� ������ ���������� ������� ��������������
                    return 0;
                else
                {}
            else
                s = t; // ���� s �� ��� �� ���������, ����������� ��� ����������� ��������
    }
    if (s == - 2) return 0;
    return s;
}

// ���������� �������������� �� ���������
void cut_polygon_for_edge (vector < point > p, int i1, int i2, vector < point > &p1, vector < point > &p2)
{
    int i;    
    int n = p.size();

    for (i = i1; i != (i2 + 1) % n; i = (i + 1) % n)
        p1.push_back (p[i]);

    for (i = i2; i != (i1 + 1) % n; i = (i + 1) % n)
        p2.push_back (p[i]);
}
// ���������� ��������� �������������� �� ������
//        ������� ���������� ��� ��������������
//        ������ ������������� ����� � ������������� ������� �� ������
//        ������ - � �������������
void cut_convex_for_line (vector < point > p, line l, vector < point > &v1, vector < point > &v2, point &p1, point &p2)
{
    int n = p.size();
    int i, j;

    // ������� ����� ����������� ������ � ��������������� � ��������� �� � �������������
    int c = 0; // ������� ����������� �������������� � ������
    list < point > s (p.begin(), p.end()); // ������������ ������������� ��� ������ ������
    list < point > :: iterator it, jt; // ��������� ������
    list < point > :: iterator i1, i2; // ��������� ����������� �����

    for (it = s.begin(); it != s.end(); ++ it)
    {
        jt = it;
        ++ jt;
        if (jt == s.end()) jt = s.begin();

        // ���������� ������ �� ��������
        point t;
        int flag = cross_segment_line (*it, *jt, l, t);
        // ���� ������ �������� �� �������
        if (flag == 2)
        {
            if (polygon_for_line (p, l) > 0)    v1 = p;
            else    v2 = p;
            return;
        }
        // ���� ������ � ������� �� ������������
        if (flag == 0) continue;

        // ���� ������ �������� ����� ������� ��������������
        if (abs (t.x - (*it).x) <= eps && abs (t.y - (*it).y) <= eps)
        {
            if (c == 0) i1 = it;
            else i2 = it;
            ++ c;
            continue;
        }
        if (abs (t.x - (*jt).x) <= eps && abs (t.y - (*jt).y) <= eps) continue;

        // ����� ������ ���������� �������, ��������� ����� ����������� � �������������
        ++ it;
        it = s.insert (it, t);

        // ����������� ������� ����������� �������������� � ������
        if (c == 0) i1 = it;
        else i2 = it;
        ++ c;
    }

    // ���� ������ �� ���������� �������������
    if (c != 2)
    {
        if (polygon_for_line (p, l) > 0)    v1 = p;
        else    v2 = p;
        return;
    }

    // ������������ ������������� �������� �����
    n = s.size ();
    vector < point > all (s.begin(), s.end());
    int j1, j2;
    for (it = s.begin(), i = 0; it != s.end(); ++ i, ++ it)
    {
        if (it == i1) j1 = i;
        if (it == i2) j2 = i;
    }

    // ����� �������������
    p1 = all[j1];
    p2 = all[j2];
    cut_polygon_for_edge (all, j1, j2, v1, v2);

    // ���� �������������� ����� �� �� ������������ ������� ��� ��������� - ������ �� �������
    if (polygon_for_line (v1, l) < 0)
        swap (v1, v2);
}

// ���������� ��������� �������������� � ��������� �������� m:n
point part_convex (vector < point > v, double m, double n)
{
    double area = abs (area_polygon (v)) / (m + n) * m;
    double a = 0;
    int i;
    for (i = 1; i < v.size () - 1; ++ i)
    {
        double s = abs (area_triangle (v[0], v[i], v[i + 1]));
        if (a + s <= area)
            a += s;
        else break;
    }
    if (abs (a - area) <= eps) return v[i];
    return part_segment (v[i], v[i + 1], area - a,
                        abs (area_triangle (v[0], v[i], v[i + 1]) - area + a));
}
// ���������� ��������� �������������� �� k ������ ������
void npart_convex (vector < point > v, int k, vector < point > &s)
{
    double area = abs (area_polygon (v));
    double a = area / (double) k;
    int i;
    for (i = 1; i < k; ++ i)
        s.push_back (part_convex (v, a * i, area - a * i));
}
