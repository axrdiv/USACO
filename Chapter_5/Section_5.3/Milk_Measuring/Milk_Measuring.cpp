/*
ID: axrdiv1
PROG: milk4
LANG: C++
*/

// A* algorithm

#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;

const int MAXQ = 20000;
int dp[MAXQ];

ofstream fout("milk4.out");
ifstream fin("milk4.in");

int Q, P;
vector<int> pails;

bool is_ans(vector<int> vec) {
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for(int i = 0; i < Q; i++) {
        if(dp[i]) {
            for(int j = 0; j < (int)vec.size(); j++) {
                int t = i + vec[j];
                if(t == Q) return true;
                if(t < Q) dp[t] = 1;
            }
        }
    }
    return false;
}
struct cmp {
    bool operator()(const vector<int>& va, const vector<int>& vb) {
        if(va.size() != vb.size()) return va.size() > vb.size();
        for(int i = 0; i < (int)va.size(); i++) {
            if(va[i] != vb[i]) return va[i] > vb[i];
        }
        return false;
    }
};

void solve() {
    priority_queue<vector<int>, vector<vector<int> >, cmp> que;
    for(int i = 0; i < (int)pails.size(); i++) {
        vector<int> v;
        v.push_back(pails[i]);
        que.push(v);
    }

    vector<int> v;
    while(!que.empty()) {
        v = que.top();
        que.pop();
        if(is_ans(v)) {
            fout << v.size();
            for(int i = 0; i < (int)v.size(); i++) {
                fout << " " << v[i];
            }
            fout << endl;
            return;
        }
        int st = upper_bound(pails.begin(), pails.end(), v.back()) - pails.begin();
        for(int i = st; i < (int)pails.size(); i++) {
            vector<int> nv = v;
            nv.push_back(pails[i]);
            que.push(nv);
        }
    }
}

int main() {
    fin >> Q >> P;
    int p;
    for(int i = 0; i < P; i++) {
        fin >> p;
        pails.push_back(p);
    }
    sort(pails.begin(), pails.end());

    solve();

    return 0;
}
