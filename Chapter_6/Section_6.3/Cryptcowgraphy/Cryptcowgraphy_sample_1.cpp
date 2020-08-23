/*
ID:maxkibb3
LANG:C++
PROB:cryptcow
*/
 
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
 
const int HASH_SIZE = 1e6 + 7;
 
bool table[HASH_SIZE], table2[HASH_SIZE];
string s, t = "Begin the Escape execution at the Break of Dawn";
 
int getHash(const string &str) {
    unsigned long h = 0, g;
    for(int i = 0; i < str.length(); i++) {
        h = (h << 4) + str[i];
        g = h & 0xf0000000l;
        if(g) h ^= g >> 24;
        h &= ~g;
    }
    return h % HASH_SIZE;
}
 
string transform(const string &str, int c, int o, int w) {
    int idx = 0, len = str.length();
    static char buffer[80];
    for(int i = 0; i < c; i++) buffer[idx++] = str[i];
    for(int i = o + 1; i < w; i++) buffer[idx++] = str[i];
    for(int i = c + 1; i < o; i++) buffer[idx++] = str[i];
    for(int i = w + 1; i < len; i++) buffer[idx++] = str[i];
    buffer[idx++] = 0;
    return string(buffer);
}
 
bool impossible(const string &str) {
    int len = str.length();
    if((len - t.length()) % 3 != 0) return true;
    int i = 0, j;
    while(i < len) {
        j = i + 1;
        if(str[i] != 'C' && str[i] != 'O' && str[i] != 'W') {
            while(j < len) {
                if(str[j] == 'C' || str[j] == 'O' || str[j] == 'W')
                    break;
                j++;
            }
            if(t.find(str.substr(i, j - i)) == string::npos)
                return true;
        }
        i = j;
    }
    return false;
}
 
bool dfs(string str) {
    cout << "dfs" << endl;
    int hash = getHash(str);
    if(table[hash]) return false;
    table[hash] = true;
 
    if(impossible(str)) return false;
 
    if(str == t) return true;
 
    int len = str.length();
    for(int o = 1; o < len - 1; o++) {
        if(str[o] != 'O') continue;
        for(int c = 0; c < o; c++) {
            if(str[c] != 'C') continue;
            for(int w = len - 1; w > o; w--) {
                if(str[w] != 'W') continue;
                if(dfs(transform(str, c, o, w)))
                    return true;
            }
        }
    }
 
    return false;
}
 
int main() {
    freopen("cryptcow.in", "r", stdin);
    // freopen("cryptcow.out", "w", stdout);
    getline(cin, s);
 
    if(dfs(s)) {
        cout << "1 " << count(s.begin(), s.end(), 'C') << endl;
    }
    else {
        cout << "0 0" << endl;
    }
 
    return 0;
}
