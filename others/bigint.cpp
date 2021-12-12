// not finished
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;

const int maxn = 82, maxl = 50;

class Bigint
{
    int a[maxl], len;

public:
    Bigint() { len = 1, memset(a, 0, sizeof(a)); }
    void clear() { memset(a, 0, sizeof(a)), len = 1; }
    friend Bigint operator+(const Bigint &a, const Bigint &b)
    {
        Bigint res;
        res.len = std::max(a.len, b.len);
        int x = 0;
        for (int i = 0; i < res.len; i++)
        {
            res.a[i] = a.a[i] + b.a[i] + x;
            x = res.a[i] / 10;
            res.a[i] %= 10;
        }
        if (x > 0)
            res.a[res.len++] = x;
        return res;
    }
    friend Bigint operator+(const Bigint &a, const int &b)
    {
        Bigint res;
        res.len = a.len;
        int x = 0;
        res.a[0] = b;
        for (int i = 0; i < res.len; i++)
        {
            res.a[i] += a.a[i] + x;
            x = res.a[i] / 10;
            res.a[i] %= 10;
        }
        while (x > 0)
            res.a[res.len++] = x % 10, x /= 10;
        return res;
    }
    Bigint operator+=(const Bigint &a)
    {
        return *this = *this + a;
    }
    Bigint operator*(const int &x)
    {
        Bigint res;
        res.len = this->len;
        int p = 0;
        for (int i = 0; i < res.len; i++)
        {
            res.a[i] = this->a[i] * x + p;
            p = res.a[i] / 10;
            res.a[i] %= 10;
        }
        while (p > 0)
            res.a[res.len++] = p % 10, p /= 10;
        return res;
    }
    friend bool operator<(const Bigint &a, const Bigint &b)
    {
        if (a.len != b.len)
            return a.len < b.len;
        for (int i = a.len - 1; i >= 0; i--)
            if (a.a[i] != b.a[i])
                return a.a[i] < b.a[i];
        return 0;
    }
    friend std::ostream &operator<<(std::ostream &os, const Bigint &n)
    {
        for (int i = n.len - 1; i >= 0; i--)
            printf("%d", n.a[i]);
        return os;
    }
};