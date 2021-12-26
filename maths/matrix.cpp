#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

const int mod = 1e9 + 7, maxn = 110;
const double eps = 1e-8;
typedef long long ll;

ll qpow(ll a, ll x, ll p)
{
    ll res = 1;
    for (; x; a = a * a % p, x >>= 1)
        if (x & 1)
            res = res * a % p;
    return res;
}

ll inv(ll x) { return qpow(x, mod - 2, mod); }

struct Matrix
{
    ll a[maxn][maxn], n, m;
    Matrix() : n(0), m(0) { memset(a, 0, sizeof(a)); }
    Matrix(int n_, int m_) : n(n_), m(m_) {}
    Matrix(int n_) : n(n_) {}
    Matrix(int _n, int _m, ll _a[maxn][maxn])
    {
        n = _n, m = _m;
        for (int i = 1; i <= _n; i++)
            for (int j = 1; j <= _m; j++)
                a[i][j] = _a[i][j];
    }
    inline void upd(ll &x, ll y) { x += y + mod, x %= mod; }
    void init(int _n)
    {
        n = m = _n;
        for (int i = 1; i <= n; i++)
            a[i][i] = 1;
    }
    Matrix operator*(const Matrix &b)
    {
        Matrix c;
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
    void operator=(const Matrix &b)
    {
        n = b.n, m = b.m;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                a[i][j] = b.a[i][j];
    }
    inline Matrix qpow(ll x)
    {
        Matrix p = *this;
        return qpow(p, x);
    }
    Matrix qpow(Matrix a, ll x)
    {
        if (x == 1)
            return a;
        x--;
        Matrix res = a;
        for (; x; x >>= 1)
        {
            if (x & 1)
                res = res * a;
            a = a * a;
        }
        return res;
    }
    int gauss_det(int p)
    {
        int res = 1, flg = 1;
        for (int i = 1; i <= n; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                while (a[i][i])
                {
                    int t = a[j][i] / a[i][i];
                    for (int k = i; k <= n; k++)
                    {
                        a[j][k] = (a[j][k] - 1ll * t * a[i][k] % p + p) % p;
                    }
                    std::swap(a[i], a[j]), flg *= -1;
                }
                std::swap(a[i], a[j]), flg *= -1;
            }
        }
        for (int i = 1; i <= n; i++)
            res = 1ll * res * a[i][i] % p;
        return (res * flg + p) % p;
    }
    void gauss_equ()
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == j)
                    continue;
                double d = a[j][i] / a[i][i];
                for (int k = i; k <= n + 1; k++)
                {
                    a[j][k] -= d * a[i][k];
                }
            }
        }
        /*
        for (int i = 1; i <= n; i++)
            if (fabs(a[i][i]) <= eps)
            {
                puts("No Solution");
                return;
            }
        */
        for (int i = 1; i <= n; i++)
            a[i][n + 1] /= a[i][i];
    }
    Matrix inv()
    {
        Matrix I(n), now = *this;
        for (int i = 1; i <= n; i++)
            I.a[i][i] = 1;
        for (int i = 1; i <= n; i++)
        {
            ll t = ::inv(now.a[i][i]);
            for (int j = 1; j <= n; j++)
            {
                if (i == j)
                    continue;
                ll d = t * now.a[j][i] % mod;
                for (int k = i; k <= n; k++)
                    upd(now.a[j][k], -d * now.a[i][k]);
                for (int k = 1; k <= n; k++)
                    upd(I.a[j][k], -d * I.a[i][k]);
            }
        }
        for (int i = 1; i <= n; i++)
        {
            ll d = ::inv(now.a[i][i]);
            for (int j = 1; j <= n; j++)
                I.a[i][j] = I.a[i][j] * d % mod;
        }
        for (int i = 1; i <= n; i++)
            if (now.a[i][i] == 0)
            {
                puts("No Solution");
                exit(0);
            }
        return I;
    }
};
