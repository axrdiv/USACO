/*
ID: axrdiv1
PROG: ariprog
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<set>
using namespace std;

int n, m;
set<int> biset;
bool dfs(int st, int d, int depth) {
    if(depth == 0) {
        return true;
    }
    if(biset.count(st) == 0) return false;
    return dfs(st+d, d, depth-1);
}

bool tuncate(ofstream& fout) {
    int cnt = 0;
    int end = *(--biset.end());
    for(int d = 1; d < (*(--biset.end())-*(biset.begin()))/(n-1)+1; d++) {
        for(set<int>::iterator it = biset.begin(); (*it <= end-(n-1)*d) && it != biset.end(); it++) {
            if(dfs(*it, d, n)) {
                fout << *it << " " << d << endl;
                cnt++;
            }
        }
    }
    return cnt > 0;
}


int main() {
    ofstream fout("ariprog.out");
    ifstream fin("ariprog.in");
    fin >> n >> m;
    for(int i = 0; i <= m; i++) {
        for(int j = i; j <= m; j++) {
            int num = i * i + j * j;
            if(biset.count(num) == 0) {
                biset.insert(num);
            }
        }
    }
    /*
    for(set<int>::iterator it = biset.begin(); it != biset.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
    */
    if(!tuncate(fout)) fout << "NONE" << endl;

    return 0;
}
