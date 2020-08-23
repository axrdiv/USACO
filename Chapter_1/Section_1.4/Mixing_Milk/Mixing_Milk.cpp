/*
ID: axrdiv1
PROG: milk
LANG: C++
*/
#include<fstream>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct farmer {
    int p, a;
    farmer(int p=0, int a=0): p(p), a(a) {};
    bool operator < (const farmer& b) {
        return p < b.p || (p == b.p && a > b.a);
    }
};

vector<farmer> list;

int N, M;
int main() {
    ofstream fout ("milk.out");
    ifstream fin ("milk.in");
    fin >> N >> M;
    for(int i = 0; i < M; i++) {
        int p, a;
        fin >> p >> a;
        list.push_back(farmer(p, a));
    }
    sort(list.begin(), list.end());
    int cnt = 0;
    for(int i = 0; i < (int)list.size() && N > 0; i++) {
        cnt += list[i].p * min(list[i].a, N);
        N -= list[i].a;
    }
    fout << cnt << endl;
    return 0;
}
