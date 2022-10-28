#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct
{
    int n, d;
} frac;

int f_get_int(char *s, int begin, int *end)
{
    for (int i = begin; i <= strlen(s); ++i)
    {
        if (!isdigit(s[i]))
        {
            if (end) *end = i - 1;
            char *r = calloc(i - begin + 2, sizeof(char));
            memcpy(r, s + begin, i - begin + 1);
            int a = atoi(r);
            free(r);
            return a;
        }
    }

    exit(1);
}

frac parse_frac(char *s)
{
    bool n = s[0] == '-';
    int e = n ? 1 : 0;
    int w = 0;

    if (strchr(s, '_'))
    {
        w = f_get_int(s, e, &e);
        e += 2;
    }

    frac f;
    f.n = f_get_int(s, e, &e);
    if (strchr(s, '/'))
        f.d = f_get_int(s, e + 2, 0);
    else
        f.d = 1;
    f.n += w * f.d;
    f.n *= n ? -1 : 1;
    return f;
}

#define fscale(f,s) { f.n *= s; f.d *= s; }
#define swap(a,b){ int t = a; a = b; b = t; }

frac calc(frac a, frac b, char op)
{
    frac r;
    switch (op)
    {
    case '+': case '-':
    {
        int d = a.d;
        fscale(a, b.d);
        fscale(b, d);
        r.n = a.n + b.n * (op == '-' ? -1 : 1);
        r.d = a.d;
    } break;
    case '/': swap(b.n, b.d);
    case '*':
        r.n = a.n * b.n;
        r.d = a.d * b.d;
        break;
    }

    return r;
}

frac simplify(frac f)
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
void display(frac f)
{
    int whole = f.n / f.d;
    int sign = sig(f.n) * sig(f.d);
    f.n = abs(f.n); f.d = abs(f.d);
    f.n = f.n % f.d;

    if (whole)
    {
        printf("%d", whole);

        if (f.n)
            printf("_%d/%d", f.n, f.d);
    }
    else
    {
        if (f.n)
            printf("%d/%d", sign * f.n, f.d);
        else
            putchar('0');
    }

    putchar('\n');
}

int main(int argc, char **argv)
{
    frac a = parse_frac(argv[1]);
    frac b = parse_frac(argv[3]);
    display(simplify(calc(a, b, argv[2][0])));

    return 0;
}
