/*
ID: axrdiv1
PROG: transform
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

int n;

vector<string> orig;
vector<string> aftr;

bool cmp(const vector<string>& a, const vector<string>& b, int n) {
    for(int i = 0; i < n; i++) {
        if(a[i] != b[i]) return false;
    }
    return true;
}

void rotate(vector<string>& tmp, int r){
    for(int rr = 0; rr < r; rr++) {
        vector<string> a = tmp;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                tmp[j][n-1-i] = a[i][j];
    }
}

vector<string> reflact(const vector<string>& orig) {
    vector<string> ret = orig;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            ret[i][j] = orig[i][n-1-j];
        }
    }
    return ret;
}

int transform() {
    // Rotation
    for(int i = 1; i <= 3; i++) {
        vector<string> tr = orig;
        rotate(tr, i);
        if(cmp(tr, aftr, n)) { return i; }
    }

    // Reflection
    vector<string> ref = reflact(orig);
    if(cmp(ref, aftr, n)) return 4;

    // Combination
    for(int i = 1; i <= 3; i++) {
        vector<string> tr = ref;
        rotate(tr, i);
        if(cmp(tr, aftr, n)) { return 5; }
    }

    // No Change
    if(cmp(orig, aftr, n)) return 6;


    // Invalid
    return 7;
}

int main() {
    ofstream fout ("transform.out");
    ifstream fin ("transform.in");
    fin >> n;
    string tmp;
    for(int i = 0; i < n; i++) { fin >> tmp; orig.push_back(tmp); }
    for(int i = 0; i < n; i++) { fin >> tmp; aftr.push_back(tmp); }
    fout << transform() << endl;
    return 0;
}

