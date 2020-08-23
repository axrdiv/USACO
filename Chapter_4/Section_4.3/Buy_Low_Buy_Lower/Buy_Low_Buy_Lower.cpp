/*
ID: axrdiv1
PROG: buylow
LANG: C++
*/
#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include<cstring>
using namespace std;
const int maxn = 5000 + 5;

ofstream fout("buylow.out");
ifstream fin("buylow.in");
int N, prices[maxn];
int dp[maxn];

struct bignum {
    static const int base = 1e9;
    int bnum[10];
    int size = 0;
    bignum(int num = 0) {
        memset(bnum, 0, sizeof(bnum));
        while(num) {
            bnum[size] = num % base;
            num = num / base;
            size++;
        }
    }

    bignum operator+ (const bignum& b) const {
        bignum ret;
        int carry = 0;
        for(int i = 0; i < max(size, b.size); i++) {
            ret.bnum[i] = bnum[i] + b.bnum[i] + carry;
            carry = ret.bnum[i] / base;
            ret.bnum[i] = ret.bnum[i] % base;
        }
        if(carry) {
            ret.bnum[max(size, b.size)] = carry;
            ret.size = max(size, b.size)+1;
        } else
            ret.size = max(size, b.size);

        return ret;
    }

    friend ostream& operator<< (ostream& os, const bignum& b) {
        os << b.bnum[b.size-1];
        for(int i = b.size-2; i >= 0; i--) {
            os << setfill('0') << setw(9) << b.bnum[i];
        }
        return os;
    }
};
bignum cnt[maxn];

int main() {
    /*
    cout << "test" << endl;
    bignum a1(5);
    bignum a2(5);
    bignum c = a1 + a2;
    cout << c << endl;
    */


    fin >> N;
    prices[0] = 2147483647;
    for(int i = 1; i <= N; i++)
        fin >> prices[i];

    cnt[0] = bignum(1);
    for(int i = 1; i <= N; i++) {
        dp[i] = 1;                          // initial status
        for(int j = i-1; j >= 1; j--) {
            if(prices[i] < prices[j])
                dp[i] = max(dp[i], dp[j]+1);
        }

        for(int j = i-1; j >= 0; j--) {
            if(prices[i] < prices[j] && dp[i] == dp[j]+1)
                cnt[i] = cnt[j] + cnt[i];
            else if(prices[i] == prices[j] && dp[i] == dp[j])
                break;
        }
    }

    /*
    for(int i = 0; i <= N; i++) {
        cout << dp[i] << " ";
    }
    cout << endl;
    for(int i = 0; i <= N; i++) {
        cout << cnt[i] << " ";
    }
    cout << endl;
    */

    int md = 0;
    bignum mn(0);
    for(int i = 1; i <= N; i++) {
        if(dp[i] > md) {
            md = dp[i];
            mn = cnt[i];
        }
        else if(md == dp[i])
            mn = cnt[i] + mn;
    }
    fout << md << " " << mn << endl;

    return 0;
}
