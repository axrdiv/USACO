/*
ID: axrdiv1
PROG: fc
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cmath>
#include<iomanip>
#include<cstdio>
using namespace std;
const int MAXN = 10000 + 5;

FILE* fout = fopen("fc.out", "w");
ifstream fin("fc.in");

struct pos {
    double x, y;
    pos(double x=0, double y=0): x(x), y(y) {};

    pos operator+= (const pos& p) {
        x += p.x;
        y += p.y;
        return *this;
    }

    pos operator/ (const int& scale) const {
        return pos(x/scale, y/scale);
    }
    pos operator- (const pos& p) const {
        return pos(x-p.x, y-p.y);
    }

};

struct angle{
    double ang;
    int id;
    angle(double ang=0, int id=0): ang(ang), id(id) {};
    bool operator< (const angle& p) const {
        return ang < p.ang;
    }
};

int N;

pos cows[MAXN];
angle angsort[MAXN];
int hull[MAXN];

double zcrossprod(const pos& p1, const pos& p2) {
    return p1.x*p2.y-p1.y*p2.x;
}

int hullpos;
int hullstart;
void build() {
    int pid;
    hull[0] = angsort[0].id;
    hull[1] = angsort[1].id;
    hullpos = 2;
    for(int i = 2; i < N-1; i++) {
        pid = angsort[i].id;
        pos& p = cows[pid];
        while(hullpos > 1 && 
                zcrossprod(cows[hull[hullpos-2]]-cows[hull[hullpos-1]],
                    cows[hull[hullpos-1]]-p) < 0) {
            hullpos -= 1;
        }
        hull[hullpos] = pid;
        hullpos += 1;
    }

    // add last position
    pid = angsort[N-1].id;
    pos& p = cows[pid];
    while(hullpos > 1 && 
            zcrossprod(cows[hull[hullpos-2]]-cows[hull[hullpos-1]],
                cows[hull[hullpos-1]]-p) < 0) {
        hullpos -= 1;
    }

    hullstart = 0;
    bool flag;
    do {
        flag = false;
        if(hullpos - hullstart >= 2 && 
                zcrossprod(p-cows[hull[hullpos-1]], 
                    cows[hull[hullstart]]-p) < 0) {
            pid = hull[hullpos-1];
            p = cows[pid];
            hullpos -= 1;
            flag = true;
        }
        if(hullpos - hullstart >= 2 &&
                zcrossprod(cows[hull[hullstart]]-p, 
                    cows[hull[hullstart+1]]-cows[hull[hullstart]]) < 0) {
            hullstart += 1;
            flag = true;
        }
    } while(flag);

    hull[hullpos] = pid;
    hullpos += 1;
}

int main() {
    fin >> N;
    pos center;
    for(int i = 0; i < N; i++) {
        pos& p = cows[i];
        fin >> p.x >> p.y;
        center += p;
    }

    center = center / N;
    for(int i = 0; i < N; i++) {
        angle& pa = angsort[i];
        pa.id = i;
        pa.ang = atan2(cows[i].y - center.y, cows[i].x - center.x);
    }
    sort(angsort, angsort+N);

#ifdef DEBUG
    for(int i = 0; i < N; i++) {
        cout << angsort[i].id << " " << angsort[i].ang << endl;
    }
#endif

    build();

#ifdef DEBUG
    cout << "size = " << hullpos - hullstart + 1 << endl;
    cout << hullpos << ", " <<  hullstart << endl;
    for(int i = hullstart; i < hullpos; i++) {
        pos& p = cows[hull[i]];
        cout << p.x << " " << p.y << endl;
        // cout << hull[i] << endl;
    }
#endif

    double length = 0;
    for(int i = hullstart+1; i < hullpos; i++) {
        pos p = cows[hull[i]] - cows[hull[i-1]];
        length += sqrt(p.x*p.x + p.y*p.y);
    }
    pos p = cows[hull[hullstart]] - cows[hull[hullpos-1]];
    length += sqrt(p.x*p.x + p.y*p.y);
    fprintf(fout, "%.2f\n", length);
    return 0;
}
