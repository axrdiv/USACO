/*
ID: axrdiv1
PROG: palsquare
LANG: C++
*/
#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include<stack>
using namespace std;

const int maxn = 22;
char map[maxn], str[17];

int base;

bool is_palin(int cnt) {
    int l = 0, r = cnt-1;
    while(l < r) {
        if(str[l++] != str[r--]) 
            return false;
    }
    return true;
}

bool palin(int num, int base) {
    num = num * num;
    int cnt = 0;
    while(num) {
        str[cnt++] = map[num%base];
        num = num / base;
    }
    str[cnt] = '\0';
    return is_palin(cnt);
}

string to_base(int num, int base) {
    string ret;
    stack<char> s;
    while(num) {
        s.push(map[num%base]);
        num = num / base;
    }
    while(!s.empty()) {
        ret.push_back(s.top());
        s.pop();
    }
    return ret;
}
int main() {
    // init
    for(int i = 0; i < maxn; i++) {
        if(i < 10)
            map[i] = '0' + i;
        else
            map[i] = 'A' + i - 10;
    }
    ofstream fout ("palsquare.out");
    ifstream fin ("palsquare.in");

    fin >> base;
    for(int i = 1; i <= 300; i++) {
        if(palin(i, base))
            fout << to_base(i, base) << " " << to_base(i*i, base) << endl;
    }
    return 0;
}
