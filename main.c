#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct
{
    int n, d;
} ff;

int g(char *s, int b, int *e)
{
    for (int i = b; i <= strlen(s); ++i)
    {
        if (!isdigit(s[i]))
        {
            if (e) *e = i - 1;
            char *r = calloc(i - b + 2, sizeof(char));
            memcpy(r, s + b, i - b + 1);
            int a = atoi(r);
            free(r);
            return a;
        }
    }

    exit(1);
}

ff p(char *s)
{
    bool n = s[0] == '-';
    int e = n ? 1 : 0;
    int w = 0;

    if (strchr(s, '_'))
    {
        w = g(s, e, &e);
        e += 2;
    }

    ff f;
    f.n = g(s, e, &e);
    if (strchr(s, '/'))
        f.d = g(s, e + 2, 0);
    else
        f.d = 1;
    f.n += w * f.d;
    f.n *= n ? -1 : 1;
    return f;
}

#define s(f,s) { f.n *= s; f.d *= s; }
#define sw(a,b){ int t = a; a = b; b = t; }

ff c(ff a, ff b, char op)
{
    ff r;
    switch (op)
    {
    case '+': case '-':
    {
        int d = a.d;
        s(a, b.d);
        s(b, d);
        r.n = a.n + b.n * (op == '-' ? -1 : 1);
        r.d = a.d;
    } break;
    case '/': sw(b.n, b.d);
    case '*':
        r.n = a.n * b.n;
        r.d = a.d * b.d;
        break;
    }

    return r;
}

ff fy(ff f)
{
    int gcf = 1;
    for (int i = 1; i <= abs(f.n) && i <= abs(f.d); ++i)
    {
        if (f.n % i == 0 && f.d % i == 0)
            gcf = i;
    }

    f.n /= gcf;
    f.d /= gcf;
    return f;
}

#define sig(a) (a < 0 ? -1 : 1)
void d(ff f)
{
    int w = f.n / f.d;
    int s = sig(f.n) * sig(f.d);
    f.n = abs(f.n); f.d = abs(f.d);
    f.n = f.n % f.d;

    if (w)
    {
        printf("%d", w);

        if (f.n)
            printf("_%d/%d", f.n, f.d);
    }
    else
    {
        if (f.n)
            printf("%d/%d", s * f.n, f.d);
        else
            putchar('0');
    }

    putchar('\n');
}

int main(int argc, char **argv)
{
    ff a = p(argv[1]);
    ff b = p(argv[3]);
    d(fy(c(a, b, argv[2][0])));

    return 0;
}
