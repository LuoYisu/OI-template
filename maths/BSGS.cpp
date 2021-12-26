#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
using std::cin;
using std::cout;
using std::endl;

typedef long long ll;

ll qpow(ll a, ll x, ll p)
{
    ll res = 1;
    for (; x; x >>= 1, a = a * a % p)
        if (x & 1)
            res = res * a % p;
    return res;
}

std::map<ll, int> mp;

ll p, b, n;

void solve()
{
    b %= p;
    ll t = ceil(sqrt(p));
    for (int i = 0; i <= t; i++)
        mp[n * qpow(b, i, p) % p] = i;
    for (int i = 0; i <= t; i++)
    {
        ll q = qpow(b, t * i, p);
        if (mp.count(q))
        {
            if (1)
            {
                cout << t * i - mp[q] << endl;
                return;
            }
        }
    }
    puts("no solution");
}

int main()
{

    cin >> p >> b >> n;
    solve();
}