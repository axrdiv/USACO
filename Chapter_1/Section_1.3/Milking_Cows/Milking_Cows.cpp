/*
ID: axrdiv1
PROG: milk2
LANG: C++
*/

#include<fstream>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct Worker {
    int s, e;
    Worker(int s = 0, int e = 0): s(s), e(e) {}
    bool operator < (const Worker & p) const {
        return s < p.s;
    }
};
int n;
vector<Worker> schedule;

int main() {
    ofstream fout ("milk2.out");
    ifstream fin ("milk2.in");

    fin >> n;
    int lo = 0, ln = 0;
    for(int i = 0; i < n; i++) {
        int s, e;
        fin >> s >> e;
        schedule.push_back(Worker(s, e));
    }
    sort(schedule.begin(), schedule.end());

    int duo, right = 0;
    for(int i = 0; i < (int)schedule.size(); i++) {
        if(i > 0 && right >= schedule[i].s)
            duo = duo + schedule[i].e - schedule[i-1].e;
        else
            duo = schedule[i].e - schedule[i].s;
        lo = max(lo, duo);
        if(i > 0 && right < schedule[i].s)
            ln = max(ln, schedule[i].s - right);
        right = max(right, schedule[i].e);
    }
    fout << lo << " " << ln << endl;
    return 0;
}
