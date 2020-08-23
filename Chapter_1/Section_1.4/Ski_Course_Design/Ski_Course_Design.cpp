/*
ID: axrdiv1
PROG: skidesign
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
const int maxd = 17;
vector<int> hills, diff;

int n;

int main() {
    ofstream fout("skidesign.out");
    ifstream fin("skidesign.in");
    fin >> n;
    for(int i = 0; i < n; i++) {
        int h;
        fin >> h;
        hills.push_back(h);
    }
    sort(hills.begin(), hills.end());
    int d = hills.back() - hills.front() - maxd;
    /*
     * for every possible height of the lower bound
     * calcuate the amount of heightened hill's mass
     * then calcuate the amount of shortened hill's mass
     */
    long long fee;
    if(d > 0) {
        fee = d * d * hills.size();
        for(int h = hills.front(); h <= hills.back() - maxd; h++) {
            long long m = 0, tot = 0, cmove=0, cadd=0;
            vector<int> move;
            for(int i = 0; i < hills.size(); i++) {
                if(hills[i] < h) {  // need to add
                    int p = h - hills[i];
                    tot += p;
                    move.push_back(p);
                }
                else if (hills[i] > h + maxd) { // need to remove
                    int p = hills[i] - h - maxd;
                    tot -= p;
                    move.push_back(-p);
                }
                else {
                    cmove += hills[i] - h;
                    cadd += h + maxd - hills[i];
                    move.push_back(0);
                }
            }
            long long adf = 0;
            for(int i = 0; i < move.size(); i++) {
                    adf += move[i] * move[i];
            }
            cout << tot << endl;
            fee = min(fee, adf);
            /*
            if(tot == 0 || (tot > 0 && cadd >= tot) || (tot < 0 && cmove >= tot)) {
                int ds = tot > 0 ? 1 : -1;
                int bou = tot > 0 ? h : h + maxd;
                int ccnt = tot + 2;
                while(tot && ccnt > 0) {
                    // cout << "ccnt = " << ccnt << endl;
                    ccnt--;
                    for(int ii = 0; tot && ii < hills.size(); ii++) {
                        // cout << h << " - " << ii << endl;
                        if(hills[ii] > h && hills[ii] < h + maxd)
                            if(abs(hills[ii]-bou) > abs(move[ii])) {
                                move[ii] += ds;
                                tot -= ds;
                            }
                    }
                }
                for(int i = 0; i < move.size(); i++) {
                    m += move[i] * move[i];
                }
                if(ccnt) {
                    fee = min(fee, m);
                    cout <<  "h = " << h << " tot = " << tot << " m = " << m << " fee = " << fee << endl;
                }
            }
            */
        }
    }
    else fee = 0;
    fout << fee << endl;
    return 0;
}
