/*
ID: axrdiv1
PROG: starry
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXWH = 100 + 5;

ofstream fout("starry.out");
ifstream fin("starry.in");

int sky[MAXWH][MAXWH], vis[MAXWH][MAXWH];
char ans[MAXWH][MAXWH];

char line[MAXWH];

int W, H;
const int dh[] = {-1, -1, -1,  0,  0,  1,  1,  1};
const int dw[] = {-1,  0,  1, -1,  1, -1,  0,  1};

struct pos {
    int h, w;
    pos(int h=0, int w=0): h(h), w(w) {}
    pos neiber(int d) {
        return pos(h+dh[d], w+dw[d]);
    }
    pos operator-= (const pos& p) {
        h -= p.h;
        w -= p.w;
        return *this;
    }
    bool valid() {
        return h >= 0 && h < H && w >= 0 && w < W;
    }
    bool operator< (const pos& p) const {
        return h < p.h || (h == p.h && w < p.w);
    }
    bool operator== (const pos& p) const {
        return h == p.h && w == p.w;
    }
    bool operator!=(const pos& p) const {
        return !(this->operator==(p));
    }
};

struct cluster {
    vector<pos> vec;
    char c;
    cluster(char c=0): c(c) {}
};

void search(int h, int w, cluster& cl) {
    vis[h][w] = 1;
    int loc = 0;
    cl.vec.push_back(pos(h, w));
    while(loc < (int)cl.vec.size()) {
        pos p = cl.vec[loc];   // if using "pos& p = vec[loc]" here will show something unexcepted
        for(int d = 0; d < 8; d++) {
            pos np = p.neiber(d);
            if(np.valid() && sky[np.h][np.w] && !vis[np.h][np.w]) {
                vis[np.h][np.w] = 1;
                cl.vec.push_back(np);
            }
        }
        loc++;
    }
    sort(cl.vec.begin(), cl.vec.end());
}

vector<cluster> stars;
int alpha[26]; int alpha_pos=0;

void regulize(cluster& cl) {
    pos m(MAXWH, MAXWH);
    for(int i = 0; i < (int)cl.vec.size(); i++) {
        pos& p = cl.vec[i];
        m.h = min(m.h, p.h);
        m.w = min(m.w, p.w);
    }
    for(int i = 0; i < (int)cl.vec.size(); i++) {
        pos& p = cl.vec[i];
        p -= m;
    }
    sort(cl.vec.begin(), cl.vec.end());
}

void reflact(cluster& cl) {
    for(int i = 0; i < (int)cl.vec.size(); i++) {
        pos& p = cl.vec[i];
        p.h = -p.h;
    }
}

bool pequ(const cluster& a, const cluster& b) {
    for(int i = 0; i < (int)a.vec.size(); i++) {
        if(!(a.vec[i] == b.vec[i])) return false;
    }
    return true;
}

void rotate(cluster& cl) {
    // rotate around origin point
    for(int i = 0; i < (int)cl.vec.size(); i++) {
        pos& p = cl.vec[i];
        int tmp = p.h;
        p.h = p.w;
        p.w = -tmp;
    }
}

bool equ(cluster a, cluster b) {
    regulize(b);
    regulize(a);
    if(pequ(a, b)) return true;
    for(int i = 0; i < 3; i++) {
        rotate(a); regulize(a);
        if(pequ(a, b)) return true;
    }
    reflact(a); regulize(a);
    if(pequ(a, b)) return true;
    for(int i = 0; i < 3; i++) {
        rotate(a); regulize(a);
        if(pequ(a, b)) return true;
    }
    return false;
}

void find() {
    for(int h = 0; h < H; h++) {
        for(int w = 0; w < W; w++) {
            if(sky[h][w] && !vis[h][w]) {
                cluster cl;
                search(h, w, cl);
                for(int i = 0; i < alpha_pos; i++) {
                    if(stars[alpha[i]].vec.size() != cl.vec.size()) continue;
                    if(equ(stars[alpha[i]], cl)) {
                        cl.c = (char)('a'+i);
                        break;
                    }
                }
                if(cl.c == 0) {
                    cl.c = (char)('a'+alpha_pos);
                    alpha[alpha_pos] = stars.size();
                    alpha_pos += 1;
                }
                stars.push_back(cl);
            }
        }
    }
}

void plot() {
    for(int i = 0; i < (int)stars.size(); i++) {
        for(int j = 0; j < (int)stars[i].vec.size(); j++) {
            pos& p = stars[i].vec[j];
            ans[p.h][p.w] = stars[i].c;
        }
    }
}

int main() {
    fin >> W >> H;
    for(int i = 0; i < H; i++) {
        fin >> line;
        for(int j = 0; j < W; j++) {
            sky[i][j] = (line[j] == '1');
        }
    }

    find();
    plot();
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            fout << (ans[i][j] ? (char)ans[i][j] : '0');
        }
        fout << endl;
    }

#ifdef DEBUG
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            cout << (char)(sky[i][j] + '0');
        }
        cout << endl;
    }
    cout << "stars.size() = " << stars.size() << endl;
    for(int i = 0; i < stars.size(); i++) {
        cout << i << ": " << stars[i].vec.size() << endl;
    }

    for(int i = 0; i < alpha_pos; i++) {
        cout << (char)('a'+i) << " " << alpha[i] << endl;
    }
#endif

    return 0;
}
