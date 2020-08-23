/*
ID: axrdiv1
PROG: prefix
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<set>
#include<string>
using namespace std;

set<string> prim[13];

const int maxl = 200000 + 10;
bool d[maxl];

string S;

void dp() {
    string t;
    for(int i = 1; i <= S.size(); i++) {
        for(int j = 1; j <= min(i, 13); j++) {
            if(d[i-j] == 0 || !prim[j].size()) continue;
            t = S.substr(i-j, j);
            // cout << i-j << "-" << j << " " << t << endl;
            if(prim[j].count(t)) {
                d[i] = 1;
                break;
            }
        }
    }
}

int main() {
    ofstream fout("prefix.out");
    ifstream fin("prefix.in");
    string tmp;
    while((fin >> tmp) && tmp != ".") {
        prim[tmp.size()].insert(tmp);
    }
    while((fin >> tmp) && tmp.size()) {
        S += tmp;
    }
    d[0] = 1;
    dp();
    for(int i = S.size(); i >= 0; i--) {
        if(d[i]) {
            fout << i << endl;
            break;
        }
    }
    return 0;
}
