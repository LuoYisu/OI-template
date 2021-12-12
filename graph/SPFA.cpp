// 负环
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

const int maxn = 2e3 + 10;

struct edge
{
    int y, w;
};

std::vector<edge> e[maxn];
inline void add(int x, int y, int w) { e[x].push_back({y, w}); }

int dis[maxn], inq[maxn], cnt[maxn], n, m;

bool spfa(int s)
{
    memset(dis, 1, sizeof(dis));
    std::queue<int> q;
    q.push(s), inq[s] = 1, dis[s] = 0;
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        inq[now] = 0;
        for (auto k : e[now])
        {
            int w = k.w, v = k.y;
            if (dis[now] + w < dis[v])
            {
                dis[v] = dis[now] + w;
                cnt[v] = cnt[now] + 1;
                if (cnt[v] >= n)
                    return true;
                if (!inq[v])
                    inq[v] = 1, q.push(v);
            }
        }
    }
    return false;
}

void clear()
{
    memset(inq, 0, sizeof(inq)), memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++)
        e[i].clear();
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 0, x, y, w; i < m; i++)
        {
            scanf("%d%d%d", &x, &y, &w);
            if (w >= 0)
                add(x, y, w), add(y, x, w);
            else
                add(x, y, w);
        }
        puts(spfa(1) ? "YES" : "NO");
        clear();
    }
}