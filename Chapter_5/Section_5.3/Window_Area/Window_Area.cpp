/*
ID: axrdiv1
PROG: window
LANG: C++
*/

/*
    222233
    551133
    551133
    554444
    其中1是覆盖的部分。
*/
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<cstdio>
using namespace std;

FILE* fout = fopen("window.out", "w");
ifstream fin("window.in");

struct win {
    int x1, y1, x2, y2;
    win(int x1=0, int y1=0, int x2=0, int y2=0): x1(x1), y1(y1), x2(x2), y2(y2) {}
};
ostream& operator<< (ostream& os, const win& w) {
    os << w.x1 << " " << w.y1 << " " << w.x2 << " " << w.y2 << endl;
    return os;
}

int id[300];
win V[3000];
int vl = 1000, vr = 1000;

void create(char ch, win w) {
    id[(int)ch] = vr;
    V[vr] = w;
    vr++;
}

void destroy(char ch) {
    win& w = V[id[(int)ch]];
    w.x1 = w.y1 = w.x2 = w.y2 = 0;
}

void top(char ch) {
    win w = V[id[(int)ch]];
    destroy(ch);
    create(ch, w);
}

void bottom(char ch) {
    win w = V[id[(int)ch]];
    destroy(ch);
    vl--;
    V[vl] = w;
    id[(int)ch] = vl;
}

int ans;

void dfs(win w, int pos) {
    if(w.x1 == w.x2 || w.y1 == w.y2) return;

    if(pos == vr) {
        ans += (w.x2 - w.x1) * (w.y2 - w.y1);
        return;
    }

    win& nw = V[pos];
    int x1 = w.x1, x2 = w.x2, y1 = w.y1, y2 = w.y2;
    int nx1 = nw.x1, nx2 = nw.x2, ny1 = nw.y1, ny2 = nw.y2;
    if(x1 >= nx2 || y1 >= ny2 || x2 <= nx1 || y2 <= ny1) {
        dfs(w, pos+1);
    }
    else if (nx1 <= x1 && ny1 <= y1 && nx2 >= x2 && ny2 >= y2) {
        return;
    }
    else {
        dfs(win(x1, y1, max(x1, nx1), min(y2, ny2)), pos+1);
        dfs(win(x1, min(y2, ny2), min(x2, nx2), y2), pos+1);
        dfs(win(min(x2, nx2), max(y1, ny1), x2, y2), pos+1);
        dfs(win(max(x1, nx1), y1, x2, max(y1, ny1)), pos+1);
    }
}

void show(char ch) {
    int pos = id[(int)ch];
    ans = 0;
    dfs(V[pos], pos+1);
    win& w = V[pos];
    int area = (w.x2-w.x1)*(w.y2-w.y1);
    fprintf(fout, "%.3f\n", (float)ans/area*100);
}

int main() {
    string s;
    while(fin >> s) {
        if(s[0] == 'w') {
            stringstream ss(s.substr(4));
            int a, b, c, d;
            char ch;
            ss >> a >> ch >> b >> ch >> c >> ch >> d;
            if(a > c) swap(a, c);
            if(b > d) swap(b, d);
            create(s[2], win(a, b, c, d));
        }
        else if(s[0] == 't') {
            top(s[2]);
        }
        else if(s[0] == 'b') {
            bottom(s[2]);
        }
        else if(s[0] == 'd') {
            destroy(s[2]);
        }
        else if(s[0] == 's') {
            show(s[2]);
        }
    }
    return 0;
}
