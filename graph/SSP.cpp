#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;

const int maxn = 5e3 + 10;

struct edge
{
    int x, y, cap, flow, cost;
};

struct Dinic
{
    std::vector<int> e[maxn];
    std::vector<edge> edges;
    inline void add(int x, int y, int cap, int cost)
    {
        edges.push_back({x, y, cap, 0, cost});
        edges.push_back({y, x, 0, 0, -cost});
        int m = edges.size();
        e[x].push_back(m - 2), e[y].push_back(m - 1);
    }
    int dis[maxn], vis[maxn], cur[maxn], s, t;
    bool spfa()
    {
        memset(vis, 0, sizeof(vis));
        memset(dis, 0x3f, sizeof(dis));
        std::queue<int> q;
        q.push(s), dis[s] = 0, vis[s] = 1;
        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            vis[x] = 0;
            for (int i : e[x])
            {
                auto &k = edges[i];
                if (k.cap - k.flow > 0 && dis[x] + k.cost < dis[k.y])
                {
                    dis[k.y] = dis[x] + k.cost;
                    if (!vis[k.y])
                        q.push(k.y), vis[k.y] = 1;
                }
            }
        }
        //cout << dis[t] << endl;
        return dis[t] < 1e8;
    }
    long long mi;
    int dfs(int x, int lim)
    {
        if (x == t || lim == 0)
            return lim;
        int res = 0, f;
        vis[x] = 1;
        for (int &i = cur[x]; i < (int)e[x].size(); i++)
        {
            auto &k = edges[e[x][i]];
            if (vis[k.y] || dis[x] + k.cost != dis[k.y] || (f = dfs(k.y, std::min(lim, k.cap - k.flow))) == 0)
                continue;
            k.flow += f, edges[e[x][i] ^ 1].flow -= f, res += f, mi += k.cost * f, lim -= f;
            if (lim == 0)
                break;
        }
        return res;
    }
    int dinic(int s_, int t_)
    {
        s = s_, t = t_;
        mi = 0;
        int ans = 0;
        while (spfa())
            memset(cur, 0, sizeof(cur)), ans += dfs(s, 1 << 30);
        return ans;
    }
} G;

int main()
{
    int n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 0, a, b, c, d; i < m; i++)
        scanf("%d%d%d%d", &a, &b, &c, &d), G.add(a, b, c, d);
    cout << G.dinic(s, t) << " ";
    cout << G.mi << endl;
}