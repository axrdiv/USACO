/*
ID: axrdiv1
PROG: barn1
LANG: C++
*/
#include<fstream>
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

vector<int> barn;
vector<int> diff;
int m, s, c;
int main() {
    ofstream fout ("barn1.out");
    ifstream fin ("barn1.in");
    fin >> m >> s >> c;
    for(int i = 0; i < c; i++) {
        int st;
        fin >> st;
        barn.push_back(st);
    }
    sort(barn.begin(), barn.end());
    for(int i = 1; i < (int)barn.size(); i++) {
        diff.push_back(barn[i] - barn[i-1] - 1);
    }
    sort(diff.begin(), diff.end(), greater<int>());
    int leng = barn[barn.size()-1] - barn[0] + 1;
    for(int i = 1; i < min(m, (int)diff.size()+1); i++) {
        if(m == 1) continue;
        leng -= diff[i-1];
    }
    fout << leng << endl;
    return 0;
}
