/*
ID: axrdiv1
PROG: rectbarn
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<algorithm>
#include<set>
using namespace std;
const int MAX_C = 3000 + 10;

ofstream fout("rectbarn.out");
ifstream fin("rectbarn.in");

struct dam {
    int r, c;
    bool operator< (const dam& p) const {
        return r < p.r || (r == p.r && c < p.c);
    }
};

int R, C, P;
set<dam> damaged;

int height[MAX_C];
int stk[MAX_C];
int stktop = 0;

int main() {
    fin >> R >> C >> P;
    for(int i = 0; i < P; i++) {
        int r, c;
        fin >> r >> c;
        r--, c--;
        damaged.insert((dam){r, c});
    }


    int maxArea = 0;
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            if(damaged.count((dam){i, j})) {
                height[j] = 0;
            } else {
                height[j] += 1;
            }
        }
        stktop = 0;
        for(int j = 0; j <= C; j++) {
            while(stktop && height[j] < height[stk[stktop]]) {
                int top = stk[stktop];
                stktop--;
                maxArea = max(maxArea, height[top] * (stktop ? (j - (stk[stktop] + 1)) : j));
            }
            stk[++stktop] = j;
        }
    }
    fout << maxArea << endl;

    return 0;
}
