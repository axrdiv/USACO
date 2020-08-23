/*
ID: axrdiv1
PROG: cowxor
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;

const int MAX_N = 100005;

ofstream fout("cowxor.out");
ifstream fin("cowxor.in");

int N;
int xors[MAX_N], trie[MAX_N * 10][2], top;
int mxor, st, ed;

void insert(int n) {
    int u = 0;
    for(int i = 20; i >= 0; i--) {
        int now = ((xors[n] >> i) & 1);
        if(!trie[u][now])
            trie[u][now] = ++top;
        u = trie[u][now];
    }
    trie[u][0] = n;
}

int find(int n) {
    int u = 0;
    for(int i = 20; i >= 0; i--) {
        int now = ((xors[n] >> i) & 1);
        if(trie[u][now ^ 1]) u = trie[u][now ^ 1];
        else u = trie[u][now];
    }
    return trie[u][0];
}

int main() {
    fin >> N;
    insert(0);

    for(int i = 1; i <= N; i++) {
        fin >> xors[i];
        xors[i] ^= xors[i - 1];

        int j = find(i);
        if(!st || mxor < (xors[i] ^ xors[j])) {
            mxor = (xors[i] ^ xors[j]);
            st = j + 1;
            ed = i;
        }
        insert(i);
    }

    fout << mxor << " " << st << " " << ed << endl;
    return 0;
}
