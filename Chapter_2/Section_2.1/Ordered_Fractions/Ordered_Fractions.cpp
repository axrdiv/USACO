/*
ID: axrdiv1
PROG: frac1
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<set>
using namespace std;


struct frac {
    int a, b;
    frac(int a=0, int b=1): a(a), b(b) {};
    bool operator < (const frac& p) const {
        return a*p.b < p.a*b;
    }

};
ostream& operator << (ostream& out, const frac& p) {
    out << p.a << "/" << p.b;
    return out;
}

set<frac> list;

int gcd(int a, int b) {
    return (b > 0) ? gcd(b, a%b) : a;
}

int n;
int main() {
    ofstream fout("frac1.out");
    ifstream fin("frac1.in");
    fin >> n;
    for(int b = 2; b <= n; b++) {
        for(int a = 1; a < b; a++) {
            int g = gcd(a, b);
            list.insert(frac(a/g, b/g));
        }
    }
    list.insert(frac(0, 1));
    list.insert(frac(1, 1));

    for(set<frac>::iterator it = list.begin(); it != list.end(); it++) {
        fout << *it << endl;
    }
    return 0;
}
