/*
ID: axrdiv1
PROG: ratios
LANG: C++
*/
#include<iostream>
#include<fstream>
using namespace std;

ofstream fout("ratios.out");
ifstream fin("ratios.in");

struct ratio {
    int x, y, z;
    ratio(int x=0, int y=0, int z=0): x(x), y(y), z(z) {}
    ratio operator+ (const ratio& p) {
        return ratio(x+p.x, y+p.y, z+p.z);
    }
    ratio operator- (const ratio& p) {
        return ratio(x-p.x, y-p.y, z-p.z);
    }
    ratio operator* (const int& t) {
        return ratio(x*t, y*t, z*t);
    }
    bool operator<= (const ratio& p) {
        return x <= p.x && y <= p.y && z <= p.z;
    }
    bool operator== (const ratio& p) {
        return x == p.x && y == p.y && z == p.z;
    }
};

ratio pros[4];
int use[4];

bool dfs(const ratio& upper, ratio p, int d) {
    if(d == 4) {
        // cout << p.x << " " << p.y << " " << p.z << endl;
        return p == upper;
    }

    for(int i = 0; p+(pros[d]*i) <= upper; i++) {
        use[d] = i;
        ratio np = p + pros[d]*i;
        if(dfs(upper, np, d+1)) return true;
    }
    return false;
};

int solve() {
    const int maxt = 100+10;
    for(int times = 1; times < maxt; times++) {
        // cout << times << endl;
        ratio upper = pros[0] * times;
        // cout << upper.x << " " << upper.y << " " << upper.z << endl;
        ratio ret;
        if(dfs(upper, ret, 1)) return times;
    }
    return -1;
}

int main() {
    int x, y, z;
    for(int i = 0; i < 4; i++) {
        fin >> x >> y >> z;
        pros[i] = ratio(x, y, z);
    }
    int ret = solve();
    if(ret > 0) {
        for(int i = 1; i < 4; i++) {
            fout << use[i] << " ";
        }
        fout << ret << endl;
    }
    else { fout << "NONE" << endl; }

    return 0;
}
