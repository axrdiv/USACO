/*
ID: axrdiv1
PROG: contact
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

struct Cnt {
    string s;
    int c;
    Cnt(string s, int c): s(s), c(c) {}
    bool operator< (const Cnt& b) const {
        return c > b.c || (c == b.c && s.size() < b.s.size()) || (c == b.c && s.size() == b.s.size() && s < b.s);
    }
};

map<string, int> idx;
vector<Cnt> vec;

ofstream fout("contact.out");
ifstream fin("contact.in");

int A, B, N;
string seq;
int main() {
    fin >> A >> B >> N;
    string tmp;
    while((fin >> tmp) && tmp.size()) {
        seq += tmp;
    }
    int tid = 0;
    for(int i = 0; i < seq.size(); i++) {
        for(int j = A; i+j <= seq.size() && j <= B; j++) {
            string st = seq.substr(i, j);
            if(!idx.count(st)) {
                idx[st] = tid++;
                vec.push_back(Cnt(st, 0));
            }
            vec[idx[st]].c++;
        }
    }

    sort(vec.begin(), vec.end());

    int tcnt = 0, lcnt;
    for(int i = 0; i < vec.size(); i++) {
        if(tcnt != vec[i].c) {
            tcnt = vec[i].c;
            N--; if(N == -1) break;
            fout << tcnt << endl;
            lcnt = 0;
        } else { lcnt++; if(lcnt == 6) { fout << endl; lcnt = 0; }}
        if(lcnt == 0) fout << vec[i].s;
        else fout << " " << vec[i].s;
        if(i+1 == vec.size() || vec[i+1].c != tcnt) 
            fout << endl;
    }

    return 0;
}
