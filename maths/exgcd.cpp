#include <algorithm>
#include <cmath>
#include <cstdio>

typedef long long ll;

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y);
    ll t = x;
    x = y;
    y = t - a / b * y;
    return d;
}
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

// ax=c (mod b)
void solve(ll a, ll c, ll b)
{
    ll d = gcd(a, b);
    if (c % d != 0)
    {
        puts("Orz, I cannot find x!");
        return;
    }
    ll x, y;
    exgcd(a, b, x, y);
    ll t = c / d;
    x *= t, y *= t, x %= b, y %= b;
    x += b / d, x += b, x %= b;
    printf("%lld\n", x);
}
