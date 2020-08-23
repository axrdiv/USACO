/*
ID: axrdiv1
PROG: buylow
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
const int maxn = 5000 + 5;

ofstream fout("buylow.out");
ifstream fin("buylow.in");
int N, prices[maxn];
int d[maxn], cnt[maxn];

int main() {
    fin >> N;
    for(int i = 0; i < N; i++)
        fin >> prices[i];

    int idx = 0;
    for(int i = 0; i < N; i++) {
        int flag = 1;
        for(int j = 0; j < idx; j++) {
            if(prices[i] < d[j]) cnt[j]++;
            // if(prices[i] < d[j]) continue;
            if(prices[i] > d[j]) {
                d[j] = prices[i];
                flag = 0; break;
            }
        }
        if(flag) {
            d[idx] = prices[i];
            cnt[idx] = 1;
            idx++;
        }
    }
    for(int i = 0; i < idx; i++) {
        cout << cnt[i] << " ";
    }
    cout << endl;

    for(int i = 0; i < idx; i++) {
        cout << d[i] << " ";
    }
    cout << endl;

    cout << idx << " " << cnt[idx-1] << endl;
    return 0;
}
