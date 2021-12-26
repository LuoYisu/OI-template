#include <stdio.h>
#include <string.h>
#define mxsiz 1 << 20

char inbuf[mxsiz], *p1, *p2;
char outbuf[mxsiz], *op = outbuf;

#define gc() (p1 == p2 && (p2 = (p1 = inbuf) + fread(inbuf, 1, mxsiz, stdin), p1 == p2) ? EOF : *p1++)

#define isdigit(x) (x >= '0' && x <= '9') // 防止忘记打 <cctype> 头文件
static inline int read()
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
#undef isdigit
static inline int ischar(char x)
{
    return x >= 'A' && x <= 'z';
}
static inline char readchar()
{
    char ch = gc();
    while (!ischar(ch))
        ch = gc();
    return ch;
}
static inline void push(char ch)
{
    if (op - outbuf == mxsiz)
        fwrite(outbuf, 1, mxsiz, stdout), op = outbuf;
    *op++ = ch;
}
static inline void work_wt(int x)
{
    if (x > 9)
        work_wt(x / 10);
    push(x % 10 + '0');
}
static inline void write(int x)
{
    if (x < 0)
        x = -x, push('-');
    work_wt(x);
}
static inline void writestr(const char *s)
{
    int n = strlen(s);
    for (int i = 0; i < n; i++)
        push(s[i]);
}
static inline void endln() { push('\n'); }
static inline void space() { push(' '); }
static inline void writeln(int x) { write(x), endln(); }
static inline void endio() { fwrite(outbuf, 1, op - outbuf, stdout); }

int main()
{
}