#include <cstdio>
#include <cstring>

const int maxn = 1e6 + 10;

char a[maxn], b[maxn];
int n, m, ans;
int nxt[maxn];

void get_nxt()
{
    for (int i = 2, j = 0; i <= m; i++)
    {
        while (j > 0 && b[i] != b[j + 1])
            j = nxt[j];
        if (b[i] == b[j + 1])
            j++;
        nxt[i] = j;
    }
}

void solve()
{
    for (int i = 1, j = 0; i <= n; i++)
    {
        while (j > 0 && a[i] != b[j + 1])
            j = nxt[j];
        if (a[i] == b[j + 1])
            j++;
        if (j == m)
            printf("%d\n", i - m + 1), j = nxt[j];
    }
}

int main()
{
    scanf("%s%s", a + 1, b + 1);
    n = strlen(a + 1), m = strlen(b + 1);
    get_nxt();
    solve();
    for (int i = 1; i <= m; i++)
        printf("%d ", nxt[i]);
    puts("");
}