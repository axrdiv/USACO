/*
ID: axrdiv1
PROG: cryptcow
LANG: C++
*/

/*
 * 三个限制
 * 1. C O W 三种字母的个数必须匹配, 且去除这三种字母后的字符串长度应与原字符串长度相等
 * 2. 访问过的字符串标记为true, 不必再次访问
 * 3. C O W 之外的字符串顺序应与原字符串相同
 */


#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;

const int MODU = 999991;
bool vis[MODU];

ofstream fout("cryptcow.out");
ifstream fin("cryptcow.in");

string t;
const string s = "Begin the Escape execution at the Break of Dawn";

unsigned int ELFhash(const char *str) {
    unsigned int hash = 0, g;
    while(*str) {
        hash = (hash << 4) + (*str++);
        if(g = hash & 0xf0000000l)
        {
            hash ^= g >> 24;
        }
        hash &= ~g;
    }
    return hash % MODU;
}

bool check(string t) {
    int cnt[256];
    memset(cnt, 0, sizeof(cnt));

    for (int i = 0; i < s.size(); i++) {
        cnt[s[i]]++;
    }
    for (int i = 0; i < t.size(); i++) {
        if (t[i] == 'C' || t[i] == 'O' || t[i] == 'W')
            cnt[t[i]]++;
        else
            cnt[t[i]]--;
    }

    if (!(cnt['C'] == cnt['O'] && cnt['C'] == cnt['W']))
        return false;

    if(cnt['C'] * 3 + s.size() != t.size())
        return false;

    cnt['C'] = cnt['O'] = cnt['W'] = 0;

    for (int i = 0; i < 256; i++) {
        if (cnt[i])
            return false;
    }

    return true;
}

string transform(string t, int c, int o, int w) {
    string tmp;
    tmp += t.substr(0, c);
    tmp += t.substr(o + 1, w - o - 1);
    tmp += t.substr(c + 1, o - c - 1);
    tmp += t.substr(w + 1);
    return tmp;
}

bool impossible(string tmp) {
    int i = 0, j;
    while(i < tmp.size()) {
        j = i + 1;
        if (tmp[i] != 'C' && tmp[i] != 'O' && tmp[i] != 'W') {
            while(j < tmp.size() && tmp[j] != 'C' && tmp[j] != 'O' && tmp[j] != 'W')
                j++;
            if(s.find(tmp.substr(i, j - i)) == string::npos)
                return true;
        }
        i = j;
    }
    return false;
}

bool dfs(string tmp) {
    unsigned hash = ELFhash(tmp.c_str());
    if(vis[hash]) return false;
    vis[hash] = true;

    if (impossible(tmp))
        return false;

    if (tmp == s)
        return true;

    for (int o = 0; o < tmp.size(); o++) {
        if (tmp[o] != 'O') continue;
        for (int c = 0; c < o; c++) {
            if (tmp[c] != 'C') continue;
            for (int w = tmp.size() - 1; w > o; w--) {
                if (tmp[w] != 'W') continue;
                if(dfs(transform(tmp, c, o, w)))
                    return true;
            }
        }
    }
    return false;
}


int main() {
    getline(fin, t);

    if (!check(t) || !dfs(t)) 
        fout << 0 << " " << 0 << endl;
    else
        fout << "1 " << count(t.begin(), t.end(), 'C') << endl;


    return 0;
}
