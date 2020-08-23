/*
ID: axrdiv1
PROG: twofive
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

ofstream fout("twofive.out");
ifstream fin("twofive.in");

char C;
string grid;
int N;
vector<string> grids;
bool vis[26];
char line[26];


void dfs(int d) {
    if(d == 25) {
        grids.push_back(line);
        cout << grids.size() << endl;
        cout << line << endl;
        /*
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                cout << line[i*5 + j];
            }
            cout << endl;
        }
        cout << endl;
        */
        return;
    }

    for(int i = 0; i < 25; i++) {
        if(!vis[i] && (d % 5 == 0 || (char)('a' + i) > line[d - 1]) && 
                (d < 5 || (char)('a' + i) > line[d - 5])) {
            vis[i] = true;
            line[d] = (char)('a' + i);
            dfs(d+1);
            vis[i] = false;
        }
    }
}

int main() {
    dfs(0);
    fin >> C;
    if(C == 'N') {
        fin >> N;
        cout << grids[N-1] << endl;
    }
    else {
        fin >> grid;
        cout << find(grids.begin(), grids.end(), grid) - grids.begin() + 1 << endl;
    }

    return 0;
}
