/*
ID: axrdiv1
PROG: gift1
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<vector>
using namespace std;

map<string, int> nti;
map<int, string> itn;
int np, cnt[11] = {0};

int main() {
    ofstream fout ("gift1.out");
    ifstream fin ("gift1.in");
    fin >> np;
    string name;
    for(int i = 0; i < np; i++) {
        fin >> name;
        nti.insert({name, i});
        itn.insert({i, name});
    }
    while(fin >> name) {
        int idx = nti[name];
        int amount, num;
        fin >> amount >> num;
        if(num == 0) continue;
        cnt[idx] -= (amount / num) * num;
        for(int i = 0; i < num; i++) {
            fin >> name;
            cnt[nti[name]] += amount / num;
        }
    }
    for(int i = 0; i < np; i++) 
        fout << itn[i] << " " << cnt[i] << endl;
    return 0;
}
