/*
ID: axrdiv1
PROG: combo
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;

int n;

inline bool dist(int x1, int x2) {
    return abs((x1-x2+n)%n) <= 2 || abs((x1-x2-n)%n) <= 2;
}
struct lock {
    int x, y, z;
    lock(int x=0, int y=0, int z=0): x(x), y(y), z(z) {};
    bool operator == (const lock& p) {
        return dist(x, p.x) && dist(y, p.y) && dist(z, p.z);
    }
};
int main() {
    ofstream fout("combo.out");
    ifstream fin("combo.in");
    fin >> n;
    int x, y, z;
    fin >> x >> y >> z;
    lock john(x, y, z);
    fin >> x >> y >> z;
    lock master(x, y, z);
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            for(int k = 1; k <= n; k++) {
                lock p(i, j, k);
                if(john == p || master == p)
                    cnt++;
            }
        }
    }
    fout << cnt << endl;
    return 0;
}
