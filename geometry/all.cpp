#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

//#define double long double

using std::abs;
using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::min;

const double eps = 1e-8;
const int maxn = 1e5 + 10;

struct V
{
    double x, y;
    V() {}
    V(const double x_, const double y_) : x(x_), y(y_) {}
    inline V operator+(const V &b) const { return V(x + b.x, y + b.y); }
    inline V operator-(const V &b) const { return V(x - b.x, y - b.y); }
    inline double dis() const { return sqrt(x * x + y * y); }
    inline V operator*(const double &b) const { return V(x * b, y * b); }
    friend inline V operator*(const double &a, V &b) { return V(b.x * a, b.y * a); }
    inline V operator/(const double &b) const { return V(x / b, y / b); }
    inline double operator*(const V &b) const { return x * b.x + y * b.y; }
    inline double operator&(const V &b) const { return x * b.y - y * b.x; } // 叉积
    inline V operator+=(const V &b) { return *this = *this + b; }
    inline V operator-=(const V &b) { return *this = *this - b; }
    inline V operator*=(const double &b) { return *this = *this * b; }
    inline V operator/=(const double &b) { return *this = *this / b; }
    inline bool operator==(const V &b) const { return abs(x - b.x) < eps && abs(y - b.y) < eps; }
    inline bool operator!=(const V &b) const { return !(*this == b); }
    inline void print() { printf("%.10lf %.10lf\n", x, y); }
    inline void in() { scanf("%lf%lf", &x, &y); }
    inline bool zero() { return dis() < eps; }
};
bool cmp_xy(const V &a, const V &b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
inline double dis(const V &a, const V &b) { return (b - a).dis(); }
inline V rotate(const V &a, const double deg) // 向量逆时针旋转
{
    double s = sin(deg), c = cos(deg);
    return V(a.x * c - a.y * s, a.y * c + a.x * s);
}
inline V rotate_90(const V &a) { return V(-a.y, a.x); } // 向量逆时针旋转 90 度

struct line // 直线或线段
{
    V x, d; // 起始点和方向向量
    V a, b; // 两个点
    V d2;
    line() {}
    inline line(const V &a_, const V &b_) : x(a_), d((b_ - a_) / (b_ - a_).dis()), a(a_), b(b_), d2(b_ - a_) {}
    inline void init(const V &a_, const V &b_) { x = a_, d = ((b_ - a_) / (b_ - a_).dis()), d2 = b_ - a_; }
    inline void init(const V &a_) { init(V(0, 0), a_); }
    inline void in() { a.in(), b.in(), init(a, b); }
    inline V mid() { return (a + b) / 2; }                              // 中点
    inline line mid_ver() { return line(mid(), mid() + rotate_90(d)); } // 中垂线
};

inline V vertical_foot(const line &l, const V &x) { return l.x + l.d * ((x - l.x) * l.d); }                                                  // 垂足
inline V reflection(const line &l, const V &x) { return vertical_foot(l, x) + (vertical_foot(l, x) - x); }                                   // 对称点
inline bool on_line(const line &l, const V &x) { return abs(l.d & (x - l.x)) < eps; }                                                        // 点在直线上
inline bool on_line(const V &x, const V &y) { return abs(x & y) < eps; }                                                                     // 两个向量共线
inline bool on_segment(const line &a, const V &b) { return on_line(a, b) && (a.a - b) * (a.b - b) < eps; }                                   // 点在线段上
inline bool parallel(const line &a, const line &b) { return on_line(a.d, b.d); }                                                             // 直线/线段 平行
inline line parallel_line(const line &a, const V &b) { return line(b, b + a.d); }                                                            // 过一点求一直线的平行线
inline bool vertical(const V &a, const V &b) { return abs(a * b) < eps; }                                                                    // 向量垂直
inline bool vertical(const line &a, const line &b) { return vertical(a.d, b.d); }                                                            // 直线垂直
inline bool same_line(const line &a, const line &b) { return abs((a.a - b.a) & (a.b - b.a)) < eps && abs((a.a - b.b) & (a.b - b.b)) < eps; } // 两直线重合
inline bool intersect(const line &a, const line &b)                                                                                          // 两线段是否相交
{
    if (min(a.a.x, a.b.x) > max(b.a.x, b.b.x) + eps || max(a.a.x, a.b.x) < min(b.a.x, b.b.x) - eps ||
        min(a.a.y, a.b.y) > max(b.a.y, b.b.y) + eps || max(a.a.y, a.b.y) < min(b.a.y, b.b.y) - eps)
        return false;
    return ((b.a - a.a) & a.d) * ((b.b - a.a) & a.d) < eps && ((a.a - b.a) & b.d) * ((a.b - b.a) & b.d) < eps;
}
inline bool intersect_l_s(const line &a, const line &b) // 直线与线段之间交点
{
    line p(a.x - a.d * 1e9, a.x + a.d * 1e9);
    return intersect(p, b);
}
inline V cross_point(const line &a, const line &b) // 交点
{
    return a.x + a.d * (((b.a - a.a) & b.d) / (a.d & b.d));
}
inline double dis_l(const line &a, const V &b) // 点到直线距离
{
    return (b - vertical_foot(a, b)).dis();
}
inline double dis_s(const line &a, const V &b) // 点到线段距离
{
    V h = vertical_foot(a, b);
    //h.print();
    if (on_segment(a, h))
        return dis_l(a, b);
    else
        return min((a.a - b).dis(), (a.b - b).dis());
}
inline double dis_two_s(const line &a, const line &b) // 两线段之间距离
{
    if (intersect(a, b))
        return 0;
    return min({dis_s(a, b.a), dis_s(a, b.b), dis_s(b, a.a), dis_s(b, a.b)});
}
inline line bisector(const line &a, const line &b) { return line(a.a, a.a + a.d + b.d); }             // 角平分线
inline line bisector(const V &a, const V &b, const V &c) { return bisector(line(a, b), line(a, c)); } // 角平分线

double S(V *a, int n) // 多边形面积
{
    double res = 0;
    for (int i = 1; i <= n; i++)
        res += (a[i] & a[i % n + 1]);
    return res / 2;
}
bool is_convex(V *a, int n) // 是否是凸多边形
{
    a[0] = a[n], a[n + 1] = a[1];
    int flag = -1;
    for (int i = 1; i <= n; i++)
    {
        double res = (a[i] - a[i - 1]) & (a[i + 1] - a[i]);
        if (abs(res) < eps)
            continue;
        if (flag == -1)
            flag = res > 0;
        else if (flag != (res > 0))
            return false;
    }
    return true;
}
int in_polygen(V *a, int n, V x) // 点在多边形内
{
    int res = 0;
    a[n + 1] = a[1];
    for (int i = 1; i <= n; i++)
    {
        if (on_segment(line(a[i], a[i + 1]), x))
            return 1;
        if (abs(a[i].y - a[i + 1].y) < eps)
            continue;
        if (min(a[i].y, a[i + 1].y) > x.y - eps || max(a[i].y, a[i + 1].y) < x.y - eps)
            continue;
        double nx = a[i].x + (x.y - a[i].y) / (a[i + 1].y - a[i].y) * (a[i + 1].x - a[i].x);
        if (nx > x.x)
            res ^= 1;
    }
    return res ? 2 : 0;
}
int used[maxn];
int andrew(V *a, int n, int *ans) // 求凸包
{
    memset(used, 0, sizeof(used));
    std::sort(a + 1, a + 1 + n, cmp_xy);
    int tp = 0;
    ans[++tp] = 1;
    for (int i = 2; i <= n; i++)
    {
        while (tp >= 2 && ((a[ans[tp]] - a[ans[tp - 1]]) & (a[i] - a[ans[tp]])) < 0)
            used[ans[tp--]] = 0;
        used[i] = 1, ans[++tp] = i;
    }
    int t = tp;
    for (int i = n - 1; i >= 1; i--)
    {
        if (!used[i])
        {
            while (tp > t && ((a[ans[tp]] - a[ans[tp - 1]]) & (a[i] - a[ans[tp]])) < 0)
                used[ans[tp--]] = 0;
            used[i] = 1, ans[++tp] = i;
        }
    }
    return tp - 1;
}
inline double S_tri(const V &a, const V &b, const V &c) { return abs((a - b) & (a - c)); } // 三角形面积
double get_farthest(V *a, int n)                                                           // 凸包直径
{
    if (n <= 2)
        return dis(a[1], a[2]);
    int pos = 3;
    a[n + 1] = a[1];
    double mx = 0;
    for (int i = 1; i <= n; i++)
    {
        while (S_tri(a[i], a[i + 1], a[pos]) <= S_tri(a[i], a[i + 1], a[pos % n + 1]))
            pos = pos % n + 1;
        mx = max(mx, max(dis(a[i], a[pos]), dis(a[i + 1], a[pos])));
    }
    return mx;
}
V convex[maxn];
double cut_polygen(V *a, int n, line l) // 直线切凸包，直线左侧的面积
{
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (((l.b - l.a) & (a[i] - l.a)) >= 0)
            convex[++cnt] = a[i];
        line s(a[i], a[i + 1]);
        if (same_line(l, s))
            continue;
        if (intersect_l_s(l, s))
        {
            V o = cross_point(l, line(a[i], a[i + 1]));
            if (o != a[i] && o != a[i + 1])
                convex[++cnt] = o;
        }
    }
    return S(convex, cnt);
}

struct circle
{
    V o;
    double r;
    circle() {}
    circle(const V &O_, double r_) : o(O_), r(r_) {}
    void in() { o.in(), scanf("%lf", &r); }
    void print() { printf("%.10lf %.10lf %.10lf\n", o.x, o.y, r); }
};

inline bool not_cross(const circle &a, const circle &b) { return a.r + b.r < (a.o - b.o).dis(); }                                       // 相离
inline bool tangency(const circle &a, const circle &b) { return abs((b.o - a.o).dis() - a.r - b.r) < eps; }                             // 外切
inline bool intersect(const circle &a, const circle &b) { return abs(a.r - b.r) < (b.o - a.o).dis() && (b.o - a.o).dis() < a.r + b.r; } // 相交
inline bool in_tangency(const circle &a, const circle &b) { return abs(abs(a.r - b.r) - (b.o - a.o).dis()) < eps; }                     // 内切
inline bool include(const circle &a, const circle &b) { return abs(a.r - b.r) > (b.o - a.o).dis() + eps; }                              // 内含

inline circle out_circle(V &a, V &b, V &c) // 外接圆
{
    line x = line(a, b).mid_ver(), y = line(b, c).mid_ver();
    //x.a.print(), x.b.print(), y.a.print(), y.b.print();
    V O = cross_point(x, y);
    return circle(O, (a - O).dis());
}

inline circle in_circle(V &a, V &b, V &c) // 内切圆
{
    V O = cross_point(bisector(a, b, c), bisector(b, a, c));
    return circle(O, dis_l(line(b, a), O));
}
