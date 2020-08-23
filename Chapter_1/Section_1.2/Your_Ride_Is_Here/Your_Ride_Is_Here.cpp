/*
ID: axrdiv1
PROG: ride
LANG: C++
*/

#include<fstream>
#include<iostream>
#include<string>

using namespace std;

#define MODNUM 47

int main() {
    ofstream fout("ride.out");
    ifstream fin("ride.in");
    string comet, group;
    fin >> comet >> group;
    int mcom = 1, mgrp = 1;
    for(int i = 0; i < (int)comet.size(); i++)
        mcom = (mcom * ((comet[i] - 'A' + 1) % MODNUM)) % MODNUM;
    for(int i = 0; i < (int)group.size(); i++)
        mgrp = (mgrp * ((group[i] - 'A' + 1) % MODNUM)) % MODNUM;

    string ret = (mcom == mgrp) ? "GO" : "STAY";
    fout << ret << endl;
    return 0;
}
