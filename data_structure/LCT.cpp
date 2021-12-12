#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#define mem(x) memset(x, 0, sizeof(x))
using std::cin;
using std::cout;
using std::endl;

const int maxn = 1e5 + 10;

inline int read()
{
    char ch = getchar();
    int x = 0;
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        x = x * 10 + ch - '0', ch = getchar();
    return x;
}

struct LCT
{
    int ch[maxn][2], rev[maxn], father[maxn], ans[maxn], val[maxn];
    inline int &ls(int x) { return ch[x][0]; }
    inline int &rs(int x) { return ch[x][1]; }
    inline bool get(int x) { return x == rs(father[x]); }
    inline bool isroot(int x) { return x != ch[father[x]][0] && x != ch[father[x]][1]; }
    inline void push_up(int x) { ans[x] = ans[ls(x)] ^ ans[rs(x)] ^ val[x]; }
    inline void push_down(int x)
    {
        if (!rev[x])
            return;
        if (ls(x))
            std::swap(ls(ls(x)), rs(ls(x))), rev[ls(x)] ^= 1;
        if (rs(x))
            std::swap(ls(rs(x)), rs(rs(x))), rev[rs(x)] ^= 1;
        rev[x] = 0;
    }
    inline void update(int x)
    {
        if (!isroot(x))
            update(father[x]);
        push_down(x);
    }
    inline void rotate(int x)
    {
        int y = father[x], z = father[y], d = get(x);
        if (!isroot(y))
            ch[z][y == ch[z][1]] = x;
        ch[y][d] = ch[x][d ^ 1];
        if (ch[x][d ^ 1])
            father[ch[x][d ^ 1]] = y;
        ch[x][d ^ 1] = y, father[y] = x, father[x] = z;
        push_up(y), push_up(x);
    }
    inline void splay(int x)
    {
        update(x);
        for (int f; f = father[x], !isroot(x); rotate(x))
            if (!isroot(f))
                rotate(get(x) == get(f) ? f : x);
    }
    int access(int x)
    {
        int p = 0;
        for (; x; p = x, x = father[x])
            splay(x), rs(x) = p, push_up(x);
        return p;
    }
    void makeroot(int x) { x = access(x), std::swap(ls(x), rs(x)), rev[x] ^= 1; }
    int find(int x)
    {
        access(x), splay(x), push_down(x);
        while (ls(x))
            x = ls(x), push_down(x);
        splay(x);
        return x;
    }
    void split(int x, int y) { makeroot(x), access(y), splay(y); }
    void link(int x, int y)
    {
        makeroot(x), splay(x);
        if (find(y) == x)
            return;
        father[x] = y;
    }
    void cut(int x, int y)
    {
        makeroot(x);
        if (find(y) == x && father[y] == x && !ls(y))
            ls(x) = father[y] = 0, push_up(x);
    }

    void modify(int x, int y) { splay(x), val[x] = y, push_up(x); }
} lct;

int main()
{
    //std::ios::sync_with_stdio(false);
    int n, m;
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
        lct.val[i] = read();
    while (m--)
    {
        int pos, x, y;
        pos = read(), x = read(), y = read();
        if (pos == 0)
            lct.split(x, y), printf("%d\n", lct.ans[y]);
        else if (pos == 1)
            lct.link(x, y);
        else if (pos == 2)
            lct.cut(x, y);
        else
            lct.modify(x, y);
    }
}
