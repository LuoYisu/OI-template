#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#define clr(a) memset((a), 0, sizeof(a))
using std::cout;
using std::endl;

const int maxn = 1e6 + 5;

struct AC
{
    int tree[maxn][26], ed[maxn], tot, fail[maxn];
    AC() { clr(tree), clr(ed), clr(fail), tot = 0; }
    void insert(const char *s)
    {
        int p = 0;
        for (int i = 0; s[i]; i++)
        {
            int nxt = s[i] - 'a';
            if (!tree[p][nxt])
                tree[p][nxt] = ++tot;
            p = tree[p][nxt];
        }
        ed[p]++;
    }
    void build()
    {
        std::queue<int> q;
        for (int i = 0; i < 26; i++)
            if (tree[0][i])
                q.push(tree[0][i]);
        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            for (int i = 0; i < 26; i++)
                if (tree[x][i])
                    fail[tree[x][i]] = tree[fail[x]][i], q.push(tree[x][i]);
                else
                    tree[x][i] = tree[fail[x]][i];
        }
    }
    int query(const char *s)
    {
        int res = 0, p = 0;
        for (int i = 0; s[i]; i++)
        {
            p = tree[p][s[i] - 'a'];
            for (int j = p; j && ed[j] != -1; j = fail[j])
                res += ed[j], ed[j] = -1;
        }
        return res;
    }
} ac;

char s[maxn];
int n;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%s", s), ac.insert(s);
    ac.build();
    scanf("%s", s);
    printf("%d\n", ac.query(s));
    return 0;
}