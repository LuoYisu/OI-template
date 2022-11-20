#include <cstdio>
#include <cstring>
#include <cctype>

namespace IO
{
    const int mxsiz = 1 << 14;

    char inbuf[mxsiz], *p1, *p2;
    char outbuf[mxsiz], *op = outbuf;

    inline void flush() { fwrite(outbuf, 1, op - outbuf, stdout), op = outbuf; }
    struct endio
    {
        endio(){};
        ~endio() { flush(); }
    } useless_var;
    inline char gc()
    {
        if (p1 == p2)
            p1 = inbuf, p2 = p1 + fread(inbuf, 1, mxsiz, stdin);
        return p1 == p2 ? EOF : *p1++;
    }
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
    template <typename T, typename... Args>
    inline void read(T &x, Args &...args) { read(x), read(args...); }
    inline void read(char &ch)
    {
        ch = gc();
        while (!isgraph(ch))
            ch = gc();
    }
    inline void push(char ch)
    {
        if (op - outbuf == mxsiz)
            fwrite(outbuf, 1, mxsiz, stdout), op = outbuf;
        *op++ = ch;
    }
    template <typename... Args>
    inline void push(char ch, Args... args) { push(ch), push(args...); }
    inline void endln() { push('\n'); }
    inline void space() { push(' '); }
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
    inline void write(char ch) { push(ch); }
    inline void write(const char *s)
    {
        int n = strlen(s);
        for (int i = 0; i < n; i++)
            push(s[i]);
    }
    template <typename T, typename... Args>
    inline void write(T x, Args... args) { write(x), write(args...); }
    template <typename T>
    inline void write_with_space(T x) { write(x), space(); }
    template <typename T, typename... Args>
    inline void write_with_space(T x, Args... args) { write_with_space(x), write_with_space(args...); }
    template <typename... Args>
    inline void writeln(Args... x) { write_with_space(x...), endln(); }
};
using IO::endln;
using IO::gc;
using IO::read;
using IO::space;
using IO::write;
using IO::write_with_space;
using IO::writeln;

int main()
{
}