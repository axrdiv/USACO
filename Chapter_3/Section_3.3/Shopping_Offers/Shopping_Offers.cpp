/*
ID: axrdiv1
PROG: shopping
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<map>
using namespace std;
const int maxn = 1000;

int ctoi[maxn];
int itoc[5];
int price[5];

struct offe {
    int num[5] = {0}, p;
    offe() {}
};

struct item {
    int num[5] = {0};
    item apply(const offe& of) {
        item ret;
        for(int i = 0; i < 5; i++) ret.num[i] = num[i] - of.num[i];
        return ret;
    }
    bool exist() {
        for(int i = 0; i < 5; i++) if(num[i] < 0) return false;
        return true;
    }
    bool operator< (const item& n) const {
        for(int i = 0; i < 5; i++) {
            if(num[i] == n.num[i]) continue;
            return num[i] < n.num[i];
        }
        return false;
    }
};
map<item, int> d;

ofstream fout("shopping.out");
ifstream fin("shopping.in");


vector<offe> offers;

int dp(item it) {
    if(d.count(it)) return d[it];
    d[it] = 0;
    for(int i = 0; i < 5; i++) d[it] += it.num[i] * price[i];

    for(int i = 0; i < (int)offers.size(); i++) {
        item nit = it.apply(offers[i]);
        if(nit.exist()) d[it] = min(d[it], offers[i].p + dp(nit));
    }
    return d[it];
}

int s, b;
int main() {
    for(int i = 0; i < maxn; i++) ctoi[i] = -1;
    fin >> s;
    int n, c, k, cnt = 0;
    for(int i = 0; i < s; i++) {
        fin >> n;
        offers.push_back(offe());
        for(int j = 0; j < n; j++) {
            fin >> c >> k;
            if(ctoi[c] == -1) {
                ctoi[c] = cnt;
                itoc[cnt] = c;
                cnt++;
            }
            offers[i].num[ctoi[c]] = k;
        }
        fin >> offers[i].p;
    }
    fin >> b;
    item st;
    for(int i = 0; i < b; i++) {
        fin >> c >> k;
        if(ctoi[c] == -1) {
            ctoi[c] = cnt;
            itoc[cnt] = c;
            cnt++;
        }
        st.num[ctoi[c]] = k;
        fin >> price[ctoi[c]];
    }
    /*
    cout << "offers.size() = " << offers.size() << endl;
    for(int i = 0; i < offers.size(); i++) {
        for(int j = 0; j < 5; j++)
            cout << offers[i].num[j] << " ";
        cout << endl;
    }
    for(map<item, int>::iterator it = d.begin(); it != d.end(); it++) {
        for(int i = 0; i < 5; i++) 
            cout << (*it).first.num[i] << " ";
        cout << (*it).second << endl;
    }
    */
    fout << dp(st) << endl;
    return 0;
}
