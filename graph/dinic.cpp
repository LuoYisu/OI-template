#include <algorithm>
#include <cassert>
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

const int maxn = 210;
const int inf = 1 << 30;
typedef long long ll;

struct edge
{
    int x, y;
    int cap, flow;
};

struct Dinic
{
    std::vector<edge> edges;
    std::vector<int> e[maxn];

    int s, t;

    inline void add(int x, int y, int cap)
    {
        edges.push_back({x, y, cap, 0});
        edges.push_back({y, x, 0, 0});
        int m = edges.size();
        e[x].push_back(m - 2), e[y].push_back(m - 1);
    }

    int cur[maxn], dis[maxn], vis[maxn];

    bool bfs()
    {
        std::queue<int> q;
        memset(vis, 0, sizeof(vis));
        q.push(s), vis[s] = 1, dis[s] = 0;
        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            for (auto i : e[x])
            {
                auto &k = edges[i];
                if (!vis[k.y] && k.cap > k.flow)
                    dis[k.y] = dis[x] + 1, q.push(k.y), vis[k.y] = 1;
            }
        }
        return vis[t] > 0;
    }

    int dfs(int x, int lim)
    {
        if (x == t || lim == 0)
            return lim;
        ll res = 0;
        for (int &i = cur[x]; i < (int)e[x].size(); i++)
        {
            auto &k = edges[e[x][i]];
            if (dis[k.y] != dis[x] + 1)
                continue;
            int f = dfs(k.y, std::min(lim, k.cap - k.flow));
            if (f == 0)
                continue;
            k.flow += f, edges[e[x][i] ^ 1].flow -= f, res += f, lim -= f;
            if (lim == 0)
                break;
        }
        return res;
    }

    ll dinic(int s_, int t_)
    {
        s = s_, t = t_;
        ll ans = 0;
        while (bfs())
            memset(cur, 0, sizeof(cur)), ans += dfs(s, inf);
        return ans;
    }
} G;
