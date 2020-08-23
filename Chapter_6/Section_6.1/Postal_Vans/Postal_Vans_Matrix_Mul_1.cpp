/*
ID: axrdiv1
PROG: vans
LANG: C++
*/

#include<iostream>
#include<iomanip>
#include<fstream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<cmath>
using namespace std;
const int MAX_N = 1000;

typedef long long ll;

struct bignum {
    static const int base = 1e5;
    int bnum[100];
    int size = 0;
    bool sign = 0;

    bignum() {
        memset(bnum, 0, sizeof(bnum));
        sign = 0;
        size = 0;
    }

    bignum(int num) {
        memset(bnum, 0, sizeof(bnum));
        sign = num < 0;
        num = abs(num);
        while(num) {
            bnum[size] = num % base;
            num = num / base;
            size++;
        }
    }

    bignum absolute_subtract(const bignum& A, const bignum& B) {
        bignum C;
        int borrow = 0;
        int pos;
        for(pos = 0; pos < max(A.size, B.size); pos++) {
            C.bnum[pos] = A.bnum[pos] - B.bnum[pos] - borrow;
            if(C.bnum[pos] < 0) {
                C.bnum[pos] = C.bnum[pos] + base;
                borrow = 1;
            } else 
                borrow = 0;
        }

        for(pos = 99; pos >= 0; pos--) {
            if(C.bnum[pos] != 0) {
                C.size = pos + 1;
                break;
            }
        }

        return C;
    }

    bignum absolute_add(const bignum& A, const bignum& B) const {
        bignum ret;
        int carry = 0;
        for(int i = 0; i < max(A.size, B.size); i++) {
            ret.bnum[i] = A.bnum[i] + B.bnum[i] + carry;
            carry = ret.bnum[i] / base;
            ret.bnum[i] = ret.bnum[i] % base;
        }
        if(carry) {
            ret.bnum[max(size, B.size)] = carry;
            ret.size = max(size, B.size)+1;
        } else
            ret.size = max(size, B.size);

        return ret;
    }
    int compare(const bignum& A, const bignum& B) {
        if(A.sign < B.sign) return 1;
        else if(A.sign > B.sign) return -1;
        else {
            for(int i = max(A.size, B.size); i >= 0; i--) {
                if(A.bnum[i] > B.bnum[i]) {
                    if(A.sign == 0)
                        return -1;
                    else
                        return 1;
                }

            }
            return 0;
        }
    }

    bignum operator+ (const bignum& B) {
        bignum ret;
        if(sign == B.sign) {
            ret = absolute_add(*this, B);
            ret.sign = sign;
        }
        else {
            if(compare(*this, B) == -1) {
                ret = absolute_subtract(*this, B);
                ret.sign = sign;
            }
            else {
                ret = absolute_subtract(B, *this);
                ret.sign = B.sign;
            }
        }
        return ret;
    }


    bignum operator= (int num) {
        memset(bnum, 0, sizeof(bnum));
        sign = num < 0;
        num = abs(num);
        while(num) {
            bnum[size] = num % base;
            num = num / base;
            size++;
        }
        return *this;
    }

    bignum operator= (const bignum& b) {
        memcpy(bnum, b.bnum, sizeof(b.bnum));
        size = b.size;
        sign = b.sign;
        return *this;
    }

    bignum operator* (int m) const {
        bignum ret;
        bignum tmp = *this;
        int mm = abs(m);
        while(mm) {
            if(mm & 1) ret = ret + tmp;
            tmp = tmp + tmp;
            mm >>= 1;
        }
        ret.sign = !(ret.sign == (m < 0));
        return ret;
    }

    bignum operator* (const bignum &b) const {
        bignum ret;
        for(int i = 0; i < size; i++) {
            bignum tmp1 = b * bnum[i];
            bignum tmp2;
            memcpy(tmp2.bnum + i, tmp1.bnum, sizeof(int) * tmp1.size);
            tmp2.size = tmp1.size + i;
            ret = ret + tmp2;
        }
        ret.sign = !(sign == b.sign);
        return ret;
    }

    friend ostream& operator<< (ostream& os, const bignum& b) {
        if(b.size) os << (b.sign ? "-" : "") << b.bnum[b.size-1];
        else os << 0;
        for(int i = b.size-2; i >= 0; i--) {
            os << setfill('0') << setw(5) << b.bnum[i];
        }
        return os;
    }

};


typedef vector<bignum> vec;
typedef vector<vec> mat;

mat mul(mat& A, mat& B) {
    mat C(A.size(), vec(B[0].size()));
    for(int i = 0; i < A.size(); i++) {
        for(int k = 0; k < B.size(); k++) {
            for(int j = 0; j < B[0].size(); j++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]);
            }
        }
    }
    return C;
}

mat pow(mat A, int n) {
    mat B(A.size(), vec(A.size()));
    for(int i = 0; i < A.size(); i++) {
        B[i][i] = 1;
    }

    while(n > 0) {
        if(n & 1) B = mul(B, A);
        A = mul(A, A);
        n >>= 1;
    }
    return B;
}

ofstream fout("vans.out");
ifstream fin("vans.in");

int N;

bignum solve() {
    if(N == 0) return bignum(0);
    if(N == 1) return bignum(0);
    if(N == 2) return bignum(2);
    if(N == 3) return bignum(4);
    mat A(4, vec(4));
    A[0][0] = 1, A[0][1] = 1, A[0][2] =-1, A[0][3] = 2;
    A[1][0] = 1, A[1][1] = 0, A[1][2] = 0, A[1][3] = 0;
    A[2][0] = 0, A[2][1] = 1, A[2][2] = 0, A[2][3] = 0;
    A[3][0] = 1, A[3][1] = 0, A[3][2] = 0, A[3][3] = 1;

    mat B = pow(A, N - 3);

    for(int i = 0; i < B.size(); i++) {
        for(int j = 0; j < B[0].size(); j++)
            cout << B[i][j] << " ";
        cout << endl;
    }
    return (B[3][0] * 8) + (B[3][1] * 2) + (B[3][2] * 2) + (B[3][3] * 4);
}

int main() {
    fin >> N;
    cout << solve() << endl;
    cout << bignum(7658493) + bignum(-7658492) << endl;
    return 0;
}
