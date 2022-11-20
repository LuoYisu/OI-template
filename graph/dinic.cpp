#include <vector>
#include <queue>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

namespace solve
{
    const int inf = 1e9;
    const int maxn = 4000;

    template <typename T>
    struct Dinic
    {
        struct edge
        {
            int x, y;
            T cap, flow;
            T now_flow() { return cap - flow; }
        };

        vector<edge> edges;
        vector<int> e[maxn];

        int mx;

        inline int add(int x, int y, T cap)
        {
            edges.push_back({x, y, cap, 0});
            edges.push_back({y, x, 0, 0});
            int m = edges.size();
            e[x].push_back(m - 2), e[y].push_back(m - 1);
            // cerr << "?" << x << " " << y << " " << cap << endl;
            mx = max({mx, x, y});
            return m - 2;
        }

        int cur[maxn], vis[maxn], s, t, dis[maxn];

        bool bfs()
        {
            fill(vis, vis + mx + 1, 0);
            dis[s] = 0, vis[s] = 1;
            queue<int> q;
            q.push(s);
            while (!q.empty())
            {
                int x = q.front();
                q.pop();
                for (int i : e[x])
                {
                    auto &k = edges[i];
                    if (!vis[k.y] && k.cap - k.flow > 0)
                    {
                        dis[k.y] = dis[x] + 1;
                        vis[k.y] = 1, q.push(k.y);
                    }
                }
            }
            return vis[t];
        }

        T dfs(int x, T lim)
        {
            if (x == t || lim == 0)
                return lim;
            T res = 0, f;
            for (int &i = cur[x]; i < (int)e[x].size(); i++)
            {
                auto &k = edges[e[x][i]];
                if (dis[x] + 1 != dis[k.y] || (f = dfs(k.y, min(lim, k.cap - k.flow))) == 0)
                    continue;
                res += f, lim -= f, k.flow += f, edges[e[x][i] ^ 1].flow -= f;
                if (lim == 0)
                    break;
            }
            return res;
        }

        T dinic(int s_, int t_)
        {
            s = s_, t = t_;
            T res = 0;
            while (bfs())
                fill(cur, cur + mx + 1, 0), res += dfs(s, inf);
            return res;
        }

        void clear()
        {
            mx = 0;
            for (int i = 0; i <= mx; i++)
                e[i].clear();
            edges.clear();
        }
        
        Dinic() { clear(); }
    };
}
