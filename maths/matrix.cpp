#include <cstdio>
#include <cstring>
#include <iostream>

const int mod = 1e9 + 7, maxn = 110;

class matrix
{
public:
    long long a[maxn][maxn], n, m;
    matrix() : n(0), m(0) { memset(a, 0, sizeof(a)); }
    matrix(int _n, int _m, long long _a[maxn][maxn])
    {
        n = _n, m = _m;
        for (int i = 1; i <= _n; i++)
            for (int j = 1; j <= _m; j++)
                a[i][j] = _a[i][j];
    }
    void init(int _n)
    {
        n = m = _n;
        for (int i = 1; i <= n; i++)
            a[i][i] = 1;
    }
    matrix operator*(const matrix &b)
    {
        matrix c;
        c.n = n, c.m = b.m;
        for (int i = 1; i <= n; i++)
            for (int k = 1; k <= b.n; k++)
                for (int j = 1; j <= b.m; j++)
                    c.a[i][j] += a[i][k] * b.a[k][j], c.a[i][j] %= mod;
        return c;
    }
    void print()
    {
        for (int i = 1; i <= n; i++, puts(""))
            for (int j = 1; j <= m; j++)
                printf("%lld ", a[i][j]);
    }
    void operator=(const matrix &b)
    {
        n = b.n, m = b.m;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                a[i][j] = b.a[i][j];
    }
    inline matrix qpow(long long x)
    {
        matrix p = *this;
        return qpow(p, x);
    }
    matrix qpow(matrix a, long long x)
    {
        if (x == 1)
            return a;
        x--;
        matrix res = a;
        for (; x; x >>= 1)
        {
            if (x & 1)
                res = res * a;
            a = a * a;
        }
        return res;
    }
};
