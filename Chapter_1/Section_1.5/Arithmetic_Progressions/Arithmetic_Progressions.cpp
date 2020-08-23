/*
ID: axrdiv1
PROG: ariprog
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<set>
#include<cstring>
using namespace std;

const int maxm = 256;
bool has[maxm*maxm*2];

int n, m;
bool dfs(int st, int d, int depth) {
    if(depth == 0) {
        return true;
    }
    if(!has[st]) return false;
    return dfs(st+d, d, depth-1);
}

bool tuncate(ofstream& fout) {
    int cnt = 0;
    int end = m*m*2;
    for(int d = 1; d < end/(n-1)+1; d++) {
        for(int i = 0; (i <= end-(n-1)*d) && i < m*m*2; i++) {
            if(has[i] && dfs(i, d, n)) {
                fout << i << " " << d << endl;
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
    memset(has, 0, sizeof(has));
    for(int i = 0; i <= m; i++) {
        for(int j = i; j <= m; j++) {
            int num = i * i + j * j;
            has[num] = 1;
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
