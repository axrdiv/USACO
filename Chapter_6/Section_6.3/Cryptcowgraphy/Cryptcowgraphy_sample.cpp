/*
TASK:cryptcow
LANG:C++
*/

#include <cstdio>
#include <cstring>

using namespace std;

const char *S = "Begin the Escape execution at the Break of Dawn";
const int lens = strlen(S);
const int MODU = 999991;

char buf[100];
int n, node;
bool hash[MODU];

bool check()
{
    int cnt[256], k = 0;
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < lens; ++i)
        cnt[S[i]]++;
    for (int i = 0; i < n; ++i)
        if (buf[i] != 'C' && buf[i] != 'O' && buf[i] != 'W')
            cnt[buf[i]]--;
        else k++;
    for (int i = 0; i < 256; ++i)
        if (cnt[i]) return false;
    return k % 3 == 0 && lens == n - k;
}

bool match(int k)
{
    if (k == n || buf[k] == 'C' || buf[k] == 'O' || buf[k] == 'W') return true;
    int f[200];
    f[0] = f[1] = 0;
    for (int i = 1; i < n - k; ++i)
    {
        int j = f[i];
        if (buf[k + i] == buf[k + j]) f[i + 1] = j + 1;
        else f[i + 1] = 0;
    }
    int j = 0;
    for (int i = 0; i < lens; ++i)
    {
        while (j != 0 && S[i] != buf[k + j]) j = f[j];
        if (S[i] == buf[k + j]) j++;
        if (k + j == n || buf[k + j] == 'C' || buf[k + j] == 'O' || buf[k + j] == 'W') return true;
    }
    return false;
}

bool judge()
{
    for (int i = 0; i < n; ++i)
    {
        if (buf[i] == 'W' || buf[i] == 'C' || buf[i] == 'O')
        {
            if (buf[i] == 'C') break;
            if (buf[i] == 'O' || buf[i] == 'W') return false;
        }
        else if (buf[i] != S[i]) return false;
    }
    for (int i = 0; i < n; ++i)
        if (buf[i] == 'C' || buf[i] == 'O' || buf[i] == 'W')
            if (!match(i + 1)) return false;
    return true;
}

int ELFhash(char *str)
{
    unsigned int h = 0, g;
    while (*str)
    {
        h = (h << 4) + (*str++);
        if (g = h & 0xf0000000l)
        {
            h ^= g >> 24;
        }
        h &= ~g;
    }
    return h % MODU;
}

bool dfs(int dep)
{
    unsigned int h = ELFhash(buf);
    if (hash[h]) return false;
    hash[h] = true;
    if (!strcmp(buf, S))
    {
        printf("1 %d\n", dep);
        return true;
    }
    char now[100];
    int len = n;
    memcpy(now, buf, sizeof(buf));
    for (int j = 0; j < len; ++j) if (now[j] == 'O')
        for (int i = 0; i < j; ++i) if (now[i] == 'C')
            for (int k = len - 1; k > j; --k) if (now[k] == 'W')
            {
                n = 0;
                for (int lv = 0; lv < i; ++lv)
                    buf[n++] = now[lv];
                for (int lv = j + 1; lv < k; ++lv)
                    buf[n++] = now[lv];
                for (int lv = i + 1; lv < j; ++lv)
                    buf[n++] = now[lv];
                for (int lv = k + 1; lv < len; ++lv)
                    buf[n++] = now[lv];
                buf[n] = '\0';
                if (judge() && dfs(dep + 1)) return true;
            }
    return false;
}

int main()
{
    freopen("cryptcow.in", "r", stdin);
    freopen("cryptcow.out", "w", stdout);
    fgets(buf, 100, stdin);
    n = strlen(buf) - 1;
    buf[n] = '\0';
    node = 0;
    memset(hash, false, sizeof(hash));
    if (!check() || !judge() || !dfs(0)) printf("0 0\n");
    return 0;
}