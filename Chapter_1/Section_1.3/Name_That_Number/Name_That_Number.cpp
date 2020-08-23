/*
ID: axrdiv1
PROG: namenum
LANG: C++
*/
#include<fstream>
#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

vector<string> dict;
vector<string> ret;

map<char, int> mapping;

bool is_samenum(string& a, string& b) {
    for(int i = 0; i < b.size(); i++) {
        if(mapping[a[i]] != (b[i] - '0'))
            return false;
    }
    return true;
}

int main() {
    int cnt = 6;
    for(int i = 0; i < 25; i++) {
        if(i == 16) continue;
        // cout << (char)('A' + i) << ": " << cnt/3 << endl;
        mapping.insert(make_pair('A'+i, cnt/3));
        cnt++;
    }
    ofstream fout ("namenum.out");
    ifstream fin ("namenum.in");
    ifstream fdic ("dict.txt");
    string s;
    while(fdic >> s) dict.push_back(s);
    fin >> s;

    for(int i = 0; i < (int)dict.size(); i++) {
        if(dict[i].size() == s.size()) {
            if(is_samenum(dict[i], s)) ret.push_back(dict[i]);
        }
    }
    if(ret.size()) {
        sort(ret.begin(), ret.end());
        for(int i = 0; i < ret.size(); i++) {
            fout << ret[i] << endl;
        }
    } else {
        fout << "NONE" << endl;
    }
    return 0;
}
