/*
ID: axrdiv1
PROG: crypt1
LANG: C++
*/
#include<fstream>
#include<iostream>
#include<set>
using namespace std;

set<int> crypt;
int n;
bool in_set(int num) {
    while(num) {
        if(crypt.count(num%10) == 0) return false;
        num = num / 10;
    }
    return true;
}
int main() {
    ofstream fout ("crypt1.out");
    ifstream fin ("crypt1.in");
    fin >> n;
    for(int i = 0; i < n; i++) {
        int x;
        fin >> x;
        crypt.insert(x);
    }
    int cnt = 0;
    for(int a = 100; a < 1000; a++) {
        if(!in_set(a)) continue;
        for(int b = 10; b < 100; b++) {
            if(!in_set(b)) continue;
            int s1, s2, s;
            s1 = a * (b%10);
            s2 = a * (b/10);
            s = a * b;
            if(s1 > 99 && s2 > 99 && s1 < 1000 && s2 < 1000 && s > 999 && s < 10000)
                if(in_set(s1) && in_set(s2) && in_set(s))
                    cnt++;
        }
    }
    fout << cnt << endl;
    return 0;
}
