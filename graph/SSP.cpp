#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int maxn = 5e3 + 10;
const int inf = 1e9;
typedef long long ll;

template <typename T>
struct Dinic
{
    struct edge
    {
        int x, y, cap, flow;
        T cost;
    };
    vector<edge> edges;
    vector<int> e[maxn];

    int mx;

    inline void add(int x, int y, int cap, T cost)
    {
        edges.push_back({x, y, cap, 0, cost});
        edges.push_back({y, x, 0, 0, -cost});
        int m = edges.size();
        e[x].push_back(m - 2), e[y].push_back(m - 1);
        mx = max({mx, x, y});
    }
    T dis[maxn];
    int vis[maxn], cur[maxn], s, t;

    bool spfa()
    {
        queue<int> q;
        fill(dis, dis + mx + 1, inf), memset(vis, 0, sizeof(int) * (mx + 2));
        dis[s] = 0, vis[s] = 1, q.push(s);
        while (!q.empty())
        {
            int x = q.front();
            q.pop(), vis[x] = 0;
            for (int i : e[x])
            {
                auto &k = edges[i];
                if (k.cap - k.flow > 0 && k.cost + dis[x] < dis[k.y])
                {
                    dis[k.y] = dis[x] + k.cost;
                    if (!vis[k.y])
                        q.push(k.y), vis[k.y] = 1;
                }
            }
        }
        return dis[t] < inf;
    }

    T mcmf;

    int dfs(int x, int lim)
    {
        if (x == t || lim == 0)
            return lim;
        vis[x] = 1;
        int res = 0, f;
        for (signed &i = cur[x]; i < (int)e[x].size(); i++)
        {
            auto &k = edges[e[x][i]];
            if (dis[x] + k.cost != dis[k.y] || vis[k.y] || (f = dfs(k.y, min(lim, k.cap - k.flow))) == 0)
                continue;
            mcmf += 1ll * f * k.cost;
            k.flow += f, edges[e[x][i] ^ 1].flow -= f, res += f, lim -= f;
            if (lim == 0)
                break;
        }
        vis[x] = 0;
        return res;
    }

    T dinic(int s_, int t_)
    {
        s = s_, t = t_;
        mcmf = 0;
        int ans = 0;
        while (spfa())
            memset(cur, 0, sizeof(int) * (t + 2)), ans += dfs(s, inf);
        return mcmf;
    }
};
