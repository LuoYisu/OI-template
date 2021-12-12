#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <random>
using std::cout;
using std::endl;
const int maxn = 1e5 + 10;
class Treap
{
public:
    struct Node
    {
        Node *son[2];
        int num, rnd, siz;
        int val;
        void push_up()
        {
            siz = num;
            for (int i = 0; i < 2; i++)
                if (son[i] != nullptr)
                    siz += son[i]->siz;
        }
    } a[maxn];
    int tot;
    Node *root;
    Treap() : tot(0), root(nullptr) { memset(a, 0, sizeof(a)); }
    int get_size(const Node *x) { return x == nullptr ? 0 : x->siz; }
    /*
    void output(Node *&now, const int &indent)
    {
        putchar('>'), putchar(' ');
        for (int i = 0; i < indent; ++i)
            putchar('|'), putchar(' ');
        if (!now)
        {
            puts("NULL");
            return;
        }
        printf("%ld:%d %d,%d %u\n", now - a, now->val, now->siz, now->num, now->rnd);
        output(now->son[0], indent + 1);
        output(now->son[1], indent + 1);
    }
    inline void output() { output(root, 0); }
    */
    Node *new_node(int x)
    {
        tot++;
        a[tot].val = x, a[tot].num = a[tot].siz = 1, a[tot].rnd = rand();
        a[tot].son[0] = a[tot].son[1] = nullptr;
        return &a[tot];
    }
    void rotate(Node *&now, const bool d) // 1: left 0: right
    {
        Node *t = now->son[d];
        now->son[d] = t->son[d ^ 1];
        t->son[d ^ 1] = now;
        t->push_up(), now->push_up();
        now = t;
    }
    void insert(Node *&now, const int x)
    {
        if (now == nullptr)
        {
            now = new_node(x);
            return;
        }
        (now->siz)++;
        if (now->val != x)
        {
            bool d = now->val < x;
            insert(now->son[d], x);
            if (now->rnd < now->son[d]->rnd)
                rotate(now, d);
        }
        else
            ++(now->num);
        now->push_up();
    }
    inline void insert(int x) { insert(root, x); }
    void erase(Node *&now, int x)
    {
        if (now == nullptr)
            return;
        if (now->val != x)
            erase(now->son[now->val < x], x);
        else if (now->son[0] != nullptr && (now->son[1] == nullptr || now->son[0]->rnd > now->son[1]->rnd))
            rotate(now, 0), erase(now->son[1], x);
        else if (now->son[1] != nullptr)
            rotate(now, 1), erase(now->son[0], x);
        else
        {
            --(now->siz), --(now->num);
            if (!now->num)
                now = nullptr;
            return;
        }
        now->push_up();
    }
    inline void erase(int x) { erase(root, x); }
    int get_rank(Node *&now, int x)
    {
        if (now == nullptr)
            return 0;
        if (now->val < x)
            return get_rank(now->son[1], x) + get_size(now->son[0]) + now->num;
        else if (now->val > x)
            return get_rank(now->son[0], x);
        else
            return get_size(now->son[0]) + 1;
    }
    inline int get_rank(int x) { return get_rank(root, x); }
    int rank(Node *now, int x)
    {
        if (now == nullptr)
            return 0;
        if (now->son[0] != nullptr && now->son[0]->siz >= x)
            return rank(now->son[0], x);
        else if (get_size(now->son[0]) + now->num < x)
            return rank(now->son[1], x - get_size(now->son[0]) - now->num);
        else
            return now->val;
    }
    inline int rank(int x) { return rank(root, x); }
    int prefix(Node *now, int x)
    {
        if (now == nullptr)
            return -(1 << 30);
        else if (now->val >= x)
            return prefix(now->son[0], x);
        else
            return std::max(now->val, prefix(now->son[1], x));
    }
    inline int prefix(int x) { return prefix(root, x); }
    int suffix(Node *now, int x)
    {
        if (now == nullptr)
            return 1 << 30;
        else if (now->val <= x)
            return suffix(now->son[1], x);
        else
            return std::min(now->val, suffix(now->son[0], x));
    }
    inline int suffix(int x) { return suffix(root, x); }
} treap;

int main()
{
    srand(time(0));
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int opt, x;
        scanf("%d%d", &opt, &x);
        if (opt == 1)
            treap.insert(x);
        else if (opt == 2)
            treap.erase(x);
        else if (opt == 3)
            printf("%d\n", treap.get_rank(x));
        else if (opt == 4)
            printf("%d\n", treap.rank(x));
        else if (opt == 5)
            printf("%d\n", treap.prefix(x));
        else
            printf("%d\n", treap.suffix(x));
    }
    return 0;
}
