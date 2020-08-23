/*
ID: axrdiv1
PROG: lgame
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

ofstream fout("lgame.out");
ifstream fin("lgame.in");
ifstream fd("lgame.dict");

const int score[] = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7};

void word2arradd(const string& word, vector<int>& v) {
    for(int c = 0; c < (int) word.size(); c++)
        v[word[c]-'a'] += 1;
}

bool vless(const vector<int>& a, const vector<int>& b) {
    for(int i = 0; i < (int)a.size(); i++) {
        if(a[i] < b[i]) return false;
    }
    return true;
}

int w2score(const string& word) {
    int ret = 0;
    for(int i = 0; i < (int)word.size(); i++) {
        ret += score[word[i]-'a'];
    }
    return ret;
}

vector<pair<string, int> > list;

int main() {
    string word, s;
    fin >> word;
    sort(word.begin(), word.end());
    vector<int> cw(26, 0);
    word2arradd(word, cw);

    while(fd >> s) {
        if(s == ".") break;
        bool flag = 1;
        for(int i = 0; i < (int)s.size(); i++) {
            if(word.find(s[i]) == string::npos) {
                flag = 0; break;
            }
        }
        vector<int> cs(26, 0); word2arradd(s, cs);
        if(!vless(cw, cs))
            continue;

        if(flag) {
            int sc = w2score(s);
            list.push_back(make_pair(s, sc));
        }
    }
    list.push_back(make_pair("", 0));

    int mscore = 0;
    vector<string> ans;
    for(int i = 0; i < (int)list.size()-1; i++) {
        vector<int> cs1(26, 0); word2arradd(list[i].first, cs1);
        for(int j = i+1; j < (int)list.size(); j++) {
            vector<int> cs2(cs1);
            word2arradd(list[j].first, cs2);
            if(vless(cw, cs2)) {
                if(mscore < list[i].second + list[j].second) {
                    mscore = list[i].second + list[j].second;
                    ans.clear();
                }
                if(mscore == list[i].second + list[j].second) {
                    string s = list[i].first;
                    if(list[j].first.size()) s += " " + list[j].first;
                    ans.push_back(s);
                }
            }
        }
    }
    fout << mscore << endl;
    for(int i = 0; i < (int)ans.size(); i++) {
        fout << ans[i] << endl;
    }

    return 0;
}
