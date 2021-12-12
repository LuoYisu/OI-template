typedef long long ll;

ll qpow(ll a, ll x, ll p)
{
    if (x == 1)
        return a;
    ll res = 1;
    for (; x; x >>= 1)
    {
        if (x & 1)
            res = res * a % p;
        a = a * a % p;
    }
    return res;
}