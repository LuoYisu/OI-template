// 当只使用 int 时更方便的版本
#include <cstdio>
#include <cstring>

namespace IO
{
    const int mxsiz = 1 << 20;
    char inbuf[mxsiz], *p1, *p2;
    char outbuf[mxsiz], *op = outbuf;
    struct endio
    {
        endio(){};
        ~endio() { fwrite(outbuf, 1, op - outbuf, stdout); }
    } useless_var;
    inline char gc() { return p1 == p2 && (p2 = (p1 = inbuf) + fread(inbuf, 1, mxsiz, stdin), p1 == p2) ? EOF : *p1++; }
#define isdigit(x) (x >= '0' && x <= '9') // 防止忘记打 <cctype> 头文件
    inline int read()
    {
        int x = 0, f = 1;
        char ch = gc();
        for (; !isdigit(ch); ch = gc())
            if (ch == '-')
                f = -1;
        for (; isdigit(ch); ch = gc())
            x = x * 10 + ch - '0';
        return x * f;
    }
    template <typename T>
    inline void read(T &x)
    {
        x = 0;
        int f = 1;
        char ch = gc();
        for (; !isdigit(ch); ch = gc())
            if (ch == '-')
                f = -1;
        for (; isdigit(ch); ch = gc())
            x = x * 10 + ch - '0';
        x *= f;
    }
#undef isdigit
    inline bool ischar(char x)
    {
        return x >= 'A' && x <= 'z';
    }
    inline char readchar()
    {
        char ch = gc();
        while (!ischar(ch))
            ch = gc();
        return ch;
    }
    inline void push(char ch)
    {
        if (op - outbuf == mxsiz)
            fwrite(outbuf, 1, mxsiz, stdout), op = outbuf;
        *op++ = ch;
    }
    template <typename T>
    inline void work_wt(T x)
    {
        if (x > 9)
            work_wt(x / 10);
        push(x % 10 + '0');
    }
    template <typename T>
    inline void write(T x)
    {
        if (x < 0)
            x = -x, push('-');
        work_wt(x);
    }
    inline void writestr(const char *s)
    {
        int n = strlen(s);
        for (int i = 0; i < n; i++)
            push(s[i]);
    }
    inline void endln() { push('\n'); }
    inline void space() { push(' '); }
    template <typename T>
    inline void writeln(T x) { write(x), endln(); }
}
using namespace IO;

int main()
{
}